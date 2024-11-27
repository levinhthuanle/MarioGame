#pragma once
#include "Items.h"
class Coins : public Items
{
public:
	const std::string path = "";

public:
	Coins() {}

	void special() override {}
};

