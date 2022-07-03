#pragma once

#include <cmath>
#include <cstdlib>
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

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}