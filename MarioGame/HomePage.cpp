#include "HomePage.h"

int HomePage::loadPage()
{
    sf::RenderWindow& window = ResourcesManager::getInstance().getWindow();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        window.display();
    }
    return 0;
}
