#ifndef VEC
#define VEC

class Vec3m {
public:
    double x;
    double y;
    double z;

    Vec3m(double x = 0, double y = 0, double z = 0);
    Vec3m normilize();
    double norm();
    double& operator[](const int i);
    const double& operator[](const int i) const;
};


Vec3m operator+(Vec3m lhs, const Vec3m& rhs);
Vec3m operator-(Vec3m lhs, const Vec3m& rhs);
Vec3m operator*(Vec3m lhs, const double a);
double operator*(const Vec3m& lhs, const Vec3m& rhs);

Vec3m reflect(const Vec3m &I, const Vec3m &N);
#endif