#pragma once
#include "BasePage.h"
#include "ResourcesManager.h"
class GameSettingPage : public BasePage
{
public:
	Button m_gobackButton;
public:
	GameSettingPage() {
		loadResources();
	}

	void loadResources();

	int loadPage() override;
};

