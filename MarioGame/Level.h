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
	Map map;
	PhysicsManager physicsManager;
	vector<GameObject*> gameObjects;

	vector<GameObject*> enemies;
	vector<GameObject*> items;

	shared_ptr<Character> character = nullptr;

public:
	Level() {}

	Level(vector<GameObject*> objects, Character* c);

	int run(string lv);
};