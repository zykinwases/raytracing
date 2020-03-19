#include "vec3m.h"

#include <cmath>

Vec3m::Vec3m(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3m Vec3m::normilize() {
    double norm = std::sqrt(x*x + y*y + z*z);
    if (norm != 0) { 
        return Vec3m(x/norm, y/norm, z/norm);
    } else return *this;
}

const double& Vec3m::operator[](const int i) const{ 
    if (i == 1) return x;
    if (i == 2) return y;
    if (i == 3) return z;
}

double& Vec3m::operator[](const int i) { 
    if (i == 1) return x;
    if (i == 2) return y;
    if (i == 3) return z;
}

Vec3m operator+(Vec3m lhs, const Vec3m& rhs) {
    for (int i = 1; i <= 3; i++) {
        lhs[i] += rhs[i];
    }
    return lhs;
}

Vec3m operator-(Vec3m lhs, const Vec3m& rhs) {
    for (int i = 1; i <= 3; i++) {
        lhs[i] -= rhs[i];
    }
    return lhs;
}

Vec3m operator*(Vec3m lhs, const double a) {
    double ret = 0;
    for (int i = 1; i <= 3; i++) {
        lhs[i] *= a;
    }
    return lhs;
}

double operator*(const Vec3m& lhs, const Vec3m& rhs) {
    double ret = 0;
    for (int i = 1; i <= 3; i++) {
        ret += lhs[i] * rhs[i];
    }
    return ret;
}