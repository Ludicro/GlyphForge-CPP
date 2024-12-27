#include "writer.h"
#include "spell_data.h"
#include "bases.h"
#include "line_shapes.h"
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Custom Spell Glyph");
    ImGui::SFML::Init(window);

    Writer writer;
    SpellAttributes attrs{
        "0",            // level
        "None",         // school
        "Instantaneous", // duration
        "None",         // range
        "None",         // area
        "None",         // dtype
        "None",         // condition
        false,          // concentration
        false           // ritual
    };

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        // Custom ImGui interface
        ImGui::Begin("Spell Customization");
        
        const char* levels[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
        static int levelIdx = 0;
        if (ImGui::Combo("Level", &levelIdx, levels, IM_ARRAYSIZE(levels))) {
            attrs.level = levels[levelIdx];
        }

        static bool concentration = false;
        if (ImGui::Checkbox("Concentration", &concentration)) {
            attrs.concentration = concentration;
        }

        static bool ritual = false;
        if (ImGui::Checkbox("Ritual", &ritual)) {
            attrs.ritual = ritual;
        }

        if (ImGui::Button("Generate Glyph")) {
            writer.createGlyph(attrs);
        }

        ImGui::End();

        window.clear(sf::Color::White);
        writer.draw(window);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
