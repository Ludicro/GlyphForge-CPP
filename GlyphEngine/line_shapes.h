#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <random>
#include <utility>

namespace line_shapes {
    using Point2D = std::pair<std::vector<double>, std::vector<double>>;
    using Point = std::pair<double, double>;

    Point2D centre_circle(const Point& P, const Point& Q, const std::string& thetas = "");
    Point2D non_centre_circle(const Point& P, const Point& Q, const std::string& thetas = "");
    Point2D straight(const Point& P, const Point& Q);
}
