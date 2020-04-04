#include "trace_ray.h"
#include <cmath>

#include <iostream>

int scene_intersect(const Vec3m &orig, const Vec3m &dir, const std::vector<Shape*> &shapes, Vec3m &intersection, Vec3m &norm, double t_max) {
    double d, min_d = t_max;
    int len = shapes.size();
    int min_i = len;
    for (int i = 0; i < len; ++i)
    {
        if (shapes[i]->intersect(orig, dir, d)) {
            if (d < min_d) {
                min_d = d;
                min_i = i;
            }
        }
    }
    if (min_i == len) return min_i;
    intersection = orig + dir * min_d;
    norm = shapes[min_i]->normal(intersection);
    return min_i;
}


Colour trace_ray(const Vec3m &orig, const Vec3m &dir, std::vector<Shape*> &shapes, std::vector<Light*> &lights, double t_max, int refl) {
    int len_sh = shapes.size();
    Material min_mat(BACK_COL,0,0); //фон

    Vec3m intersection, norm_sh;
    int min_i = scene_intersect(orig, dir, shapes, intersection, norm_sh, t_max);

    if ((min_i == len_sh) || (!refl)) {
        return min_mat.colour;
    }

    norm_sh = shapes[min_i]->normal(intersection);

    //рекурсивные отражения
    Vec3m reflect_dir = reflect(dir, norm_sh).normilize();
    Vec3m reflect_orig = reflect_dir*norm_sh < 0 ? intersection - norm_sh*1e-3 : intersection + norm_sh*1e-3; //дабы не отражаться от самого себя   
    Colour reflect_colour = trace_ray(reflect_orig, reflect_dir, shapes, lights, t_max, refl-1);

    double light_intensity = 0, specular_light = 0;
    min_mat = shapes[min_i]->getMaterial(intersection);
    int len_l = lights.size();
    for (int i = 0; i < len_l; i++) {
        Vec3m light_direction = (lights[i]->position - intersection).normilize();
        double pr_ld_norm = light_direction * norm_sh;
        //тень или не тень
        Vec3m shadow_orig = intersection + norm_sh*1e-3;
        Vec3m shadow_pt, shadow_N;
        if ((scene_intersect(shadow_orig, light_direction, shapes, shadow_pt, shadow_N, t_max) != len_sh) && ((shadow_pt - shadow_orig).norm() < (lights[i]->position - intersection).norm()))
            continue;

        //освещённость (диффузная)
        if (pr_ld_norm > 0) {
            light_intensity += lights[i]->intens * pr_ld_norm;
        }
       
        //интенсивность отражённого цвета (блеск)
        Vec3m R = (reflect(light_direction, norm_sh)).normilize();
        double pr_r_rd = R * dir;
        if (min_mat.specularity != -1){ 
            if (pr_r_rd > 0) {
                specular_light += lights[i]->intens * std::pow(pr_r_rd, min_mat.specularity);
            }
        }
    }
    return min_mat.colour * light_intensity + Colour(255,255,255) * specular_light + reflect_colour * min_mat.reflectivity * (refl * 0.25); 
    //                                                                                                      затемнение отражения по мере углубления
}