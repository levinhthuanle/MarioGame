#include "GameInformationPage.h"

void GameInformationPage::loadResources()
{
    if (!textTexture.loadFromFile("./Resources/Background/PagesBackground/text.png")) {
        std::cerr << "Can not load text Information Texture \n";
        return;
    }

    textSprite.setTexture(textTexture);
    textSprite.setPosition(100, 200);

	m_gobackButton.loadButton("./Resources/Background/PagesBackground/GobackButton.png");
}

int GameInformationPage::loadPage()
{
    sf::RenderWindow& window = ResourcesManager::getInstance().getWindow();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 4;
            }

            if (m_gobackButton.isClicked(window, event)) {
                std::cout << "Go back Button clicked\n";
                return 0;
            }
            if (m_gobackButton.isHover(window)) {
                m_gobackButton.setOpacity(255);
            }
            else {
                m_gobackButton.setOpacity(127);
            }
        }

        window.clear(sf::Color::Black);

        window.draw(m_backgroundSprite);
        window.draw(textSprite);
        m_gobackButton.draw(window, 700.f, 700.f);
        window.display();
    }
    return 0;
}
