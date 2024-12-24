#pragma once
#include "PhysicsManager.h"

using namespace std;

class TextureManager
{
private:
	static TextureManager* instance;
	vector<sf::Texture> goombaTextures = vector<sf::Texture>(3);
	vector<sf::Texture> koopaTextures = vector<sf::Texture>(8);
	vector<sf::Texture> bowserTextures = vector<sf::Texture>(10);

	TextureManager();

	TextureManager(const TextureManager&) = delete;

	TextureManager& operator=(TextureManager) = delete;

public:
	static TextureManager* getInstance();

	sf::Texture& getGoombaTexture(int i);

	sf::Texture& getKoopaTexture(int i);

	sf::Texture& getBowserTexture(int i);
};



class Enemy : public PhysicsAppliedObject
{
protected:
	TextureManager* textureManager = TextureManager::getInstance();

	int currentTexture = 0;
	chrono::high_resolution_clock::time_point lastUpdate = chrono::high_resolution_clock::now();
	const chrono::milliseconds updateInterval{ 100 };

public:
	virtual void update(float deltaTime, Map map) = 0;

	virtual ~Enemy() = default;
};

class Goomba : public Enemy
{
public:
	Goomba();

	void update(float deltaTime, Map map) override;
};

class Koopa : public Enemy
{
private:
	bool rolling = 0;
	chrono::high_resolution_clock::time_point rollPoint;

public:
	void update(float deltaTime, Map map) override;

	void startRolling();
};

class Bowser : public Enemy
{
public:
	void update(float deltaTime, Map map) override;
};

class EnemyFactory
{
public:
	virtual Enemy* create() = 0;

	virtual ~EnemyFactory() = default;
};

class GoombaFactory : public EnemyFactory
{
public:
	Enemy* create() override;
};

class KoopaFactory : public EnemyFactory
{
public:
	Enemy* create() override;
};

class BowserFactory : public EnemyFactory
{
public:
	Enemy* create() override;
};