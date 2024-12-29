#pragma once
#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>
#include <utility>

namespace bases {
    // Return type for all base functions
    using Point2D = std::pair<std::vector<double>, std::vector<double>>;

    Point2D polygon(int n, double radius = 1.0, double start_angle = -1);
    Point2D line(int n);
    Point2D quadratic(int n, double a = 1.0, double b = 0.0, double c = 0.0);
    Point2D circle(int n, double radius = 1.0, double theta0 = 0.0, double theta1 = -M_PI/2);
    Point2D cubic(int n, double a = 0.1, double b = 0.0, double c = -0.75, double d = 0.0);
    Point2D golden(int n, double lim = 3.0 * M_PI);
}
