#include "shapes.h"
#include <cmath>

#include <iostream>
#define sqr(x) ((x)*(x))

Colour::Colour(int r, int g, int b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Sphere::Sphere(Vec3m center, double r, Material material) {
    this->center = center;
    this->r = r;
    this->material = material;
}

bool Sphere::intersect(const Vec3m &orig, const Vec3m &dir, double &d) {
    Vec3m L = center - orig;
    double L_dir = L*dir;
    double c_dir = L*L - L_dir*L_dir;
    if (c_dir > r*r) return false;
    double d_in_sph = std::sqrt(r*r - c_dir);
    d = L_dir - d_in_sph;
    if (d < 1) d = L_dir + d_in_sph; //переделать 1 на что-то более общее (расстояние до экрана)
    if (d < 1) return false;
    return true;
}