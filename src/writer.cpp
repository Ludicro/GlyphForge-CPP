#include "writer.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <cmath>

using json = nlohmann::json;

Writer::Writer() {
    loadCombinations();
}

void Writer::loadCombinations() {
    std::ifstream file("resources/combinations.bin", std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not load combinations file");
    }
    
    // Read the pre-computed combinations from binary file
    uint32_t numCombinations, combinationSize;
    file.read(reinterpret_cast<char*>(&numCombinations), sizeof(uint32_t));
    file.read(reinterpret_cast<char*>(&combinationSize), sizeof(uint32_t));
    
    combinations.resize(numCombinations);
    for (auto& combo : combinations) {
        combo.resize(combinationSize);
        file.read(reinterpret_cast<char*>(combo.data()), combinationSize * sizeof(int));
    }
}

std::vector<int> Writer::generatePattern(const SpellAttributes& attrs) {
    // Convert attributes to indices
    std::vector<int> indices;
    indices.push_back(std::stoi(attrs.level));
    // Add other attribute conversions
    
    // Combine patterns based on attributes
    std::vector<int> finalPattern(combinations[0].size(), 0);
    for (size_t i = 0; i < indices.size(); ++i) {
        for (size_t j = 0; j < finalPattern.size(); ++j) {
            finalPattern[j] |= combinations[indices[i]][j];
        }
    }
    
    return finalPattern;
}

sf::Image Writer::createGlyph(const SpellAttributes& attrs) {
    sf::RenderTexture renderTexture;
    renderTexture.create(800, 800);
    renderTexture.clear(sf::Color::White);
    
    // Generate base points
    std::vector<sf::Vector2f> basePoints = generateBasePoints(attrs);
    
    // Draw base shape
    drawBase(renderTexture, basePoints);
    
    // Generate and draw connections
    std::vector<int> pattern = generatePattern(attrs);
    drawConnections(renderTexture, basePoints, pattern);
    
    // Add ritual/concentration markers if needed
    if (attrs.ritual || attrs.concentration) {
        drawMarkers(renderTexture, attrs);
    }
    
    renderTexture.display();
    return renderTexture.getTexture().copyToImage();
}

std::string Writer::findMatchingSpell(const SpellAttributes& attrs) {
    std::string filename = "resources/spells/wizard_" + attrs.level + ".json";
    std::ifstream f(filename);
    if (!f) {
        return "";
    }
    
    json spells = json::parse(f);
    for (const auto& spell : spells) {
        if (spell["school"] == attrs.school &&
            spell["duration"] == attrs.duration &&
            spell["range"] == attrs.range &&
            spell["area_type"] == attrs.area &&
            spell["dtype"] == attrs.dtype &&
            spell["condition"] == attrs.condition &&
            spell["concentration"] == attrs.concentration &&
            spell["ritual"] == attrs.ritual) {
            return spell["name"];
        }
    }
    
    return "";
}

void Writer::drawBase(sf::RenderTexture& texture, const std::vector<sf::Vector2f>& points) {
    // Draw points
    for (const auto& point : points) {
        sf::CircleShape circle(5.f);
        circle.setFillColor(sf::Color::Black);
        circle.setPosition(point - sf::Vector2f(5.f, 5.f));
        texture.draw(circle);
    }
    
    // Draw base outline
    sf::VertexArray lines(sf::LineStrip, points.size() + 1);
    for (size_t i = 0; i < points.size(); ++i) {
        lines[i].position = points[i];
        lines[i].color = sf::Color::Black;
    }
    lines[points.size()] = lines[0]; // Close the shape
    texture.draw(lines);
}

void Writer::drawConnections(sf::RenderTexture& texture, 
                           const std::vector<sf::Vector2f>& points, 
                           const std::vector<int>& pattern) {
    for (size_t i = 0; i < pattern.size(); ++i) {
        if (pattern[i] == 0) continue;
        
        size_t start = i;
        size_t end = (i + 1) % points.size();
        
        if (currentLineType == LineType::STRAIGHT) {
            drawStraightLine(texture, points[start], points[end]);
        } else {
            drawArcLine(texture, points[start], points[end]);
        }
    }
}

void Writer::drawStraightLine(sf::RenderTexture& texture, 
                            sf::Vector2f start, 
                            sf::Vector2f end) {
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = start;
    line[1].position = end;
    line[0].color = sf::Color::Red;
    line[1].color = sf::Color::Red;
    texture.draw(line);
}

void Writer::drawArcLine(sf::RenderTexture& texture, 
                        sf::Vector2f start, 
                        sf::Vector2f end) {
    // Calculate center point
    sf::Vector2f center = (start + end) / 2.f;
    float radius = std::sqrt(
        std::pow(start.x - center.x, 2) + 
        std::pow(start.y - center.y, 2)
    );
    
    // Create arc points
    sf::VertexArray arc(sf::LineStrip);
    float startAngle = std::atan2(start.y - center.y, start.x - center.x);
    float endAngle = std::atan2(end.y - center.y, end.x - center.x);
    
    for (float t = 0; t <= 1.0f; t += 0.02f) {
        float angle = startAngle + (endAngle - startAngle) * t;
        sf::Vector2f point(
            center.x + radius * std::cos(angle),
            center.y + radius * std::sin(angle)
        );
        arc.append(sf::Vertex(point, sf::Color::Red));
    }
    
    texture.draw(arc);
}
