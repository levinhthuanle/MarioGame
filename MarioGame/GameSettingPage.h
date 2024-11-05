#pragma once
#include "BasePage.h"
class GameSettingPage : public BasePage
{
public:
	GameSettingPage() {
		loadResources();
	}

	void loadResources() override {

	}

	int loadPage() override {
		system("cls");
		std::cout << "Game Setting Page" << std::endl;

		return 0;
	}
};

