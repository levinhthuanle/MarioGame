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
public:
	SelectDiffPage() {
		loadResources();
	}

	void loadResources() override;

	int loadPage() override;
};

