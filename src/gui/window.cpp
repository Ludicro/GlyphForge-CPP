#include "gui/window.h"
#include <fstream>
#include <random>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

SpellApp::SpellApp() : window(sf::VideoMode(800, 600), "Spell Generator") {
    ImGui::SFML::Init(window);
    loadAttributes();
    
    // Set default selections
    currentLevel = "None";
    currentSchool = "None";
    currentDuration = "Instantaneous";
    currentRange = "None";
    currentArea = "None";
    currentDtype = "None";
    currentCondition = "None";
    concentration = false;
    ritual = false;
}

void SpellApp::loadAttributes() {
    std::ifstream f("resources/attributes.json");
    json data = json::parse(f);
    
    levels = data["levels"].get<std::vector<std::string>>();
    schools = data["schools"].get<std::vector<std::string>>();
    durations = data["durations"].get<std::vector<std::string>>();
    ranges = data["ranges"].get<std::vector<std::string>>();
    areas = data["area_types"].get<std::vector<std::string>>();
    dtypes = data["damage_types"].get<std::vector<std::string>>();
    conditions = data["conditions"].get<std::vector<std::string>>();
}

void SpellApp::run() {
    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());
        
        createGUI();
        
        window.clear();
        window.draw(imageSprite);
        ImGui::SFML::Render(window);
        window.display();
    }
    
    ImGui::SFML::Shutdown();
}

void SpellApp::createGUI() {
    ImGui::Begin("Spell Generator");
    
    if (ImGui::BeginCombo("Level", currentLevel.c_str())) {
        for (const auto& level : levels) {
            if (ImGui::Selectable(level.c_str(), currentLevel == level))
                currentLevel = level;
        }
        ImGui::EndCombo();
    }
    
    // Similar combo boxes for other attributes
    
    ImGui::Checkbox("Concentration", &concentration);
    ImGui::Checkbox("Ritual", &ritual);
    
    if (ImGui::Button("Generate Glyph"))
        generateSpell();
        
    if (ImGui::Button("Random Spell"))
        randomSpell();
        
    if (ImGui::Button("Save Image"))
        saveImage();
    
    ImGui::End();
}

void SpellApp::generateSpell() {
    Writer writer;
    SpellAttributes attrs{
        currentLevel,
        currentSchool,
        currentDuration,
        currentRange,
        currentArea,
        currentDtype,
        currentCondition,
        concentration,
        ritual
    };
    
    sf::Image glyphImage = writer.createGlyph(attrs);
    displayImage(glyphImage);
    
    // Check for matching spell
    std::string matchingSpell = writer.findMatchingSpell(attrs);
    if (!matchingSpell.empty()) {
        // Display matching spell name using ImGui
        ImGui::Text("Matching Spell: %s", matchingSpell.c_str());
    } else {
        ImGui::Text("Spell does not exist... yet");
    }
}

void SpellApp::randomSpell() {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    auto randomElement = [&gen](const std::vector<std::string>& vec) {
        std::uniform_int_distribution<> dis(0, vec.size() - 1);
        return vec[dis(gen)];
    };
    
    currentLevel = randomElement(levels);
    currentSchool = randomElement(schools);
    currentDuration = randomElement(durations);
    currentRange = randomElement(ranges);
    currentArea = randomElement(areas);
    currentDtype = randomElement(dtypes);
    currentCondition = randomElement(conditions);
    
    concentration = std::uniform_int_distribution<>(0, 1)(gen);
    ritual = std::uniform_int_distribution<>(0, 1)(gen);
    
    generateSpell();
}

void SpellApp::saveImage() {
    if (!currentImage.getSize().x || !currentImage.getSize().y)
        return;
        
    nfdchar_t *outPath = nullptr;
    nfdresult_t result = NFD_SaveDialog("png", nullptr, &outPath);
    
    if (result == NFD_OKAY) {
        sf::Image img = currentImage.copyToImage();
        img.saveToFile(outPath);
        free(outPath);
    }
}

void SpellApp::displayImage(const sf::Image& image) {
    currentImage.loadFromImage(image);
    imageSprite.setTexture(currentImage);
    
    // Center the sprite
    float scaleX = window.getSize().x / static_cast<float>(currentImage.getSize().x);
    float scaleY = window.getSize().y / static_cast<float>(currentImage.getSize().y);
    float scale = std::min(scaleX, scaleY) * 0.8f;
    
    imageSprite.setScale(scale, scale);
    imageSprite.setPosition(
        (window.getSize().x - imageSprite.getGlobalBounds().width) / 2,
        (window.getSize().y - imageSprite.getGlobalBounds().height) / 2
    );
}
