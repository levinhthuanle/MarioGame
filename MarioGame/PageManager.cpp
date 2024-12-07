#include "PageManager.h"

int PageManager::loadPage()
{
	if (m_currentPage == 0)
		m_currentPage = m_homePage.loadPage();

	if (m_currentPage == 1)
		m_currentPage = m_GameInformationPage.loadPage();

	if (m_currentPage == 2)
		m_currentPage = m_GameSettingPage.loadPage();

	if (m_currentPage == 3)
		m_currentPage = m_SelectDiffPage.loadPage();

	if (m_currentPage == 4)
		return 0;

	// Easy 1.1 
	if (m_currentPage == 5)
		level.run("1-1");

	// For the m_currentPage >= 10. It's for the play game page
	// 10 for 1-1; 11 for 1-2 and so on.

	// This switch case will navigate to the play game page with the diff as an argument
	switch (m_currentPage)
	{
	case 11:
		m_currentPage = level.run("1-1");
		break;
	case 12:
		m_currentPage = level.run("1-2");
		break;
	case 13:
		m_currentPage = level.run("1-3");
		break;
	case 14:
		m_currentPage = level.run("2-1");
		break;
	case 15:
		m_currentPage = level.run("2-2");
		break;
	case 16:
		m_currentPage = level.run("2-3");
		break;
	case 17:
		m_currentPage = level.run("3-1");
		break;
	case 18:
		m_currentPage = level.run("3-2");
		break;
	case 19:
		m_currentPage = level.run("3-3");
		break;

	default:
		break;
	}

	return 1;
}
