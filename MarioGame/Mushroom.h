#pragma once
#include "Items.h"
class Mushroom : public Items
{
public:
	std::string path = "";

	Mushroom(std::string path, std::string isBreakable) : Items(path, isBreakable) {}

};

