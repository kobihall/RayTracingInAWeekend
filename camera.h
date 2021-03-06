#pragma once

#include <glm/glm.hpp>

#include "utils.h"
#include "ray.h"

class camera {
public:
    camera();
    camera(uint32_t ViewportWidth, uint32_t ViewportHeight, double vfov, glm::dvec3 lookfrom, glm::dvec3 lookat, glm::dvec3 vup);

    ray get_ray(double u, double v) const;

private:
    glm::dvec3 m_origin;
    glm::dvec3 m_lower_left_corner;
    glm::dvec3 m_horizontal;
    glm::dvec3 m_vertical;
};