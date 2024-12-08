#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Map.h"
#include "Items.h"
#include <string>

using namespace std;
using namespace sf;

void convertSketch(string lv, Map& new_map, vector<GameObject*> enemies, vector<GameObject*> items);