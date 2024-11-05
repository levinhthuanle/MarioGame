#pragma once
#include "BasePage.h"
class GameInformationPage: public BasePage
{
public:
	GameInformationPage() {
		loadResources();
	}

	void loadResources() override {

	}

	int loadPage() override {
		system("cls");
		std::cout << "Game Information Page" << std::endl;

		return 0;
	}
};

