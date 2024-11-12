#pragma once
#include "BasePage.h"
#include "ResourcesManager.h"
class HomePage : public BasePage
{
public:
	sf::Texture m_startButtonTexture;
	sf::Sprite m_startButtonSprite;
	sf::Texture m_settingButtonTexture;
	sf::Sprite m_settingButtonSprite;
	sf::Texture m_informationButtonTexture;
	sf::Sprite m_informationButtonSprite;

	Button m_startButton;
	Button m_settingButton;
	Button m_informationButton;

public: 

	HomePage() {
		loadResources();
	}

	void loadResources() override;


	int loadPage() override;


};

