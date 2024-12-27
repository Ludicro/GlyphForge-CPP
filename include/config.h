#ifndef CONFIG_H
#define CONFIG_H

#include <SFML/Graphics.hpp>

namespace Config {
    // Window settings
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 600;
    constexpr char WINDOW_TITLE[] = "GlyphForge";
    
    // Drawing settings
    constexpr float BASE_RADIUS = 300.f;
    constexpr float POINT_RADIUS = 5.f;
    constexpr int LINE_SEGMENTS = 150;
    
    // Colors
    const sf::Color BACKGROUND_COLOR = sf::Color::White;
    const sf::Color BASE_COLOR = sf::Color::Black;
    const sf::Color LINE_COLOR = sf::Color::Red;
    const sf::Color POINT_COLOR = sf::Color::Black;
    
    // File paths
    constexpr char RESOURCE_PATH[] = "resources/";
    constexpr char COMBINATIONS_FILE[] = "resources/combinations.bin";
    constexpr char ATTRIBUTES_FILE[] = "resources/attributes.json";
    constexpr char SPELLS_PATH[] = "resources/spells/";
    
    // GUI settings
    constexpr float PADDING = 10.f;
    constexpr float BUTTON_WIDTH = 120.f;
    constexpr float BUTTON_HEIGHT = 30.f;
    constexpr float DROPDOWN_WIDTH = 150.f;
}

#endif // CONFIG_H
