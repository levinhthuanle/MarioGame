#pragma once

#include "Components.h"


class BasePage
{
public:
	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;


public:
	BasePage() {
		if (!m_backgroundTexture.loadFromFile("./Resources/Background/PagesBackground/HomePageBackground.png")) {
			std::cerr << "Can not load background Texture \n";
			return;
		}

		m_backgroundSprite.setTexture(m_backgroundTexture);
	}

	virtual void loadResources() = 0;

	virtual int loadPage() = 0;


};

