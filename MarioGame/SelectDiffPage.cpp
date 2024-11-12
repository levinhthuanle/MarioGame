#include "SelectDiffPage.h"

void SelectDiffPage::loadResources()
{
	m_easyButton.loadButton("./Resources/Background/PagesBackground/easyButton.png");
	m_mediumButton.loadButton("./Resources/Background/PagesBackground/mediumButton.png");
	m_hardButton.loadButton("./Resources/Background/PagesBackground/hardButton.png");
	m_customButton.loadButton("./Resources/Background/PagesBackground/customButton.png");

	m_gobackButton.loadButton("./Resources/Background/PagesBackground/GobackButton.png");
}

int SelectDiffPage::loadPage()
{
    sf::RenderWindow& window = ResourcesManager::getInstance().getWindow();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 4;
            }

            // GO BACK
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

            // EASY
            if (m_easyButton.isClicked(window, event)) {
                std::cout << "Easy Button clicked\n";
                // Add return statement
            }
            if (m_easyButton.isHover(window)) {
                m_easyButton.setOpacity(255);
            }
            else {
                m_easyButton.setOpacity(127);
            }

            // MEDIUM
            if (m_mediumButton.isClicked(window, event)) {
                std::cout << "Medium Button clicked\n";
                // Add return statement
            }
            if (m_mediumButton.isHover(window)) {
                m_mediumButton.setOpacity(255);
            }
            else {
                m_mediumButton.setOpacity(127);
            }

            // HARD
            if (m_hardButton.isClicked(window, event)) {
                std::cout << "Hard Button clicked\n";
                // Add return statement
            }
            if (m_hardButton.isHover(window)) {
                m_hardButton.setOpacity(255);
            }
            else {
                m_hardButton.setOpacity(127);
            }

            // CUSTOM
            if (m_customButton.isClicked(window, event)) {
                std::cout << "Custom Button clicked\n";
                // Add return statement
            }
            if (m_customButton.isHover(window)) {
                m_customButton.setOpacity(255);
            }
            else {
                m_customButton.setOpacity(127);
            }
        }

        window.clear(sf::Color::Black);

        window.draw(m_backgroundSprite);
        m_gobackButton.draw(window, 700.f, 700.f);

        m_easyButton.draw(window, 700.f, 220.f);
        m_mediumButton.draw(window, 700.f, 320.f);
        m_hardButton.draw(window, 700.f, 420.f);
        m_customButton.draw(window, 700.f, 520.f);
        window.display();
    }
    return 0;
}
