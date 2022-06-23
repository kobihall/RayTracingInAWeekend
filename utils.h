#pragma once

#include <cmath>
#include <limits>
#include <memory>

// Constants
const double INFTY = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

// Utility functions
inline double degrees_to_radians(double degrees)
{
    return degrees * PI / 180.0;
}