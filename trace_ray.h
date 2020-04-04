#ifndef TRACE
#define TRACE
#include <cstdint>
#include <vector>
#include "shapes.h"
#include "lights.h"

#define MAX_REFL 3
#define BACK_COL Colour(0,0,0)

Colour trace_ray(const Vec3m &orig, const Vec3m &dir, std::vector<Shape*> &shapes, std::vector<Light*> &lights, double t_max, int refl = MAX_REFL);
#endif