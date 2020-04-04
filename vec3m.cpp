#include "vec3m.h"

#include <cmath>

#include <iostream>

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

double Vec3m::norm() {
    return std::sqrt(x*x + y*y + z*z);
}

const double& Vec3m::operator[](const int i) const{ 
    if (i == 1) return x;
    if (i == 2) return y;
    else return z;
}

bool Vec3m::operator==(const Vec3m &v) {
    return ((std::abs(this->x - v.x) < 1e-3) && (std::abs(this->y - v.y) < 1e-3) && (std::abs(this->z - v.z) < 1e-3));
}

double& Vec3m::operator[](const int i) { 
    if (i == 1) return x;
    if (i == 2) return y;
    else return z;
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

Vec3m reflect(const Vec3m &I, const Vec3m &N) {
    return I - N*2*(I*N);
}