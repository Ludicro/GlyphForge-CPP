#ifndef CONTROLS_H
#define CONTROLS_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include <vector>

namespace GUI {

class Dropdown {
public:
    Dropdown(const sf::Vector2f& position, const sf::Vector2f& size);
    void setOptions(const std::vector<std::string>& options);
    void setSelectedOption(const std::string& option);
    std::string getSelectedOption() const;
    void draw(sf::RenderWindow& window);
    bool handleEvent(const sf::Event& event);

private:
    sf::RectangleShape background;
    sf::Text selectedText;
    std::vector<std::string> options;
    std::string selectedOption;
    bool isOpen;
};

class Button {
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text);
    void setCallback(std::function<void()> callback);
    void draw(sf::RenderWindow& window);
    bool handleEvent(const sf::Event& event);

private:
    sf::RectangleShape shape;
    sf::Text text;
    std::function<void()> callback;
    bool isHovered;
};

class Checkbox {
public:
    Checkbox(const sf::Vector2f& position, const std::string& label);
    void setChecked(bool checked);
    bool isChecked() const;
    void draw(sf::RenderWindow& window);
    bool handleEvent(const sf::Event& event);

private:
    sf::RectangleShape box;
    sf::Text label;
    bool checked;
};

} // namespace GUI

#endif // CONTROLS_H
