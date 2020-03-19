#ifndef LIGHTS
#define LIGHTS
#include "vec3m.h"

class Light
{
public:
    Vec3m position;
    double intens;

    Light(const Vec3m position, const double intens);
};

#endif