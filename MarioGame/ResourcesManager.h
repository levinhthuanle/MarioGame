#pragma once
// Singleton
// Manage all the global resources, including: renderwindow, fonts
#include "Global.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "Map.h"

class ResourcesManager {
public:
    static ResourcesManager& getInstance() {
        static ResourcesManager instance;
        return instance;
    }

    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager& operator=(const ResourcesManager&) = delete;


public:
    vector<vector<GameObject*>> objMap;
    sf::Font default_font;
    sf::RenderWindow window;
    Map map;

    bool loadFont();
    
    sf::RenderWindow& getWindow();
    
    Map &getMap();
    vector<vector<GameObject*>>& getObjMap() {
        return objMap;
    }
    sf::Font& getFont(const std::string& name);

private:
    ResourcesManager() {} 
};
