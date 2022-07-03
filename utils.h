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

inline double random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}