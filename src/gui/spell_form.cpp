#include "gui/spell_form.h"
#include "config.h"
#include "resource_manager.h"
#include <nlohmann/json.hpp>
#include <fstream>

SpellForm::SpellForm(sf::RenderWindow& window) : window(window) {
    initializeControls();
    loadAttributes();
}

void SpellForm::initializeControls() {
    float startX = Config::PADDING;
    float startY = Config::PADDING;
    float dropdownHeight = Config::BUTTON_HEIGHT;
    
    // Initialize dropdowns
    levelDropdown = std::make_unique<GUI::Dropdown>(
        sf::Vector2f(startX, startY),
        sf::Vector2f(Config::DROPDOWN_WIDTH, dropdownHeight)
    );
    
    schoolDropdown = std::make_unique<GUI::Dropdown>(
        sf::Vector2f(startX + Config::DROPDOWN_WIDTH + Config::PADDING, startY),
        sf::Vector2f(Config::DROPDOWN_WIDTH, dropdownHeight)
    );
    
    // Initialize remaining dropdowns with appropriate positioning
    
    // Initialize checkboxes
    float checkY = startY + 3 * (dropdownHeight + Config::PADDING);
    concentrationCheck = std::make_unique<GUI::Checkbox>(
        sf::Vector2f(startX, checkY),
        "Concentration"
    );
    
    ritualCheck = std::make_unique<GUI::Checkbox>(
        sf::Vector2f(startX + 150.f, checkY),
        "Ritual"
    );
    
    // Initialize buttons
    float buttonY = checkY + Config::BUTTON_HEIGHT + Config::PADDING;
    generateButton = std::make_unique<GUI::Button>(
        sf::Vector2f(startX, buttonY),
        sf::Vector2f(Config::BUTTON_WIDTH, Config::BUTTON_HEIGHT),
        "Generate Glyph"
    );
    
    randomButton = std::make_unique<GUI::Button>(
        sf::Vector2f(startX + Config::BUTTON_WIDTH + Config::PADDING, buttonY),
        sf::Vector2f(Config::BUTTON_WIDTH, Config::BUTTON_HEIGHT),
        "Random Spell"
    );
    
    saveButton = std::make_unique<GUI::Button>(
        sf::Vector2f(startX + 2 * (Config::BUTTON_WIDTH + Config::PADDING), buttonY),
        sf::Vector2f(Config::BUTTON_WIDTH, Config::BUTTON_HEIGHT),
        "Save Glyph"
    );
}

void SpellForm::loadAttributes() {
    std::ifstream file(Config::ATTRIBUTES_FILE);
    nlohmann::json attributes = nlohmann::json::parse(file);
    
    levelDropdown->setOptions(attributes["levels"]);
    schoolDropdown->setOptions(attributes["schools"]);
    durationDropdown->setOptions(attributes["durations"]);
    rangeDropdown->setOptions(attributes["ranges"]);
    areaDropdown->setOptions(attributes["area_types"]);
    dtypeDropdown->setOptions(attributes["damage_types"]);
    conditionDropdown->setOptions(attributes["conditions"]);
}

void SpellForm::draw() {
    levelDropdown->draw(window);
    schoolDropdown->draw(window);
    durationDropdown->draw(window);
    rangeDropdown->draw(window);
    areaDropdown->draw(window);
    dtypeDropdown->draw(window);
    conditionDropdown->draw(window);
    shapeDropdown->draw(window);
    lineTypeDropdown->draw(window);
    
    concentrationCheck->draw(window);
    ritualCheck->draw(window);
    
    generateButton->draw(window);
    randomButton->draw(window);
    saveButton->draw(window);
}

SpellAttributes SpellForm::getAttributes() const {
    return SpellAttributes{
        levelDropdown->getSelectedOption(),
        schoolDropdown->getSelectedOption(),
        durationDropdown->getSelectedOption(),
        rangeDropdown->getSelectedOption(),
        areaDropdown->getSelectedOption(),
        dtypeDropdown->getSelectedOption(),
        conditionDropdown->getSelectedOption(),
        concentrationCheck->isChecked(),
        ritualCheck->isChecked()
    };
}
