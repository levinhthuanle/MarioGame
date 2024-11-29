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
	return 1;
}
