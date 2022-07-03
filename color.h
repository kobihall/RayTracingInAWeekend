#pragma once

#include "utils.h"

#include <iostream>

uint32_t write_color(glm::dvec3 pixel_color, int samples_per_pixel) {
    double r = pixel_color.x;
    double g = pixel_color.y;
    double b = pixel_color.z;

    auto scale = 1.0/ samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    return (255 << 24) 
    | (static_cast<uint8_t>(256 * clamp(b, 0.0, 0.999)) << 16) 
    | (static_cast<uint8_t>(256 * clamp(g, 0.0, 0.999)) << 8) 
    |  static_cast<uint8_t>(256 * clamp(r, 0.0, 0.999));
}