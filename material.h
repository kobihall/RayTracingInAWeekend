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
    metal(const glm::dvec3& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, glm::dvec3& attenuation, ray& scattered) const override;

public:
    glm::dvec3 albedo;
    double fuzz;
};

class phong : public material {
public:
    phong(const glm::dvec3& a, double s) : albedo(a), smoothness(s) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, glm::dvec3& attenuation, ray& scattered) const override;

public:
    glm::dvec3 albedo;
    double smoothness;
};

glm::dvec3 refract(const glm::dvec3& uv, const glm::dvec3& n, double niovernt);

class dielectric : public material {
public:
    dielectric(double index_of_refraction) : ir(index_of_refraction) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, glm::dvec3& attenuation, ray& scattered) const override;

public:
    double ir; //Index of Refraction

private:
    static double reflectance(double cosine, double ref_idx);
};