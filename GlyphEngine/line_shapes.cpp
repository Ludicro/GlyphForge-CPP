#include "GlyphEngine\line_shapes.h"

namespace line_shapes {

// Draws connecting circles between two lines with the center being the average of the two points
Point2D centre_circle(const Point& P, const Point& Q, const std::string& thetas) {
    const int NUM_POINTS = 150;
    std::vector<double> X(NUM_POINTS), Y(NUM_POINTS);
    
    // Extract coordinates from input points
    double x1 = P.first, y1 = P.second;
    double x2 = Q.first, y2 = Q.second;
    
    // Calculate center point and radius
    double a = (x1 + x2) / 2;
    double b = (y1 + y2) / 2;
    double r = std::sqrt(std::pow(a - x1, 2) + std::pow(b - y1, 2));
    
    if (thetas == "Full") {
        // Generate points for a full circle
        for (int i = 0; i < NUM_POINTS; i++) {
            double theta = i * 2 * M_PI / (NUM_POINTS - 1);
            X[i] = r * std::cos(theta) + a;
            Y[i] = r * std::sin(theta) + b;
        }
    } else {
        // Calculate start and end angles for arc
        double theta0 = std::atan2(y1 - b, x1 - a);
        double theta1 = std::atan2(y2 - b, x2 - a);
        
        // Adjust angles if necessary
        if (y2 < y1) {
            theta0 += M_PI;
            theta1 += M_PI;
        }
        
        // Generate points for the arc
        for (int i = 0; i < NUM_POINTS; i++) {
            double theta = theta0 + i * (theta1 - theta0) / (NUM_POINTS - 1);
            X[i] = r * std::cos(theta) + a;
            Y[i] = r * std::sin(theta) + b;
        }
    }
    
    return {X, Y};
}

// Function to create a circle with a randomly offset center point between P and Q
Point2D non_centre_circle(const Point& P, const Point& Q, const std::string& thetas) {
    const int NUM_POINTS = 150;
    std::vector<double> X(NUM_POINTS), Y(NUM_POINTS);
    
    // Extract coordinates from input points
    double x1 = P.first, y1 = P.second;
    double x2 = Q.first, y2 = Q.second;
    
    // Calculate distance between points
    double distance = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    
    // Set up random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-0.1 * distance, 0.1 * distance);
    
    // Generate two possible center points
    double b = dis(gen);
    double b2 = -b;
    
    // Calculate corresponding x-coordinates for the center points
    double delta = x1*x1 - x2*x2 + y1*y1 - y2*y2;
    double a = (delta - 2*(y1 - y2)*b)/(2*(x1 - x2));
    double a2 = (delta - 2*(y1 - y2)*b2)/(2*(x1 - x2));
    
    // Calculate radii for both possible circles
    double r = std::sqrt(std::pow(x1-a, 2) + std::pow(y1-b, 2));
    double r2 = std::sqrt(std::pow(x1-a2, 2) + std::pow(y1-b2, 2));
    
    // Choose the circle with smaller radius
    if (r2 <= r) {
        a = a2;
        b = b2;
        r = r2;
    }
    
    if (thetas == "Full") {
        // Generate points for a full circle
        for (int i = 0; i < NUM_POINTS; i++) {
            double theta = i * 2 * M_PI / (NUM_POINTS - 1);
            X[i] = r * std::cos(theta) + a;
            Y[i] = r * std::sin(theta) + b;
        }
    } else {
        // Calculate possible start and end angles for arcs
        double theta0 = std::atan2(y1-b, x1-a);
        double theta1 = std::atan2(y2-b, x2-a);
        double theta02 = theta0;
        double theta12 = theta1;
        
        // Adjust angles to ensure proper arc calculation
        while (theta1 < theta0) theta0 -= 2*M_PI;
        while (theta02 < theta12) theta12 -= 2*M_PI;
        
        // Calculate arc lengths for both possibilities
        double arc1 = r*(theta1 - theta0);
        double arc2 = r*(theta02 - theta12);
        
        // Choose the shorter arc or default to first arc if center is close to line
        if (arc1 < arc2 || std::abs(b) < 1) {
            for (int i = 0; i < NUM_POINTS; i++) {
                double theta = theta1 + i * (theta0 - theta1) / (NUM_POINTS - 1);
                X[i] = r * std::cos(theta) + a;
                Y[i] = r * std::sin(theta) + b;
            }
        } else {
            for (int i = 0; i < NUM_POINTS; i++) {
                double theta = theta02 + i * (theta12 - theta02) / (NUM_POINTS - 1);
                X[i] = r * std::cos(theta) + a;
                Y[i] = r * std::sin(theta) + b;
            }
        }
    }
    
    return {X, Y};
}

// Function to create a straight line between points P and Q
Point2D straight(const Point& P, const Point& Q) {
    return {
        std::vector<double>{P.first, Q.first},
        std::vector<double>{P.second, Q.second}
    };
}

}
