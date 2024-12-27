
#include "line_shapes.h"
#include <cmath>

std::vector<sf::Vector2f> LineShape::drawStraight(const sf::Vector2f& P, const sf::Vector2f& Q) {
    std::vector<sf::Vector2f> points;
    points.push_back(P);
    points.push_back(Q);
    return points;
}

std::vector<sf::Vector2f> LineShape::drawCentreCircle(const sf::Vector2f& P, const sf::Vector2f& Q, bool fullCircle) {
    std::vector<sf::Vector2f> points;
    const int NUM_POINTS = 150;
    
    // Calculate center point (average of P and Q)
    sf::Vector2f center = (P + Q) / 2.f;
    
    // Calculate radius
    float radius = std::sqrt(
        std::pow(center.x - P.x, 2) + 
        std::pow(center.y - P.y, 2)
    );
    
    if (fullCircle) {
        // Generate full circle
        for (int i = 0; i <= NUM_POINTS; ++i) {
            float theta = 2.0f * M_PI * i / NUM_POINTS;
            float x = radius * std::cos(theta) + center.x;
            float y = radius * std::sin(theta) + center.y;
            points.push_back(sf::Vector2f(x, y));
        }
    } else {
        // Calculate start and end angles
        float theta0 = std::atan2(P.y - center.y, P.x - center.x);
        float theta1 = std::atan2(Q.y - center.y, Q.x - center.x);
        
        // Adjust for y-coordinate comparison
        if (Q.y < P.y) {
            theta0 += M_PI;
            theta1 += M_PI;
        }
        
        // Generate arc points
        for (int i = 0; i <= NUM_POINTS; ++i) {
            float t = static_cast<float>(i) / NUM_POINTS;
            float theta = theta0 + (theta1 - theta0) * t;
            float x = radius * std::cos(theta) + center.x;
            float y = radius * std::sin(theta) + center.y;
            points.push_back(sf::Vector2f(x, y));
        }
    }
    
    return points;
}
