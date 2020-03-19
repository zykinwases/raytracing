#include "trace_ray.h"

#include <iostream>

Colour trace_ray(const Vec3m &orig, const Vec3m &dir, std::vector<Shape*> shapes, double t_max, int refl) {
    int len = shapes.size();
    double d, min_d = t_max;
    Colour min_c(255,255,255); //цвет фона
    for (int i = 0; i < len; ++i)
    {
        if (shapes[i]->intersect(orig, dir, d)) {
            if (d < min_d) {
        	    min_d = d;
                min_c = shapes[i]->material.colour;
            }
        }
    }
    return min_c;
}