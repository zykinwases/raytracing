#ifndef BITMAP_GUARDIAN_H
#define BITMAP_GUARDIAN_H
#include "shapes.h"

typedef std::vector<std::vector<Colour>> vec2;
void SaveBMP(const char* fname, const vec2 pixels, int h, int w);

#endif 
