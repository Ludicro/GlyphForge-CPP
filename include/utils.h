#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

namespace Utils {
    // String manipulation
    std::string toLower(const std::string& str);
    std::string toUpper(const std::string& str);
    std::vector<std::string> split(const std::string& str, char delimiter);
    
    // Math utilities
    float degToRad(float degrees);
    float radToDeg(float radians);
    float normalizeAngle(float angle);
    
    // Vector operations
    float distance(const sf::Vector2f& p1, const sf::Vector2f& p2);
    sf::Vector2f normalize(const sf::Vector2f& vector);
    float dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2);
    
    // Color operations
    sf::Color interpolateColor(const sf::Color& c1, const sf::Color& c2, float t);
    sf::Color adjustBrightness(const sf::Color& color, float factor);
    
    // Random utilities
    float randomFloat(float min, float max);
    int randomInt(int min, int max);
    bool randomBool();
}

#endif // UTILS_H
