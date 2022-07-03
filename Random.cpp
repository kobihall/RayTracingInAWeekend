#include "Random.h"

glm::dvec3 random_in_unit_sphere(glm::dvec3 normal, double alpha)
{
    double cosTheta = pow(random_double(), 1.0 / (alpha + 1.0));
    double sinTheta = sqrt(std::max(0.0, 1 - cosTheta * cosTheta));
    float phi = 2 * PI * random_double();
    glm::dvec3 tangentSpaceDir = glm::dvec3(cos(phi) * sinTheta, sin(phi) * sinTheta, cosTheta);

    return GetTangentSpace(normal)*tangentSpaceDir;
}

glm::dmat3 GetTangentSpace(glm::dvec3 normal)
{
    glm::dvec3 helper = glm::dvec3(1,0,0);
    if(abs(normal.x) > 0.99)
        helper = glm::dvec3(0,0,1);
    glm::dvec3 tangent = normalize(cross(normal,helper));
    glm::dvec3 binormal = normalize(cross(normal,tangent));
    return glm::mat3(tangent, binormal, normal);
}