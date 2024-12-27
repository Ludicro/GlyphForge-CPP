
#ifndef LINE_SHAPES_H
#define LINE_SHAPES_H

#include <SFML/Graphics.hpp>
#include <vector>

class LineShape {
public:
    enum class Type {
        STRAIGHT,
        CENTRE_CIRCLE
    };

    static std::vector<sf::Vector2f> drawStraight(const sf::Vector2f& P, const sf::Vector2f& Q);
    static std::vector<sf::Vector2f> drawCentreCircle(const sf::Vector2f& P, const sf::Vector2f& Q, bool fullCircle = false);
    
    static std::vector<sf::Vector2f> draw(Type type, const sf::Vector2f& P, const sf::Vector2f& Q) {
        switch (type) {
            case Type::STRAIGHT:      return drawStraight(P, Q);
            case Type::CENTRE_CIRCLE: return drawCentreCircle(P, Q);
            default:                  return drawStraight(P, Q);
        }
    }
};

#endif // LINE_SHAPES_H
