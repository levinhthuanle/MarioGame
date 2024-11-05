#pragma once
#include "BasePage.h"
#include "Global.h"
class HomePage : public BasePage
{
public:
	HomePage() {
		loadResources();
	}

	void loadResources() override {
		// Load the assets
	}

	int loadPage() override;
};

