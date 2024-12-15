#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include "Map.h"
#include "GameObject.h"
#include "Character.h"

using namespace std;

class Level
{
protected:
	int point = 0;
	Map map;
	PhysicsManager physicsManager;
	vector<GameObject*> gameObjects;

	vector<GameObject*> enemies;
	vector<GameObject*> items;

	shared_ptr<Character> character = nullptr;

	sf::Sprite bg_sprite;

public:
	Level() {}

	Level(vector<GameObject*> objects, Character* c);

	int selectCharacter();

	int run(string lv);
};