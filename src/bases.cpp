#include "bases.h"
#include <cmath>

std::vector<sf::Vector2f> BaseShape::generatePolygon(int n, float radius) {
    std::vector<sf::Vector2f> points;
    float startAngle = M_PI / n;
    
    for (int i = 0; i < n; ++i) {
        float angle = startAngle + i * 2 * M_PI / n;
        float x = radius * std::sin(angle) + 400.f; // Center offset
        float y = radius * std::cos(angle) + 400.f;
        points.push_back(sf::Vector2f(x, y));
    }
    return points;
}

std::vector<sf::Vector2f> BaseShape::generateCircle(int n, float radius) {
    std::vector<sf::Vector2f> points;
    float theta0 = 0;
    float theta1 = -M_PI / 2;
    
    for (int i = 0; i < n; ++i) {
        float t = theta0 + (theta1 - theta0) * i / (n - 1);
        float x = radius * std::cos(t) + 400.f;
        float y = radius * std::sin(t) + 400.f;
        points.push_back(sf::Vector2f(x, y));
    }
    return points;
}

std::vector<sf::Vector2f> BaseShape::generateQuadratic(int n, float a, float b, float c) {
    std::vector<sf::Vector2f> points;
    std::vector<float> x_values;
    x_values.push_back(0);
    
    while (x_values.size() < n) {
        float last_x = x_values.back();
        if (std::find(x_values.begin(), x_values.end(), -last_x) != x_values.end()) {
            x_values.push_back(-last_x + 1);
        } else {
            x_values.push_back(-last_x);
        }
    }
    
    float scale = 50.f;
    for (float x : x_values) {
        float y = a * x * x + b * x + c;
        points.push_back(sf::Vector2f(x * scale + 400.f, y * scale + 400.f));
    }
    return points;
}

std::vector<sf::Vector2f> BaseShape::generateGolden(int n, float limit) {
    std::vector<sf::Vector2f> points;
    float golden_ratio = (1.f + std::sqrt(5.f)) / 2.f;
    float scale = 50.f;
    
    for (int i = 0; i < n; ++i) {
        float t = limit * i / (n - 1);
        float factor = std::pow(golden_ratio, t * golden_ratio / (2 * M_PI));
        float x = std::cos(t) * factor * scale + 400.f;
        float y = std::sin(t) * factor * scale + 400.f;
        points.push_back(sf::Vector2f(x, y));
    }
    return points;
}
