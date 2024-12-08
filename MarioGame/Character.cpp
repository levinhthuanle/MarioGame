#include "Character.h"

using namespace std;

Character::Character()
{
	m_sprite.setPosition(50, 50);
	m_sprite.setScale(4, 4);
}

void Character::setForceX(float x)
{
	forceX = x;
}

void Character::setForceY(float y)
{
	if (velocity.y == 0)
		forceY = y;
}

void Character::update(float deltaTime, Map map)
{
	velocity.x += forceX * deltaTime;
	if (velocity.x > maxVelocityX)
		velocity.x = maxVelocityX;
	else if (velocity.x < -maxVelocityX)
		velocity.x = -maxVelocityX;

	velocity.y += (gravity + forceY) * deltaTime;

	checkObstacle(deltaTime, map);

	updateTexture();

	m_sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);

	if (forceX < 0)
		forceX += inertia;
	else if (forceX > 0)
		forceX -= inertia;
	if (forceY < 0)
		forceY += gravity;
	else if (forceY > 0)
		forceY = 0;
}

void Character::updateTexture()
{
	//chrono::time_point<chrono::high_resolution_clock> now = chrono::high_resolution_clock::now();
	//if (now - lastUpdate >= updateInterval) {
	//	lastUpdate = now;

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
	//}
}



