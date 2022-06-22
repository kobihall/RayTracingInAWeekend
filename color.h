#pragma once

#include "vec3.h"

#include <iostream>

uint32_t write_color(color pixel_color) {
    return (255 << 24) 
    | (static_cast<uint8_t>(255.999 * pixel_color.z()) << 16) 
    | (static_cast<uint8_t>(255.999 * pixel_color.y()) << 8) 
    |  static_cast<uint8_t>(255.999 * pixel_color.x());
}