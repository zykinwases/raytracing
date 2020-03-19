#include "trace_ray.h"

#include <iostream>

Colour trace_ray(const Vec3m &orig, const Vec3m &dir, std::vector<Shape*> shapes, std::vector<Light*> lights, double t_max, int refl) {
    int len = shapes.size();
    int min_i = len;
    double d, min_d = t_max;
    Colour min_c(255,255,255); //цвет фона
    for (int i = 0; i < len; ++i)
    {
        if (shapes[i]->intersect(orig, dir, d)) {
            if (d < min_d) {
        	    min_d = d;
                min_c = shapes[i]->material.colour;
                min_i = i;
            }
        }
    }
    Vec3m intersection = orig + dir * d;

    double light_intensity = 0;
    if (min_i < len) {
        len = lights.size();
        for (int i = 0; i < len; i++) {
            Vec3m light_direction = (lights[i]->position - intersection).normilize();
            double pr_ld_norm = light_direction * shapes[i]->normal(intersection);
            if (pr_ld_norm > 0) {
                light_intensity += lights[i]->intens * pr_ld_norm; //тут делить на произведение длин light_direction и нормали к примитиву, но их длина и так равна 1
            }
        }
    }
    return min_c * light_intensity;
}