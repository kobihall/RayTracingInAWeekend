#pragma once

#include <glm/glm.hpp>
#include "ray.h"

struct hit_record {
    glm::dvec3 p;
    glm::dvec3 normal;
    double t;
    bool front_face;

    inline void set_face_normal(const ray& r, const glm::dvec3& outward_normal) 
    {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class hittable {
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};