#pragma once

#include "hittable.h"
#include <glm/glm.hpp>

class sphere : public hittable
{
public:
    sphere() {}
    sphere(glm::dvec3 cen, double r) : center(cen), radius(r) {};

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
public:
    glm::dvec3 center;
    double radius;
};