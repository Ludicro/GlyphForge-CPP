#include "gui/controls.h"
#include "resource_manager.h"
#include "config.h"

namespace GUI {

// Dropdown Implementation
Dropdown::Dropdown(const sf::Vector2f& position, const sf::Vector2f& size) {
    background.setPosition(position);
    background.setSize(size);
    background.setFillColor(sf::Color::White);
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(1.f);

    selectedText.setFont(ResourceManager::getInstance().getFont(Config::RESOURCE_PATH + std::string("fonts/default.ttf")));
    selectedText.setCharacterSize(14);
    selectedText.setFillColor(sf::Color::Black);
    selectedText.setPosition(position + sf::Vector2f(5.f, 5.f));
    
    isOpen = false;
}

void Dropdown::setOptions(const std::vector<std::string>& newOptions) {
    options = newOptions;
    if (!options.empty() && selectedOption.empty()) {
        selectedOption = options[0];
    }
}

void Dropdown::draw(sf::RenderWindow& window) {
    window.draw(background);
    selectedText.setString(selectedOption);
    window.draw(selectedText);

    if (isOpen) {
        // Draw dropdown list
        for (size_t i = 0; i < options.size(); ++i) {
            sf::RectangleShape optionBox = background;
            optionBox.setPosition(background.getPosition() + sf::Vector2f(0, (i + 1) * background.getSize().y));
            window.draw(optionBox);

            sf::Text optionText = selectedText;
            optionText.setString(options[i]);
            optionText.setPosition(optionBox.getPosition() + sf::Vector2f(5.f, 5.f));
            window.draw(optionText);
        }
    }
}

// Button Implementation
Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& buttonText) {
    shape.setPosition(position);
    shape.setSize(size);
    shape.setFillColor(sf::Color::White);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1.f);

    text.setFont(ResourceManager::getInstance().getFont(Config::RESOURCE_PATH + std::string("fonts/default.ttf")));
    text.setString(buttonText);
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::Black);
    
    // Center text in button
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        position.x + (size.x - textBounds.width) / 2,
        position.y + (size.y - textBounds.height) / 2
    );
    
    isHovered = false;
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

// Checkbox Implementation
Checkbox::Checkbox(const sf::Vector2f& position, const std::string& checkboxLabel) {
    box.setPosition(position);
    box.setSize(sf::Vector2f(20.f, 20.f));
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(1.f);

    label.setFont(ResourceManager::getInstance().getFont(Config::RESOURCE_PATH + std::string("fonts/default.ttf")));
    label.setString(checkboxLabel);
    label.setCharacterSize(14);
    label.setFillColor(sf::Color::Black);
    label.setPosition(position + sf::Vector2f(30.f, 0.f));
    
    checked = false;
}

void Checkbox::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(label);
    
    if (checked) {
        sf::RectangleShape checkmark;
        checkmark.setPosition(box.getPosition() + sf::Vector2f(4.f, 4.f));
        checkmark.setSize(sf::Vector2f(12.f, 12.f));
        checkmark.setFillColor(sf::Color::Black);
        window.draw(checkmark);
    }
}
