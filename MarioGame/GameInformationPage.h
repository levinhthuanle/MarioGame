#pragma once
#include "BasePage.h"
#include "ResourcesManager.h"
class GameInformationPage: public BasePage
{
public:
	sf::Texture textTexture;
	sf::Sprite textSprite;
	Button m_gobackButton;
public:
	GameInformationPage() {
		loadResources();
	}

	void loadResources() override;

	int loadPage() override;
};

