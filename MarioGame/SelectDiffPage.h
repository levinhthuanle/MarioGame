#pragma once
#include "Components.h"
#include "BasePage.h"
#include "ResourcesManager.h"
class SelectDiffPage : public BasePage
{
public:
	Button m_easyButton;
	Button m_mediumButton;
	Button m_hardButton;
	Button m_customButton;
	Button m_gobackButton;

	Button m_level1Button;
	Button m_level2Button;
	Button m_level3Button;
public:
	SelectDiffPage() {
		loadResources();
	}

	void loadResources() override;

	int loadPage() override;

	int selectLevel(int diff);

	int selectCharacter();
};

