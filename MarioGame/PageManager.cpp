#include "PageManager.h"

void PageManager::loadPage()
{
	if (m_currentPage == 0)
		m_currentPage = m_homePage.loadPage();

	/*if (m_currentPage == 1)
		m_currentPage = m_GameInformationPage.loadPage();*/
}
