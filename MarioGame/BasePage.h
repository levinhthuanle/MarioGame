#pragma once
#include <iostream>
class BasePage
{
public:
	BasePage() {}

	virtual void loadResources() = 0;

	virtual int loadPage() = 0;


};

