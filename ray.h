#pragma once

#include <glm/glm.hpp>

class ray {
public:
    ray() {}
    ray(const glm::dvec3& origin, const glm::dvec3& direction) : orig(origin), dir(direction) {}

    glm::dvec3 origin() const  { return orig; }
    glm::dvec3 direction() const { return dir; }

    glm::dvec3 at(double t) const { return orig + t*dir; }

    glm::dvec3 orig;
    glm::dvec3 dir;
};