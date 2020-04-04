#include "shapes.h"
#include <cmath>

#include <iostream>
#define sqr(x) ((x)*(x))
#define min(x,y) ((x) < (y) ? (x) : (y))
#define max(x,y) ((x) >= (y) ? (x) : (y))

Colour::Colour(int r, int g, int b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Colour operator* (Colour col, const double a) {
    col.r = (col.r * a <= 255) ? (col.r * a) : 255;
    col.g = (col.g * a <= 255) ? (col.g * a) : 255;
    col.b = (col.b * a <= 255) ? (col.b * a) : 255;
    return col;
}

Colour operator+ (Colour col1, Colour col2) {
    col1.r = (col1.r + col2.r <= 255) ? (col1.r + col2.r) : 255;
    col1.g = (col1.g + col2.g <= 255) ? (col1.g + col2.g) : 255;
    col1.b = (col1.b + col2.b <= 255) ? (col1.b + col2.b) : 255;
    return col1;
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
    if (d < 1) d = L_dir + d_in_sph;
    if (d < 1) return false;
    return true;
}

Vec3m Sphere::normal(const Vec3m &point) {
    return (point - center).normilize();
}

Material Floor::getMaterial(Vec3m &point) {
    return (int(round(point.x/2) + round(point.z/2)) & 1) ? mat1 : mat2;
}

bool Floor::intersect(const Vec3m &orig, const Vec3m &dir, double &d) {
    if (((orig.y > y) && (dir.y < 0)) || ((orig.y < y) && (dir.y > 0))) {
        double a = (y - orig.y) / dir.y;
        d = (dir * a).norm();
        return true;
    }
    return false;
}

Vec3m Floor::normal(const Vec3m &point) {
    return (y < 0) ? Vec3m(0,1,0) : Vec3m(0,-1,0);
}

Plane::Plane(Vec3m normal_v, double dest0, Material material) {
    this->normal_v = normal_v.normilize();
    this->dest0 = dest0;
    this->material = material;
}

bool Plane::intersect(const Vec3m &orig, const Vec3m &dir, double &d) {
    d = (-dest0 - (normal_v * orig))/(normal_v * dir);
    return (d >= 0);
}