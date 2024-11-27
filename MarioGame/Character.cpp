#include "Character.h"

using namespace std;

Character::Character()
{
	currentWalkTexture = 0;
}

void Character::update(float deltaTime, Map map)
{
	PhysicsAppliedObject::update(deltaTime, map);

	changeMovementTexture();
}

void Character::changeMovementTexture()
{
	chrono::time_point<chrono::high_resolution_clock> now = chrono::high_resolution_clock::now();
	if (now - lastUpdate >= updateInterval) {
		lastUpdate = now;
		if (velocity.y != 0) {
			if (direction)
				m_sprite.setTexture(textures[2]);
			else
				m_sprite.setTexture(textures[3]);
		}
		else if ((velocity.x > 0 and velocity.x >= lastXVelocity) or (velocity.x < 0 and velocity.x <= lastXVelocity)) {
			currentWalkTexture = (currentWalkTexture + 1) % 3;
			if (velocity.x > 0)
				m_sprite.setTexture(textures[currentWalkTexture + 5]);
			else if (velocity.x < 0)
				m_sprite.setTexture(textures[currentWalkTexture + 8]);
		}
		else {
			if (velocity.x > 0)
				m_sprite.setTexture(textures[11]);
			else if (velocity.x < 0)
				m_sprite.setTexture(textures[12]);
		}
	}
}



Mario::Mario()
{
	textures[0].loadFromFile("Resources/Character/Mario/SmallMario/stand_0.png");
	textures[1].loadFromFile("Resources/Character/Mario/SmallMario/stand_1.png");
	textures[2].loadFromFile("Resources/Character/Mario/SmallMario/jump_0.png");
	textures[3].loadFromFile("Resources/Character/Mario/SmallMario/jump_1.png");
	textures[4].loadFromFile("Resources/Character/Mario/SmallMario/die.png");
	textures[5].loadFromFile("Resources/Character/Mario/SmallMario/walk_0_0.png");
	textures[6].loadFromFile("Resources/Character/Mario/SmallMario/walk_0_1.png");
	textures[7].loadFromFile("Resources/Character/Mario/SmallMario/walk_0_2.png");
	textures[8].loadFromFile("Resources/Character/Mario/SmallMario/walk_1_0.png");
	textures[9].loadFromFile("Resources/Character/Mario/SmallMario/walk_1_1.png");
	textures[10].loadFromFile("Resources/Character/Mario/SmallMario/walk_1_2.png");
	textures[11].loadFromFile("Resources/Character/Mario/SmallMario/slide_0.png");
	textures[12].loadFromFile("Resources/Character/Mario/SmallMario/slide_1.png");
	textures[13].loadFromFile("Resources/Character/Mario/SmallMario/climb_0_0.png");
	textures[14].loadFromFile("Resources/Character/Mario/SmallMario/climb_0_1.png");
	textures[15].loadFromFile("Resources/Character/Mario/SmallMario/climb_1_0.png");
	textures[16].loadFromFile("Resources/Character/Mario/SmallMario/climb_1_1.png");

	jumpHeight = 80;
	inertia = 10;
	maxVelocityX = 50;
}



Luigi::Luigi()
{
	textures[0].loadFromFile("Resources/Character/Luigi/SmallLuigi/stand_0.png");
	textures[1].loadFromFile("Resources/Character/Luigi/SmallLuigi/stand_1.png");
	textures[2].loadFromFile("Resources/Character/Luigi/SmallLuigi/jump_0.png");
	textures[3].loadFromFile("Resources/Character/Luigi/SmallLuigi/jump_1.png");
	textures[4].loadFromFile("Resources/Character/Luigi/SmallLuigi/die.png");
	textures[5].loadFromFile("Resources/Character/Luigi/SmallLuigi/walk_0_0.png");
	textures[6].loadFromFile("Resources/Character/Luigi/SmallLuigi/walk_0_1.png");
	textures[7].loadFromFile("Resources/Character/Luigi/SmallLuigi/walk_0_2.png");
	textures[8].loadFromFile("Resources/Character/Luigi/SmallLuigi/walk_1_0.png");
	textures[9].loadFromFile("Resources/Character/Luigi/SmallLuigi/walk_1_1.png");
	textures[10].loadFromFile("Resources/Character/Luigi/SmallLuigi/walk_1_2.png");
	textures[11].loadFromFile("Resources/Character/Luigi/SmallLuigi/slide_0.png");
	textures[12].loadFromFile("Resources/Character/Luigi/SmallLuigi/slide_1.png");
	textures[13].loadFromFile("Resources/Character/Luigi/SmallLuigi/climb_0_0.png");
	textures[14].loadFromFile("Resources/Character/Luigi/SmallLuigi/climb_0_1.png");
	textures[15].loadFromFile("Resources/Character/Luigi/SmallLuigi/climb_1_0.png");
	textures[16].loadFromFile("Resources/Character/Luigi/SmallMario/climb_1_1.png");

	jumpHeight = 90;
	inertia = 20;
	maxVelocityX = 60;
}



Decorator::Decorator() : character(nullptr) {}

Decorator::Decorator(shared_ptr<Character> c) : character(c) {}



SuperDecorator::SuperDecorator(shared_ptr<Character> c) : Decorator(c)
{
	breakBrick = 1;
	fire = 0;
}



FireDecorator::FireDecorator(shared_ptr<Character> c) : Decorator(c)
{
	fire = 1;
}