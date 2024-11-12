#include "Game.h"

Game::Game()
{
	m_IsRunning = true;
}

void Game::run()
{
	std::cout << "Run game\n";
	while (m_IsRunning) {
		m_IsRunning = m_PageManager.loadPage();
	}
}
