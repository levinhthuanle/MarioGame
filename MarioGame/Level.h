#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include "Map.h"
#include "GameObject.h"
#include "Character.h"
#include "Enemy.h"

using namespace std;

class Level
{
protected:
	int lifeHealth = 2;

	int point = 0;
	// Map map;
	PhysicsManager physicsManager;
	vector<GameObject*> gameObjects;
	vector<GameObject*> bricks;
	vector<GameObject*> luckyblocks;

	vector<GameObject*> enemies;
	vector<GameObject*> items;

	Character* character = nullptr;

	sf::Sprite bg_sprite;

public:
	Level() {}

	Level(vector<GameObject*> objects, Character* c);

	int pause();

	int selectCharacter();

	int run(string lv);

	int win();

	int lose();
};