Mario::Mario()
{
	jumpHeight = 80;
	inertia = 250;
	maxVelocityX = 300;

	textures[0].loadFromFile("./Resources/Character/Mario/SmallMario/stand.png", sf::IntRect(1, 1, 20, 30));
	textures[1].loadFromFile("./Resources/Character/Mario/SmallMario/stand.png", sf::IntRect(22, 1, 20, 30));
	textures[2].loadFromFile("./Resources/Character/Mario/SmallMario/jump.png", sf::IntRect(1, 1, 20, 30));
	textures[3].loadFromFile("./Resources/Character/Mario/SmallMario/jump.png", sf::IntRect(22, 1, 20, 30));
	textures[4].loadFromFile("./Resources/Character/Mario/SmallMario/die.png", sf::IntRect(1, 1, 20, 30));
	textures[5].loadFromFile("./Resources/Character/Mario/SmallMario/walk.png", sf::IntRect(1, 1, 20, 30));
	textures[6].loadFromFile("./Resources/Character/Mario/SmallMario/walk.png", sf::IntRect(22, 1, 20, 30));
	textures[7].loadFromFile("./Resources/Character/Mario/SmallMario/walk.png", sf::IntRect(43, 1, 20, 30));
	textures[8].loadFromFile("./Resources/Character/Mario/SmallMario/walk.png", sf::IntRect(64, 1, 20, 30));
	textures[9].loadFromFile("./Resources/Character/Mario/SmallMario/walk.png", sf::IntRect(85, 1, 20, 30));
	textures[10].loadFromFile("./Resources/Character/Mario/SmallMario/walk.png", sf::IntRect(106, 1, 20, 30));
	textures[11].loadFromFile("./Resources/Character/Mario/SmallMario/slide.png", sf::IntRect(1, 1, 20, 30));
	textures[12].loadFromFile("./Resources/Character/Mario/SmallMario/slide.png", sf::IntRect(22, 1, 20, 30));

	superTextures[0].loadFromFile("./Resources/Character/Mario/BigMario/bigStand.png", sf::IntRect(1, 1, 20, 30));
	superTextures[1].loadFromFile("./Resources/Character/Mario/BigMario/bigStand.png", sf::IntRect(22, 1, 20, 30));
	superTextures[2].loadFromFile("./Resources/Character/Mario/BigMario/bigCrouch.png", sf::IntRect(1, 1, 20, 30));
	superTextures[3].loadFromFile("./Resources/Character/Mario/BigMario/bigCrouch.png", sf::IntRect(22, 1, 20, 30));
	superTextures[4].loadFromFile("./Resources/Character/Mario/BigMario/bigJump.png", sf::IntRect(1, 1, 20, 30));
	superTextures[5].loadFromFile("./Resources/Character/Mario/BigMario/bigJump.png", sf::IntRect(22, 1, 20, 30));
	superTextures[6].loadFromFile("./Resources/Character/Mario/BigMario/bigSlide.png", sf::IntRect(1, 1, 20, 30));
	superTextures[7].loadFromFile("./Resources/Character/Mario/BigMario/bigSlide.png", sf::IntRect(22, 1, 20, 30));
	superTextures[8].loadFromFile("./Resources/Character/Mario/BigMario/bigWalk.png", sf::IntRect(1, 1, 20, 30));
	superTextures[9].loadFromFile("./Resources/Character/Mario/BigMario/bigWalk.png", sf::IntRect(22, 1, 20, 30));
	superTextures[10].loadFromFile("./Resources/Character/Mario/BigMario/bigWalk.png", sf::IntRect(43, 1, 20, 30));
	superTextures[11].loadFromFile("./Resources/Character/Mario/BigMario/bigWalk.png", sf::IntRect(64, 1, 20, 30));
	superTextures[12].loadFromFile("./Resources/Character/Mario/BigMario/bigWalk.png", sf::IntRect(85, 1, 20, 30));
	superTextures[13].loadFromFile("./Resources/Character/Mario/BigMario/bigWalk.png", sf::IntRect(106, 1, 20, 30));

	fireTextures[0].loadFromFile("./Resources/Character/Mario/FireMario/fireStand.png", sf::IntRect(1, 1, 20, 30));
	fireTextures[1].loadFromFile("./Resources/Character/Mario/FireMario/fireStand.png", sf::IntRect(22, 1, 20, 30));
	fireTextures[2].loadFromFile("./Resources/Character/Mario/FireMario/fireCrouch.png", sf::IntRect(1, 1, 20, 30));
	fireTextures[3].loadFromFile("./Resources/Character/Mario/FireMario/fireCrouch.png", sf::IntRect(22, 1, 20, 30));
	fireTextures[4].loadFromFile("./Resources/Character/Mario/FireMario/fireJump.png", sf::IntRect(1, 1, 20, 30));
	fireTextures[5].loadFromFile("./Resources/Character/Mario/FireMario/fireJump.png", sf::IntRect(22, 1, 20, 30));
	fireTextures[6].loadFromFile("./Resources/Character/Mario/FireMario/fireSlide.png", sf::IntRect(1, 1, 20, 30));
	fireTextures[7].loadFromFile("./Resources/Character/Mario/FireMario/fireSlide.png", sf::IntRect(22, 1, 20, 30));
	fireTextures[8].loadFromFile("./Resources/Character/Mario/FireMario/fireWalk.png", sf::IntRect(1, 1, 20, 30));
	fireTextures[9].loadFromFile("./Resources/Character/Mario/FireMario/fireWalk.png", sf::IntRect(22, 1, 20, 30));
	fireTextures[10].loadFromFile("./Resources/Character/Mario/FireMario/fireWalk.png", sf::IntRect(43, 1, 20, 30));
	fireTextures[11].loadFromFile("./Resources/Character/Mario/FireMario/fireWalk.png", sf::IntRect(64, 1, 20, 30));
	fireTextures[12].loadFromFile("./Resources/Character/Mario/FireMario/fireWalk.png", sf::IntRect(85, 1, 20, 30));
	fireTextures[13].loadFromFile("./Resources/Character/Mario/FireMario/fireWalk.png", sf::IntRect(106, 1, 20, 30));
	fireTextures[14].loadFromFile("./Resources/Character/Mario/FireMario/fireShoot.png", sf::IntRect(1, 1, 20, 30));
	fireTextures[15].loadFromFile("./Resources/Character/Mario/FireMario/fireShoot.png", sf::IntRect(22, 1, 20, 30));

	m_sprite.setTexture(textures[0]);
}

void Mario::setCrouch()
{
	return;
}



