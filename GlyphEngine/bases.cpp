#include "GlyphEngine\bases.h"
#include <cmath>

namespace bases {

// Creates a regular polygon with n sides
// Parameters:
//   n: number of vertices
//   radius: distance from center to vertices (default = 1.0)
//   start_angle: initial angle in radians (default = -1)
Point2D polygon(int n, double radius, double start_angle) {
    std::vector<double> x(n), y(n);
    
    // If no start angle specified, use PI/n
    if (start_angle < 0) {
        start_angle = M_PI / n;
    }
    
    // Calculate vertex positions using polar coordinates
    for (int i = 0; i < n; i++) {
        double angle = start_angle + i * 2 * M_PI / n;
        x[i] = radius * sin(angle);
        y[i] = radius * cos(angle);
    }
    
    return {x, y};
}

// Creates a horizontal line with n points
// Parameters:
//   n: number of points
Point2D line(int n) {
    std::vector<double> x(n), y(n, 0.0);
    for (int i = 0; i < n; i++) {
        x[i] = i;
    }
    return {x, y};
}

// Creates points following a quadratic function f(x) = ax² + bx + c
// Parameters:
//   n: number of points
//   a, b, c: quadratic coefficients
Point2D quadratic(int n, double a, double b, double c) {
    std::vector<double> x, y;
    x.push_back(0);
    
    // Generate x coordinates
    while (x.size() < size_t(n)) {
        double last = x.back();
        bool found = false;
        for (double val : x) {
            if (val == -last) {
                found = true;
                break;
            }
        }
        x.push_back(found ? -last + 1 : -last);
    }
    
    // Calculate y coordinates using quadratic formula
    y.resize(x.size());
    for (size_t i = 0; i < x.size(); i++) {
        y[i] = a * x[i] * x[i] + b * x[i] + c;
    }
    
    return {x, y};
}

// Creates points along a circular arc
// Parameters:
//   n: number of points
//   radius: circle radius
//   theta0: start angle in radians
//   theta1: end angle in radians
Point2D circle(int n, double radius, double theta0, double theta1) {
    std::vector<double> x(n), y(n);
    double step = (theta1 - theta0) / (n - 1);
    
    // Generate points using parametric equations of a circle
    for (int i = 0; i < n; i++) {
        double theta = theta0 + i * step;
        x[i] = radius * cos(theta);
        y[i] = radius * sin(theta);
    }
    
    return {x, y};
}

// Creates points following a cubic function f(x) = ax³ + bx² + cx + d
// Parameters:
//   n: number of points
//   a, b, c, d: cubic coefficients
Point2D cubic(int n, double a, double b, double c, double d) {
    std::vector<double> x(n), y(n);
    int start = -n/2;
    
    // Generate points centered around x=0
    for (int i = 0; i < n; i++) {
        x[i] = start + i;
        double x_val = x[i];
        y[i] = a * x_val * x_val * x_val + b * x_val * x_val + c * x_val + d;
    }
    
    return {x, y};
}

// Creates points in a golden spiral pattern
// Parameters:
//   n: number of points
//   lim: maximum angle limit
Point2D golden(int n, double lim) {
    std::vector<double> x(n), y(n);
    double g = (1.0 + sqrt(5.0)) / 2.0;  // golden ratio
    double step = lim / (n - 1);
    
    // Generate points using golden ratio spiral formula
    for (int i = 0; i < n; i++) {
        double t = i * step;
        double f = pow(g, t * g / (2 * M_PI));
        x[i] = cos(t) * f;
        y[i] = sin(t) * f;
    }
    
    return {x, y};
}

}
