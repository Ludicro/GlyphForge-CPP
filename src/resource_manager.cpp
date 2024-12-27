#include "resource_manager.h"
#include "error_handling.h"
#include "logger.h"
#include <fstream>

sf::Texture& ResourceManager::getTexture(const std::string& filename) {
    auto it = textures.find(filename);
    if (it != textures.end()) {
        return *it->second;
    }

    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filename)) {
        LOG_ERROR("Failed to load texture: " + filename);
        throw FileError(filename);
    }

    LOG_INFO("Loaded texture: " + filename);
    textures[filename] = std::move(texture);
    return *textures[filename];
}

sf::Font& ResourceManager::getFont(const std::string& filename) {
    auto it = fonts.find(filename);
    if (it != fonts.end()) {
        return *it->second;
    }

    auto font = std::make_unique<sf::Font>();
    if (!font->loadFromFile(filename)) {
        LOG_ERROR("Failed to load font: " + filename);
        throw FileError(filename);
    }

    LOG_INFO("Loaded font: " + filename);
    fonts[filename] = std::move(font);
    return *fonts[filename];
}

std::vector<char>& ResourceManager::getBinaryData(const std::string& filename) {
    auto it = binaryData.find(filename);
    if (it != binaryData.end()) {
        return it->second;
    }

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        LOG_ERROR("Failed to load binary data: " + filename);
        throw FileError(filename);
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size)) {
        LOG_ERROR("Failed to read binary data: " + filename);
        throw FileError(filename);
    }

    LOG_INFO("Loaded binary data: " + filename);
    binaryData[filename] = std::move(buffer);
    return binaryData[filename];
}

void ResourceManager::unloadTexture(const std::string& filename) {
    textures.erase(filename);
    LOG_INFO("Unloaded texture: " + filename);
}

void ResourceManager::unloadFont(const std::string& filename) {
    fonts.erase(filename);
    LOG_INFO("Unloaded font: " + filename);
}

void ResourceManager::unloadBinaryData(const std::string& filename) {
    binaryData.erase(filename);
    LOG_INFO("Unloaded binary data: " + filename);
}

void ResourceManager::clearAll() {
    clearTextures();
    clearFonts();
    clearBinaryData();
    LOG_INFO("Cleared all resources");
}

void ResourceManager::clearTextures() {
    textures.clear();
    LOG_INFO("Cleared all textures");
}

void ResourceManager::clearFonts() {
    fonts.clear();
    LOG_INFO("Cleared all fonts");
}

void ResourceManager::clearBinaryData() {
    binaryData.clear();
    LOG_INFO("Cleared all binary data");
}
