#pragma once

#include <algorithm>
#include <glm/glm.hpp>
#include "utils.h"

glm::dvec3 random_in_unit_sphere(glm::dvec3 normal, double alpha);

glm::dmat3 GetTangentSpace(glm::dvec3 normal);