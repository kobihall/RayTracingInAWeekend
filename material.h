#pragma once

#include <glm/glm.hpp>
#include "ray.h"
#include "Random.h"

struct hit_record;

class material {
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, glm::dvec3& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {
public:
    lambertian(const glm::dvec3& a) : albedo(a) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, glm::dvec3& attenuation, ray& scattered) const override;

public:
    glm::dvec3 albedo;
};

class metal : public material {
public:
    metal(const glm::dvec3& a) : albedo(a) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, glm::dvec3& attenuation, ray& scattered) const override;

public:
    glm::dvec3 albedo;
};