Luigi::Luigi()
{
	jumpHeight = 90;
	inertia = 20;
	maxVelocityX = 60;

	textures[0].loadFromFile("./Resources/Character/Luigi/SmallLuigi/stand.png", sf::IntRect(1, 1, 20, 30));
	textures[1].loadFromFile("./Resources/Character/Luigi/SmallLuigi/stand.png", sf::IntRect(22, 1, 20, 30));
	textures[2].loadFromFile("./Resources/Character/Luigi/SmallLuigi/jump.png", sf::IntRect(1, 1, 20, 30));
	textures[3].loadFromFile("./Resources/Character/Luigi/SmallLuigi/jump.png", sf::IntRect(22, 1, 20, 30));
	textures[4].loadFromFile("./Resources/Character/Luigi/SmallLuigi/die.png", sf::IntRect(1, 1, 20, 30));
	textures[5].loadFromFile("./Resources/Character/Luigi/SmallLuigi/walk.png", sf::IntRect(1, 1, 20, 30));
	textures[6].loadFromFile("./Resources/Character/Luigi/SmallLuigi/walk.png", sf::IntRect(22, 1, 20, 30));
	textures[7].loadFromFile("./Resources/Character/Luigi/SmallLuigi/walk.png", sf::IntRect(43, 1, 20, 30));
	textures[8].loadFromFile("./Resources/Character/Luigi/SmallLuigi/walk.png", sf::IntRect(64, 1, 20, 30));
	textures[9].loadFromFile("./Resources/Character/Luigi/SmallLuigi/walk.png", sf::IntRect(85, 1, 20, 30));
	textures[10].loadFromFile("./Resources/Character/Luigi/SmallLuigi/walk.png", sf::IntRect(106, 1, 20, 30));
	textures[11].loadFromFile("./Resources/Character/Luigi/SmallLuigi/slide.png", sf::IntRect(1, 1, 20, 30));
	textures[12].loadFromFile("./Resources/Character/Luigi/SmallLuigi/slide.png", sf::IntRect(22, 1, 20, 30));

	superTextures[0].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigStand.png", sf::IntRect(1, 1, 20, 30));
	superTextures[1].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigStand.png", sf::IntRect(22, 1, 20, 30));
	superTextures[2].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigCrouch.png", sf::IntRect(1, 1, 20, 30));
	superTextures[3].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigCrouch.png", sf::IntRect(22, 1, 20, 30));
	superTextures[4].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigJump.png", sf::IntRect(1, 1, 20, 30));
	superTextures[5].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigJump.png", sf::IntRect(22, 1, 20, 30));
	superTextures[6].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigSlide.png", sf::IntRect(1, 1, 20, 30));
	superTextures[7].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigSlide.png", sf::IntRect(22, 1, 20, 30));
	superTextures[8].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigWalk.png", sf::IntRect(1, 1, 20, 30));
	superTextures[9].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigWalk.png", sf::IntRect(22, 1, 20, 30));
	superTextures[10].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigWalk.png", sf::IntRect(43, 1, 20, 30));
	superTextures[11].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigWalk.png", sf::IntRect(64, 1, 20, 30));
	superTextures[12].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigWalk.png", sf::IntRect(85, 1, 20, 30));
	superTextures[13].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigWalk.png", sf::IntRect(106, 1, 20, 30));

	fireTextures[0].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireStand.png", sf::IntRect(1, 1, 20, 30));
	fireTextures[1].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireStand.png", sf::IntRect(22, 1, 20, 30));
	fireTextures[2].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireCrouch.png", sf::IntRect(1, 1, 20, 30));
	fireTextures[3].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireCrouch.png", sf::IntRect(22, 1, 20, 30));
	fireTextures[4].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireJump.png", sf::IntRect(1, 1, 20, 30));
	fireTextures[5].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireJump.png", sf::IntRect(22, 1, 20, 30));
	fireTextures[6].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireSlide.png", sf::IntRect(1, 1, 20, 30));
	fireTextures[7].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireSlide.png", sf::IntRect(22, 1, 20, 30));
	fireTextures[8].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireWalk.png", sf::IntRect(1, 1, 20, 30));
	fireTextures[9].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireWalk.png", sf::IntRect(22, 1, 20, 30));
	fireTextures[10].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireWalk.png", sf::IntRect(43, 1, 20, 30));
	fireTextures[11].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireWalk.png", sf::IntRect(64, 1, 20, 30));
	fireTextures[12].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireWalk.png", sf::IntRect(85, 1, 20, 30));
	fireTextures[13].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireWalk.png", sf::IntRect(106, 1, 20, 30));
	fireTextures[14].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireShoot.png", sf::IntRect(1, 1, 20, 30));
	fireTextures[15].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireShoot.png", sf::IntRect(22, 1, 20, 30));
}

void Luigi::setCrouch()
{
	return;
}



Decorator::Decorator() : character(nullptr) {}

Decorator::Decorator(shared_ptr<Character> c) : character(c) {}

void Decorator::updateTexture()
{
	if (crouch) {
		if (direction)
			m_sprite.setTexture(currentTexture[2]);
		else
			m_sprite.setTexture(currentTexture[3]);
		crouch = false;
		return;
	}
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

void Decorator::setCrouch()
{
	if (velocity.y == 0) {
		Character::crouch = true;
	}
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