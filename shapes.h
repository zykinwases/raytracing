#ifndef SHAPES
#define SHAPES

#include "vec3m.h"

class Colour {
public:
    int r;
    int g;
    int b;

    Colour(int r = 0, int g = 0, int b = 0);
};
Colour operator* (Colour col, const double a);
Colour operator+ (Colour col1, Colour col2);

class Material {
public:
    Colour colour;
    double specularity;
    double reflectivity;
    Material(Colour colour = Colour(), double specularity = 1, double reflectivity = 0) {this->colour = colour; this->specularity = specularity; this->reflectivity=reflectivity;}
};

class Shape {
    public:
        Material material;
        virtual bool intersect(const Vec3m &orig, const Vec3m &dir, double &d) = 0; //расстояние до ближайшего пересечения с лучём из точки О в направлении D
        virtual Vec3m normal(const Vec3m &point) = 0;
};

class Sphere : public Shape
{
public:
    Vec3m center;
    double r;
    Sphere(Vec3m center, double r, Material material);
    bool intersect(const Vec3m &orig, const Vec3m &dir, double &d);
    Vec3m normal(const Vec3m &point);
};

class Floor : public Shape
{
public:
    double y;
    Material mat1;
    Material mat2;
	Floor(double y, Material mat1, Material mat2) {this->y = y; this->mat1 = mat1; this->mat2 = mat2;};
	bool intersect(const Vec3m &orig, const Vec3m &dir, double &d);
    Vec3m normal(const Vec3m &point);
};
#endif