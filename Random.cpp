#include "Random.h"

std::mt19937 Random::s_RandomEngine;
std::uniform_int_distribution<std::mt19937::result_type> Random::s_iDistribution;
std::uniform_real_distribution<double> Random::s_dDistribution;

uint32_t Random::random_uint()
{
    return s_iDistribution(s_RandomEngine);
}

uint32_t Random::random_uint(uint32_t min, uint32_t max)
{
    return min + (s_iDistribution(s_RandomEngine) % (max - min + 1));
}

double Random::random_double()
{
    return s_dDistribution(s_RandomEngine);
}

double Random::random_double(double min, double max)
{
    return min + (max-min)*random_double();
}

glm::dvec3 Random::random_vec3()
{
    return glm::dvec3(random_double(), random_double(), random_double());
}

glm::dvec3 Random::random_vec3(double min, double max)
{
    return glm::dvec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

glm::dvec3 Random::random_in_ball()
{
    while (true) {
        auto p = random_vec3(-1,1);
        if (dot(p,p) >= 1) continue;
        return p;
    }
}

glm::dvec3 Random::random_in_unit_sphere()
{
    double cosTheta = random_double(-1,1);
    double sinTheta = sqrt(std::max(0.0, 1 - cosTheta * cosTheta));
    float phi = 2 * PI * random_double();
    return glm::dvec3(cos(phi) * sinTheta, sin(phi) * sinTheta, cosTheta);
}

glm::dvec3 Random::random_in_hemisphere(glm::dvec3 normal)
{
    return Random::random_in_hemisphere(normal,0);
}

glm::dvec3 Random::random_in_hemisphere(glm::dvec3 normal, double alpha)
{
    double cosTheta = pow(random_double(), 1.0 / (alpha + 1.0));
    double sinTheta = sqrt(std::max(0.0, 1 - cosTheta * cosTheta));
    float phi = 2 * PI * random_double();
    glm::dvec3 tangentSpaceDir = glm::dvec3(cos(phi) * sinTheta, sin(phi) * sinTheta, cosTheta);

    return getTangentSpace(normal)*tangentSpaceDir;
}

glm::dmat3 getTangentSpace(glm::dvec3 normal)
{
    glm::dvec3 helper = glm::dvec3(1,0,0);
    if(abs(normal.x) > 0.99)
        helper = glm::dvec3(0,0,1);
    glm::dvec3 tangent = normalize(cross(normal,helper));
    glm::dvec3 binormal = normalize(cross(normal,tangent));
    return glm::mat3(tangent, binormal, normal);
}