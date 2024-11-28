#include "Character.h"

using namespace std;

Character::Character()
{
	currentWalkTexture = 0;
}

void Character::update(float deltaTime, Map map)
{
	chrono::time_point<chrono::high_resolution_clock> now = chrono::high_resolution_clock::now();
	if (now - lastUpdate >= updateInterval) {
		lastUpdate = now;

		PhysicsAppliedObject::update(deltaTime, map);

		updateTexture();
	}
}

void Character::updateTexture()
{
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



Mario::Mario()
{
	jumpHeight = 80;
	inertia = 10;
	maxVelocityX = 50;

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

	superTextures[0].loadFromFile("Resources/Character/Mario/SuperMario/stand_0.png");
	superTextures[1].loadFromFile("Resources/Character/Mario/SuperMario/stand_1.png");
	superTextures[2].loadFromFile("Resources/Character/Mario/SuperMario/crouch_0.png");
	superTextures[3].loadFromFile("Resources/Character/Mario/SuperMario/crouch_1.png");
	superTextures[4].loadFromFile("Resources/Character/Mario/SuperMario/jump_0.png");
	superTextures[5].loadFromFile("Resources/Character/Mario/SuperMario/jump_1.png");
	superTextures[6].loadFromFile("Resources/Character/Mario/SuperMario/slide_0.png");
	superTextures[7].loadFromFile("Resources/Character/Mario/SuperMario/slide_1.png");
	superTextures[8].loadFromFile("Resources/Character/Mario/SuperMario/walk_0_0.png");
	superTextures[9].loadFromFile("Resources/Character/Mario/SuperMario/walk_0_1.png");
	superTextures[10].loadFromFile("Resources/Character/Mario/SuperMario/walk_0_2.png");
	superTextures[11].loadFromFile("Resources/Character/Mario/SuperMario/walk_1_0.png");
	superTextures[12].loadFromFile("Resources/Character/Mario/SuperMario/walk_1_1.png");
	superTextures[13].loadFromFile("Resources/Character/Mario/SuperMario/walk_1_2.png");
	superTextures[14].loadFromFile("Resources/Character/Mario/SuperMario/climb_0_0.png");
	superTextures[15].loadFromFile("Resources/Character/Mario/SuperMario/climb_0_1.png");
	superTextures[16].loadFromFile("Resources/Character/Mario/SuperMario/climb_1_0.png");
	superTextures[17].loadFromFile("Resources/Character/Mario/SuperMario/climb_1_1.png");

	fireTextures[0].loadFromFile("Resources/Character/Mario/FireMario/stand_0.png");
	fireTextures[1].loadFromFile("Resources/Character/Mario/FireMario/stand_1.png");
	fireTextures[2].loadFromFile("Resources/Character/Mario/FireMario/crouch_0.png");
	fireTextures[3].loadFromFile("Resources/Character/Mario/FireMario/crouch_1.png");
	fireTextures[4].loadFromFile("Resources/Character/Mario/FireMario/jump_0.png");
	fireTextures[5].loadFromFile("Resources/Character/Mario/FireMario/jump_1.png");
	fireTextures[6].loadFromFile("Resources/Character/Mario/FireMario/slide_0.png");
	fireTextures[7].loadFromFile("Resources/Character/Mario/FireMario/slide_1.png");
	fireTextures[8].loadFromFile("Resources/Character/Mario/FireMario/walk_0_0.png");
	fireTextures[9].loadFromFile("Resources/Character/Mario/FireMario/walk_0_1.png");
	fireTextures[10].loadFromFile("Resources/Character/Mario/FireMario/walk_0_2.png");
	fireTextures[11].loadFromFile("Resources/Character/Mario/FireMario/walk_1_0.png");
	fireTextures[12].loadFromFile("Resources/Character/Mario/FireMario/walk_1_1.png");
	fireTextures[13].loadFromFile("Resources/Character/Mario/FireMario/walk_1_2.png");
	fireTextures[14].loadFromFile("Resources/Character/Mario/FireMario/climb_0_0.png");
	fireTextures[15].loadFromFile("Resources/Character/Mario/FireMario/climb_0_1.png");
	fireTextures[16].loadFromFile("Resources/Character/Mario/FireMario/climb_1_0.png");
	fireTextures[17].loadFromFile("Resources/Character/Mario/FireMario/climb_1_1.png");
}



Luigi::Luigi()
{
	jumpHeight = 90;
	inertia = 20;
	maxVelocityX = 60;

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

	superTextures[0].loadFromFile("Resources/Character/Luigi/SuperLuigi/stand_0.png");
	superTextures[1].loadFromFile("Resources/Character/Luigi/SuperLuigi/stand_1.png");
	superTextures[2].loadFromFile("Resources/Character/Luigi/SuperLuigi/crouch_0.png");
	superTextures[3].loadFromFile("Resources/Character/Luigi/SuperLuigi/crouch_1.png");
	superTextures[4].loadFromFile("Resources/Character/Luigi/SuperLuigi/jump_0.png");
	superTextures[5].loadFromFile("Resources/Character/Luigi/SuperLuigi/jump_1.png");
	superTextures[6].loadFromFile("Resources/Character/Luigi/SuperLuigi/slide_0.png");
	superTextures[7].loadFromFile("Resources/Character/Luigi/SuperLuigi/slide_1.png");
	superTextures[8].loadFromFile("Resources/Character/Luigi/SuperLuigi/walk_0_0.png");
	superTextures[9].loadFromFile("Resources/Character/Luigi/SuperLuigi/walk_0_1.png");
	superTextures[10].loadFromFile("Resources/Character/Luigi/SuperLuigi/walk_0_2.png");
	superTextures[11].loadFromFile("Resources/Character/Luigi/SuperLuigi/walk_1_0.png");
	superTextures[12].loadFromFile("Resources/Character/Luigi/SuperLuigi/walk_1_1.png");
	superTextures[13].loadFromFile("Resources/Character/Luigi/SuperLuigi/walk_1_2.png");
	superTextures[14].loadFromFile("Resources/Character/Luigi/SuperLuigi/climb_0_0.png");
	superTextures[15].loadFromFile("Resources/Character/Luigi/SuperLuigi/climb_0_1.png");
	superTextures[16].loadFromFile("Resources/Character/Luigi/SuperLuigi/climb_1_0.png");
	superTextures[17].loadFromFile("Resources/Character/Luigi/SuperLuigi/climb_1_1.png");

	fireTextures[0].loadFromFile("Resources/Character/Luigi/FireLuigi/stand_0.png");
	fireTextures[1].loadFromFile("Resources/Character/Luigi/FireLuigi/stand_1.png");
	fireTextures[2].loadFromFile("Resources/Character/Luigi/FireLuigi/crouch_0.png");
	fireTextures[3].loadFromFile("Resources/Character/Luigi/FireLuigi/crouch_1.png");
	fireTextures[4].loadFromFile("Resources/Character/Luigi/FireLuigi/jump_0.png");
	fireTextures[5].loadFromFile("Resources/Character/Luigi/FireLuigi/jump_1.png");
	fireTextures[6].loadFromFile("Resources/Character/Luigi/FireLuigi/slide_0.png");
	fireTextures[7].loadFromFile("Resources/Character/Luigi/FireLuigi/slide_1.png");
	fireTextures[8].loadFromFile("Resources/Character/Luigi/FireLuigi/walk_0_0.png");
	fireTextures[9].loadFromFile("Resources/Character/Luigi/FireLuigi/walk_0_1.png");
	fireTextures[10].loadFromFile("Resources/Character/Luigi/FireLuigi/walk_0_2.png");
	fireTextures[11].loadFromFile("Resources/Character/Luigi/FireLuigi/walk_1_0.png");
	fireTextures[12].loadFromFile("Resources/Character/Luigi/FireLuigi/walk_1_1.png");
	fireTextures[13].loadFromFile("Resources/Character/Luigi/FireLuigi/walk_1_2.png");
	fireTextures[14].loadFromFile("Resources/Character/Luigi/FireLuigi/climb_0_0.png");
	fireTextures[15].loadFromFile("Resources/Character/Luigi/FireLuigi/climb_0_1.png");
	fireTextures[16].loadFromFile("Resources/Character/Luigi/FireLuigi/climb_1_0.png");
	fireTextures[17].loadFromFile("Resources/Character/Luigi/FireLuigi/climb_1_1.png");
}



Decorator::Decorator() : character(nullptr) {}

Decorator::Decorator(shared_ptr<Character> c) : character(c) {}

void Decorator::updateTexture()
{
	//if (velocity.y != 0) {
	//	if (direction)
	//		m_sprite.setTexture(textures[2]);
	//	else
	//		m_sprite.setTexture(textures[3]);
	//}
	//else if ((velocity.x > 0 and velocity.x >= lastXVelocity) or (velocity.x < 0 and velocity.x <= lastXVelocity)) {
	//	currentWalkTexture = (currentWalkTexture + 1) % 3;
	//	if (velocity.x > 0)
	//		m_sprite.setTexture(textures[currentWalkTexture + 5]);
	//	else if (velocity.x < 0)
	//		m_sprite.setTexture(textures[currentWalkTexture + 8]);
	//}
	//else {
	//	if (velocity.x > 0)
	//		m_sprite.setTexture(textures[11]);
	//	else if (velocity.x < 0)
	//		m_sprite.setTexture(textures[12]);
	//}
}



SuperDecorator::SuperDecorator(shared_ptr<Character> c) : Decorator(c)
{
	breakBrick = 1;
	fire = 0;
}



FireDecorator::FireDecorator(shared_ptr<Character> c) : Decorator(c)
{
	fire = 1;
}