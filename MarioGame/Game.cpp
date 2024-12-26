#include "Game.h"

SoundManager* SoundManager::instance = nullptr;

Game::Game()
{
	m_IsRunning = true;
}

void Game::run()
{
	std::cout << "Run game\n";
	SoundManager::getInstance()->loadSounds();
	//SoundManager* soundManager = SoundManager::getInstance();
	//soundManager->playBackground();
	while (m_IsRunning) {
		m_IsRunning = m_PageManager.loadPage();
	}

	std::cout << "Game ended\n";
}
