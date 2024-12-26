#include "ResourcesManager.h"


bool ResourcesManager::loadFont()
{
    if (!default_font.loadFromFile(ARIAL_PATH)) 
        return false;

       return true;
}

sf::RenderWindow& ResourcesManager::getWindow()
{
    if (!window.isOpen()) {
        window.create(sf::VideoMode(WIDTH, HEIGHT), "Mario Game", sf::Style::Titlebar | sf::Style::Close);

    }
    return window;
}

Map& ResourcesManager::getMap()
{
    return map;
}

sf::Font& ResourcesManager::getFont(const std::string& name)
{
    return default_font;
}
