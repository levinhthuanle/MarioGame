#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Map.h"
#include "Items.h"
#include <string>
#include "Pipe.h"

using namespace std;
using namespace sf;

void convertSketch(string fileName, Map& new_map, vector<vector<GameObject*>>& objMap, vector<GameObject*>& gameObjects, vector<GameObject*>& bricks, vector<GameObject*>& luckyblocks, vector<GameObject*>& enemies, vector<GameObject*>& items, Character* character);

void convertToSketch(const vector<vector<GameObject*>>& objMap, const vector<vector<Cell>>& cellGrid, const string& outputFilePath, Character* character);