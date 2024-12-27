#ifndef SPELLAPP_H
#define SPELLAPP_H

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <string>
#include <vector>
#include <memory>
#include "writer.h"
#include "bases.h"
#include "line_shapes.h"

class SpellApp {
private:
    sf::RenderWindow window;
    sf::Texture currentImage;
    sf::Sprite imageSprite;
    
    // Attribute storage
    std::vector<std::string> levels;
    std::vector<std::string> schools;
    std::vector<std::string> durations;
    std::vector<std::string> ranges;
    std::vector<std::string> areas;
    std::vector<std::string> dtypes;
    std::vector<std::string> conditions;
    
    // Current selections
    std::string currentLevel;
    std::string currentSchool;
    std::string currentDuration;
    std::string currentRange;
    std::string currentArea;
    std::string currentDtype;
    std::string currentCondition;
    bool concentration;
    bool ritual;
    
    void loadAttributes();
    void createGUI();
    void generateSpell();
    void randomSpell();
    void saveImage();
    void displayImage(const sf::Image& image);

public:
    SpellApp();
    void run();
};

#endif // SPELLAPP_H
