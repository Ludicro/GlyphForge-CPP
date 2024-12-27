#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include <string>

class ResourceManager {
public:
    static ResourceManager& getInstance() {
        static ResourceManager instance;
        return instance;
    }

    // Texture management
    sf::Texture& getTexture(const std::string& filename);
    void unloadTexture(const std::string& filename);

    // Font management
    sf::Font& getFont(const std::string& filename);
    void unloadFont(const std::string& filename);

    // Binary data management
    std::vector<char>& getBinaryData(const std::string& filename);
    void unloadBinaryData(const std::string& filename);

    // Resource clearing
    void clearAll();
    void clearTextures();
    void clearFonts();
    void clearBinaryData();

private:
    ResourceManager() = default;
    ~ResourceManager() = default;

    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;
    std::unordered_map<std::string, std::unique_ptr<sf::Font>> fonts;
    std::unordered_map<std::string, std::vector<char>> binaryData;

    // Prevent copying
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
};

#endif // RESOURCE_MANAGER_H
