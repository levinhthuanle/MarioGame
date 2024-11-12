#pragma once
#include "BasePage.h"
#include "ResourcesManager.h"
class HomePage : public BasePage
{
public:
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

