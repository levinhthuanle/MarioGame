#pragma once
#include "GameObject.h"

class LuckyBlock : public GameObject {
private:
	bool isReal;
public:
	LuckyBlock(std::string path, std::string pathAfter, std::string name, bool isLucky) : GameObject(path, pathAfter, name), isReal(isLucky) {}

	bool doesItContainMushroom() {
		return isReal;
	}
};

