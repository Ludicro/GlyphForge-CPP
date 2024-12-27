#include "utils.h"
#include <algorithm>
#include <random>
#include <cmath>

namespace Utils {
    std::string toLower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

    std::string toUpper(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }

    std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(str);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    float degToRad(float degrees) {
        return degrees * M_PI / 180.0f;
    }

    float radToDeg(float radians) {
        return radians * 180.0f / M_PI;
    }

    float normalizeAngle(float angle) {
        while (angle > 2 * M_PI) angle -= 2 * M_PI;
        while (angle < 0) angle += 2 * M_PI;
        return angle;
    }

    float distance(const sf::Vector2f& p1, const sf::Vector2f& p2) {
        return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
    }

    sf::Vector2f normalize(const sf::Vector2f& vector) {
        float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
        if (length != 0) {
            return sf::Vector2f(vector.x / length, vector.y / length);
        }
        return vector;
    }

    float dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    sf::Color interpolateColor(const sf::Color& c1, const sf::Color& c2, float t) {
        return sf::Color(
            c1.r + (c2.r - c1.r) * t,
            c1.g + (c2.g - c1.g) * t,
            c1.b + (c2.b - c1.b) * t,
            c1.a + (c2.a - c1.a) * t
        );
    }

    sf::Color adjustBrightness(const sf::Color& color, float factor) {
        return sf::Color(
            std::min(255.f, color.r * factor),
            std::min(255.f, color.g * factor),
            std::min(255.f, color.b * factor),
            color.a
        );
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());

    float randomFloat(float min, float max) {
        std::uniform_real_distribution<float> dis(min, max);
        return dis(gen);
    }

    int randomInt(int min, int max) {
        std::uniform_int_distribution<int> dis(min, max);
        return dis(gen);
    }

    bool randomBool() {
        return randomInt(0, 1) == 1;
    }
}
