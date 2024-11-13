#pragma once
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include "SFML/Audio.hpp"
#include <experimental/filesystem>
#include <map>

using namespace std;

// Singleton
class SoundManager
{
private:
	static SoundManager* instance;
	map<string, sf::SoundBuffer> buffers;
	map<string, sf::Sound> sounds;
	sf::Music background;

	SoundManager() = default;

	SoundManager(const SoundManager&) = delete;

	SoundManager& operator=(SoundManager) = delete;

public:
	static SoundManager* getInstance();

	void playBackground();

	void stopBackground();

	void loadSound(const string& soundName, string path);

	void loadSounds();

	void playSound(const string& soundName);

	void playSoundGameOver();

	void playSoundMarioDie();

	void playSoundStageClear();

	void playSoundWarning();

	void playSoundWorldClear();

	void playSound1up();

	void playSoundBowserFalls();

	void playSoundBowserFire();

	void playSoundBreakBlock();

	void playSoundBump();

	void playSoundCoin();

	void playSoundFireBall();

	void playSoundFireworks();

	void playSoundFlagpole();

	void playSoundJumpSmall();

	void playSoundJumpSuper();

	void playSoundKick();

	void playSoundPause();

	void playSoundPipe();

	void playSoundPowerUp();

	void playSoundPowerUpAppears();

	void playSoundStomp();

	void playSoundVine();
};

