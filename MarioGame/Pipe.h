#pragma once
#include "Character.h"
#include "GameObject.h"
class Pipe : public GameObject
{
private:
	bool isTeleport;
	sf::Vector2f goal;
public:
	Pipe(): GameObject("Resources/Tile/pipetopleft.png", "Pipe"){
		isTeleport = false;
		goal = { 0.f, 0.f };
	}

	Pipe(bool isTeleport, sf::Vector2f goal) : GameObject("Resources/Tile/pipetopleft.png", "Pipe") {
		this->isTeleport = isTeleport;
		this->goal = goal;
	}

	Pipe(sf::Vector2f location) {
		isTeleport = true;
		this->goal = location;
	}

	Pipe(float x, float y) {
		isTeleport = true;
		this->goal = { x, y };
	}

	bool canTeleport(Character* character) {
		return isTeleport;
	}

	void teleport(Character* character) {
		character->setPosition(goal);
	}
};

