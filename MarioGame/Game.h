#pragma once

#include "PageManager.h"
class Game
{
public:
	bool m_IsRunning;
	int m_CurrentPage;
	PageManager m_PageManager;

public:

	Game();

	void run();
};

