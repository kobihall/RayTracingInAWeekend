#pragma once

#include "vec3.h"
#include "utils.h"

#include <iostream>

uint32_t write_color(color pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    auto scale = 1.0/ samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    return (255 << 24) 
    | (static_cast<uint8_t>(256 * clamp(b, 0.0, 0.999)) << 16) 
    | (static_cast<uint8_t>(256 * clamp(g, 0.0, 0.999)) << 8) 
    |  static_cast<uint8_t>(256 * clamp(r, 0.0, 0.999));
}