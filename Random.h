#pragma once

#include <random>
#include <algorithm>
#include <glm/glm.hpp>
#include "utils.h"

class Random
{
public:
    static void Init()
    {
        s_RandomEngine.seed(std::random_device()());
    } 

    static uint32_t random_uint();
    static uint32_t random_uint(uint32_t min, uint32_t max);

    static double random_double();
    static double random_double(double min, double max);

    static glm::dvec3 random_vec3();
    static glm::dvec3 random_vec3(double min, double max);

    static glm::dvec3 random_in_ball();
    static glm::dvec3 random_in_unit_sphere();
    static glm::dvec3 random_in_hemisphere(glm::dvec3 normal);
    static glm::dvec3 random_in_hemisphere(glm::dvec3 normal, double alpha);
private:
    static std::mt19937 s_RandomEngine;
    static std::uniform_int_distribution<std::mt19937::result_type> s_iDistribution;
    static std::uniform_real_distribution<double> s_dDistribution;
};

glm::dmat3 getTangentSpace(glm::dvec3 normal);