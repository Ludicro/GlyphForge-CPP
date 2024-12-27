#ifndef BASES_H
#define BASES_H

#include <SFML/Graphics.hpp>
#include <vector>

class BaseShape {
public:
    enum class Type {
        POLYGON,
        CIRCLE,
        QUADRATIC,
        CUBIC,
        GOLDEN
    };

    static std::vector<sf::Vector2f> generatePolygon(int n, float radius = 300.f);
    static std::vector<sf::Vector2f> generateCircle(int n, float radius = 300.f);
    static std::vector<sf::Vector2f> generateQuadratic(int n, float a = 1.f, float b = 0.f, float c = 0.f);
    static std::vector<sf::Vector2f> generateCubic(int n, float a = 0.1f, float b = 0.f, float c = -0.75f, float d = 0.f);
    static std::vector<sf::Vector2f> generateGolden(int n, float limit = 3.f * M_PI);

    static std::vector<sf::Vector2f> generate(Type type, int n) {
        switch (type) {
            case Type::POLYGON:   return generatePolygon(n);
            case Type::CIRCLE:    return generateCircle(n);
            case Type::QUADRATIC: return generateQuadratic(n);
            case Type::CUBIC:     return generateCubic(n);
            case Type::GOLDEN:    return generateGolden(n);
            default:             return generatePolygon(n);
        }
    }
};

#endif // BASES_H
