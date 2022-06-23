#pragma once

#include <cstdint>
#include "vec3.h"

class Renderer {
public:
    Renderer() {}
    ~Renderer() {}

    void render(uint32_t* ImageData, uint32_t ViewportWidth, uint32_t ViewportHeight);
private:
    point3 origin = point3(0, 0, 0);
    double focal_length = 1.0;
    double camera_height = 2.0;
};