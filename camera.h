#pragma once

#include "utils.h"
#include "vec3.h"
#include "ray.h"

class camera {
public:
    camera();
    camera(uint32_t ViewportWidth, uint32_t ViewportHeight);

    ray get_ray(double u, double v) const;

private:
    point3 m_origin;
    point3 m_lower_left_corner;
    vec3 m_horizontal;
    vec3 m_vertical;
};