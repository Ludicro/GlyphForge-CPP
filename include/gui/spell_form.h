#ifndef SPELL_FORM_H
#define SPELL_FORM_H

#include "gui/controls.h"
#include "spell_data.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class SpellForm {
public:
    SpellForm(sf::RenderWindow& window);
    
    void update();
    void draw();
    bool handleEvent(const sf::Event& event);
    SpellAttributes getAttributes() const;
    
private:
    sf::RenderWindow& window;
    
    // GUI Controls
    std::unique_ptr<GUI::Dropdown> levelDropdown;
    std::unique_ptr<GUI::Dropdown> schoolDropdown;
    std::unique_ptr<GUI::Dropdown> durationDropdown;
    std::unique_ptr<GUI::Dropdown> rangeDropdown;
    std::unique_ptr<GUI::Dropdown> areaDropdown;
    std::unique_ptr<GUI::Dropdown> dtypeDropdown;
    std::unique_ptr<GUI::Dropdown> conditionDropdown;
    std::unique_ptr<GUI::Dropdown> shapeDropdown;
    std::unique_ptr<GUI::Dropdown> lineTypeDropdown;
    
    std::unique_ptr<GUI::Checkbox> concentrationCheck;
    std::unique_ptr<GUI::Checkbox> ritualCheck;
    
    std::unique_ptr<GUI::Button> generateButton;
    std::unique_ptr<GUI::Button> randomButton;
    std::unique_ptr<GUI::Button> saveButton;
    
    void initializeControls();
    void loadAttributes();
};

#endif // SPELL_FORM_H
