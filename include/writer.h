#ifndef WRITER_H
#define WRITER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

struct SpellAttributes {
    std::string level;
    std::string school;
    std::string duration;
    std::string range;
    std::string area;
    std::string dtype;
    std::string condition;
    bool concentration;
    bool ritual;
};

class Writer {
private:
    std::vector<std::vector<int>> combinations;
    
    void loadCombinations();
    void drawBase(sf::RenderTexture& texture, const std::vector<sf::Vector2f>& points);
    void drawConnections(sf::RenderTexture& texture, const std::vector<sf::Vector2f>& points, 
                        const std::vector<int>& pattern);
    std::vector<int> generatePattern(const SpellAttributes& attrs);

public:
    Writer();
    sf::Image createGlyph(const SpellAttributes& attrs);
    std::string findMatchingSpell(const SpellAttributes& attrs);
};

#endif // WRITER_H
