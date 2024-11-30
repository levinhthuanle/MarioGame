#pragma once
#include <SFML\Graphics.hpp>
#include "HomePage.h"
#include "GameInformationPage.h"
#include "GameSettingPage.h"
#include "SelectDiffPage.h"
#include "Level.h"
class PageManager
{
public:
	int m_currentCharacter = 1; // 1 for Mario and 2 for Luigi
	std::string m_currentHard = "1-1";

	int m_currentPage = 0;
	HomePage m_homePage;
	GameInformationPage m_GameInformationPage;
	GameSettingPage m_GameSettingPage;
	SelectDiffPage m_SelectDiffPage;
	Level level;

public:
	PageManager() {
		m_currentPage = 0;
	}

	int loadPage();
};

