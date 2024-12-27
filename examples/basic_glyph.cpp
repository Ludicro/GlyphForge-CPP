#include "writer.h"
#include "spell_data.h"
#include <SFML/Graphics.hpp>

int main() {
    // Create a basic spell configuration
    SpellAttributes attrs{
        "1",            // level
        "Evocation",    // school
        "Instantaneous", // duration
        "60 feet",      // range
        "Cone",         // area
        "Fire",         // dtype
        "None",         // condition
        false,          // concentration
        false           // ritual
    };

    // Initialize writer and create glyph
    Writer writer;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Basic Glyph Example");
    
    // Generate and display the glyph
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                // Regenerate glyph on spacebar press
                writer.createGlyph(attrs);
            }
        }

        window.clear(sf::Color::White);
        writer.draw(window);
        window.display();
    }

    return 0;
}
