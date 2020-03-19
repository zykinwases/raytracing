#include "lights.h"

Light::Light(const Vec3m position, const double intens) {
    this->position = position;
    this->intens = intens;
}