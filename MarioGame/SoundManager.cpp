#include "SoundManager.h"

using namespace std;
namespace fs = std::experimental::filesystem;

SoundManager* SoundManager::getInstance()
{
	if (!instance)
		instance = new SoundManager();
	return instance;
}

void SoundManager::playBackground()
{
	if (background.openFromFile("Resources/Sounds/Music/background.mp3")) {
		background.setLoop(true);
		background.play();
	}
}

void SoundManager::stopBackground() {
	background.stop();
}

void SoundManager::loadSound(const string& soundName, string path)
{
	sf::SoundBuffer buffer;
	if (buffer.loadFromFile(path)) {
		buffers[soundName] = buffer;
		sounds[soundName].setBuffer(buffers[soundName]);
	}
}

void SoundManager::loadSounds() {
	for (const fs::directory_entry& entry : fs::directory_iterator("Resources/Sounds/SFX")) {
		if (fs::is_regular_file(entry)) {
			string filePath = entry.path().string();
			string soundName = entry.path().stem().string();
			loadSound(soundName, filePath);
		}
	}
}

void SoundManager::playSound(const string& soundName)
{
	if (sounds.find(soundName) != sounds.end()) {
		sounds[soundName].play();
	}
}

void SoundManager::playSoundGameOver()
{
	playSound("gameover");
}

void SoundManager::playSoundMarioDie()
{
	playSound("mariodie");
}

void SoundManager::playSoundStageClear()
{
	playSound("stageclear");
}

void SoundManager::playSoundWarning()
{
	playSound("warning");
}

void SoundManager::playSoundWorldClear()
{
	playSound("worldclear");
}

void SoundManager::playSound1up()
{
	playSound("1-up");
}

void SoundManager::playSoundBowserFalls()
{
	playSound("bowserfalls");
}

void SoundManager::playSoundBowserFire()
{
	playSound("bowserfire");
}

void SoundManager::playSoundBreakBlock()
{
	playSound("breakblock");
}

void SoundManager::playSoundBump()
{
	playSound("bump");
}

void SoundManager::playSoundCoin()
{
	playSound("coin");
}

void SoundManager::playSoundFireBall()
{
	playSound("fireball");
}

void SoundManager::playSoundFireworks()
{
	playSound("fireworks");
}

void SoundManager::playSoundFlagpole()
{
	playSound("flagpole");
}

void SoundManager::playSoundJumpSmall()
{
	playSound("jump-small");
}

void SoundManager::playSoundJumpSuper()
{
	playSound("jump-super");
}

void SoundManager::playSoundKick()
{
	playSound("kick");
}

void SoundManager::playSoundPause()
{
	playSound("pause");
}

void SoundManager::playSoundPipe()
{
	playSound("pipe");
}

void SoundManager::playSoundPowerUp()
{
	playSound("powerup");
}

void SoundManager::playSoundPowerUpAppears()
{
	playSound("powerup_appears");
}

void SoundManager::playSoundStomp()
{
	playSound("stomp");
}

void SoundManager::playSoundVine()
{
	playSound("vine");
}