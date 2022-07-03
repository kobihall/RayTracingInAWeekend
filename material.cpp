#include "material.h"
#include "hittable.h"

bool lambertian::scatter(const ray& r_in, const hit_record& rec, glm::dvec3& attenuation, ray& scattered) const
{
    auto scatter_direction = rec.normal + Random::random_in_ball();
    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}

bool metal::scatter(const ray& r_in, const hit_record& rec, glm::dvec3& attenuation, ray& scattered) const
{
    glm::dvec3 reflected = glm::reflect(glm::normalize(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}