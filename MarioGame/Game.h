#pragma once
#include "PageManager.h"
class Game
{
public:
	bool m_IsRunning;
	PageManager m_PageManager;
	// Level Manager

public:

	Game();

	void run();
};

