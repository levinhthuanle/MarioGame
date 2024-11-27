#pragma once
#include <iostream>
#include <vector>
#include "Map.h"
#include "GameObject.h"
#include "Character.h"

using namespace std;

class LevelManager
{
protected:
	Map map;
	vector<GameObject> gameObjects;
	shared_ptr<Character> character;

public:
	int run(string lv);
};