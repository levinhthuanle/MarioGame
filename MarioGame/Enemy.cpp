#include "Enemy.h"
#include "ResourcesManager.h"
TextureManager* TextureManager::getInstance()
{
	if (!instance)
		instance = new TextureManager();
	return instance;
}

void TextureManager::loadTextures()
{
	goombaTextures[0].loadFromFile("./Resources/Enemy/Goombas/Normal/walk.png", sf::IntRect(2, 2, 16, 16));
	goombaTextures[1].loadFromFile("./Resources/Enemy/Goombas/Normal/walk.png", sf::IntRect(21, 2, 16, 16));
	goombaTextures[2].loadFromFile("./Resources/Enemy/Goombas/Normal/die.png", sf::IntRect(2, 2, 16, 16));

	koopaTextures[0].loadFromFile("./Resources/Enemy/Koopas/Normal/walk.png", sf::IntRect(2, 3, 16, 23));
	koopaTextures[1].loadFromFile("./Resources/Enemy/Koopas/Normal/walk.png", sf::IntRect(21, 2, 16, 24));
	koopaTextures[2].loadFromFile("./Resources/Enemy/Koopas/Normal/shelled.png", sf::IntRect(2, 12, 16, 14));
	koopaTextures[3].loadFromFile("./Resources/Enemy/Koopas/Normal/shelled.png", sf::IntRect(21, 12, 16, 14));
	koopaTextures[4].loadFromFile("./Resources/Enemy/Koopas/Normal/roll.png", sf::IntRect(2, 12, 16, 14));
	koopaTextures[5].loadFromFile("./Resources/Enemy/Koopas/Normal/roll.png", sf::IntRect(21, 12, 16, 14));
	koopaTextures[6].loadFromFile("./Resources/Enemy/Koopas/Normal/roll.png", sf::IntRect(40, 12, 16, 14));
	koopaTextures[7].loadFromFile("./Resources/Enemy/Koopas/Normal/roll.png", sf::IntRect(59, 12, 16, 14));
}

sf::Texture& TextureManager::getGoombaTexture(int i)
{
	return goombaTextures[i];
}

sf::Texture& TextureManager::getKoopaTexture(int i)
{
	return koopaTextures[i];
}

sf::Texture& TextureManager::getBowserTexture(int i)
{
	return bowserTextures[i];
}

Goomba::Goomba()
{
	velocity.x = 250;
	velocity.y = 0;
	m_sprite.setTexture(textureManager->getGoombaTexture(0));
}

void Goomba::update(float deltaTime, Map map)
{
	velocity.y += gravity * deltaTime;

	vector<vector<GameObject*>>& objMap = ResourcesManager::getInstance().getObjMap();
	Map& mapData = ResourcesManager::getInstance().getMap();

	vector<vector<Sprite*>>& mapSprites = mapData.getSpriteGrid();

	int x1 = round(m_sprite.getPosition().x / 54.4);
	int y1 = round(m_sprite.getPosition().y / 54.4);
	objMap[x1][y1] = nullptr;

	std::pair<int, int> nothing = { 0, 0 };
	int collision = checkObstacle(deltaTime, map, nothing);
	if (collision == 1 or collision == 11)
		velocity.x = -250;
	else if (collision == 2 or collision == 12)
		velocity.x = 250;

	chrono::time_point<chrono::high_resolution_clock> now = chrono::high_resolution_clock::now();
	if (now - lastUpdate >= updateInterval) {
		lastUpdate = now;

		currentTexture = (currentTexture + 1) % 2;

		m_sprite.setTexture(textureManager->getGoombaTexture(currentTexture));
	}

	m_sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);
	int x2 = round(m_sprite.getPosition().x / 54.4);
	int y2 = round(m_sprite.getPosition().y / 54.4);
	objMap[x2][y2] = this;
	swap(mapSprites[x1][y1], mapSprites[x2][y2]);
}

void Koopa::update(float deltaTime, Map map)
{
	velocity.y += gravity * deltaTime;

	vector<vector<GameObject*>>& objMap = ResourcesManager::getInstance().getObjMap();
	Map& mapData = ResourcesManager::getInstance().getMap();

	vector<vector<Sprite*>>& mapSprites = mapData.getSpriteGrid();

	int x1 = round(m_sprite.getPosition().x / 54.4);
	int y1 = round(m_sprite.getPosition().y / 54.4);
	objMap[x1][y1] = nullptr;

	std::pair<int, int> nothing = { 0, 0 };
	int collision = checkObstacle(deltaTime, map, nothing);

	if (rolling) {
		chrono::time_point<chrono::high_resolution_clock> now = chrono::high_resolution_clock::now();
		if (now - rollPoint >= chrono::milliseconds(5000))
			rolling = false;
	}

	if (!rolling) {
		if (collision == 1 or collision == 11)
			velocity.x = -280;
		else if (collision == 2 or collision == 12)
			velocity.x = 280;
	}
	else {
		if (collision == 1 or collision == 11)
			velocity.x = -400;
		else if (collision == 2 or collision == 12)
			velocity.x = 400;
	}

	chrono::time_point<chrono::high_resolution_clock> now = chrono::high_resolution_clock::now();
	if (now - lastUpdate >= updateInterval) {
		lastUpdate = now;

		if (!rolling) {
			currentTexture = (currentTexture + 1) % 2;
			m_sprite.setTexture(textureManager->getKoopaTexture(currentTexture));
		}
		else {
			currentTexture = (currentTexture + 1) % 4;
			m_sprite.setTexture(textureManager->getKoopaTexture(currentTexture + 4));
		}
	}

	m_sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);
	int x2 = round(m_sprite.getPosition().x / 54.4);
	int y2 = round(m_sprite.getPosition().y / 54.4);
	objMap[x2][y2] = this;
	mapSprites[x2][y2] = mapSprites[x1][y1];
	mapSprites[x1][y1] = nullptr;
}

void Koopa::startRolling()
{
	rolling = true;
	rollPoint = chrono::high_resolution_clock::now();
}

Enemy* GoombaFactory::create()
{
	return new Goomba();
}

Enemy* KoopaFactory::create()
{
	return new Koopa();
}