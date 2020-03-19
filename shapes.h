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

class Material {
public:
    Colour colour;
    Material(Colour colour = Colour()) {this->colour = colour;}
};

class Shape {
    public:
        Material material;
        virtual bool intersect(const Vec3m &orig, const Vec3m &dir, double &d) = 0; //расстояние до ближайшего пересечения с лучём из точки О в направлении D
};

class Sphere : public Shape
{
public:
    Vec3m center;
    double r;
    bool intersect(const Vec3m &orig, const Vec3m &dir, double &d);
    Sphere(Vec3m center, double r, Material material);
};
#endif