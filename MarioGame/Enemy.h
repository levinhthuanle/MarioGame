#pragma once
#include "PhysicsManager.h"

using namespace std;

class TextureManager
{
private:
	static TextureManager* instance;
	vector<sf::Texture> goombaTextures = vector<sf::Texture>(3);
	vector<sf::Texture> koopaTextures = vector<sf::Texture>(10);

	TextureManager() = default;

	TextureManager(const TextureManager&) = delete;

	TextureManager& operator=(TextureManager) = delete;

public:
	static TextureManager* getInstance();

	void loadTextures();

	sf::Texture& getGoombaTexture(int i);

	sf::Texture& getKoopaTexture(int i);
};



class Enemy : public PhysicsAppliedObject
{
protected:
	TextureManager* textureManager = TextureManager::getInstance();

	int currentTexture = 0;
	chrono::high_resolution_clock::time_point lastUpdate = chrono::high_resolution_clock::now();
	const chrono::milliseconds updateInterval{ 100 };

	int lastCollision = 0;

public:
	void update(float deltaTime, Map map, vector<vector<GameObject*>>& objMap, Collision* collision) = 0;

	virtual ~Enemy() = default;
};

class Goomba : public Enemy
{
private:

public:
	Goomba();

	void update(float deltaTime, Map map, vector<vector<GameObject*>>& objMap, Collision* collision) override;
};

class Koopa : public Enemy
{
private:
	bool rolling = 0;
	chrono::high_resolution_clock::time_point rollPoint;

public:
	Koopa();

	void update(float deltaTime, Map map, vector<vector<GameObject*>>& objMap, Collision* collision) override;

	bool isRolling();

	void startRolling();
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