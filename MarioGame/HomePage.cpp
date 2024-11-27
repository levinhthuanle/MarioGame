#include "HomePage.h"
#include "SoundManager.h"
void HomePage::loadResources()
{


    m_startButton.loadButton("./Resources/Background/PagesBackground/StartButton.png");
    m_settingButton.loadButton("./Resources/Background/PagesBackground/SettingButton.png");
    m_informationButton.loadButton("./Resources/Background/PagesBackground/InformationButton.png");
}

int HomePage::loadPage()
{
    sf::RenderWindow& window = ResourcesManager::getInstance().getWindow();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 4;
            }

            if (m_startButton.isClicked(window, event)) {
                std::cout << "Start Button clicked\n";
                return 3;
            }
            if (m_startButton.isHover(window)) {
                m_startButton.setOpacity(255);
            }
            else {
                m_startButton.setOpacity(127);
            }

            if (m_settingButton.isClicked(window, event)) {
                std::cout << "Setting Button clicked\n";
                return 2;
            }
            if (m_settingButton.isHover(window)) {
                m_settingButton.setOpacity(255);
            }
            else {
                m_settingButton.setOpacity(127);
            }

            if (m_informationButton.isClicked(window, event)) {
                std::cout << "information Button clicked\n";
                return 1;
            }
            if (m_informationButton.isHover(window)) {
                m_informationButton.setOpacity(255);
            }
            else {
                m_informationButton.setOpacity(127);
            }
        }

        window.clear(sf::Color::Black);
        
        window.draw(m_backgroundSprite);
        m_startButton.draw(window, 700.f, 250.f);
        m_settingButton.draw(window, 700.f, 400.f);
        m_informationButton.draw(window, 700.f, 550.f);
        window.display();
    }
    return 0;
}
