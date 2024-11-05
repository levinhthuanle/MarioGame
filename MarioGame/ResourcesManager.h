#pragma once
// Singleton
// Manage all the global resources, including: renderwindow, fonts
#include "Global.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class ResourcesManager {
public:
    static ResourcesManager& getInstance() {
        static ResourcesManager instance;
        return instance;
    }

    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager& operator=(const ResourcesManager&) = delete;


public:
    sf::Font default_font;
    sf::RenderWindow window;

    bool loadFont();
    
    sf::RenderWindow& getWindow();
    sf::Font& getFont(const std::string& name);

private:
    ResourcesManager() {} 
};
