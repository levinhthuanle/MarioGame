#include "Game.h"

Game::Game()
{
	m_IsRunning = true;
}

void Game::run()
{
	while (m_IsRunning) {
		m_PageManager.loadPage();
	}
}
