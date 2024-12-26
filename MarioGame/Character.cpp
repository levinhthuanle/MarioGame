#include "Character.h"

using namespace std;

NormalState::NormalState(Character& character)
{
	character.breakBrick = false;
	character.fireable = false;
}

void NormalState::updateTexture(Character& character)
{
	if (character.velocity.y != 0) {
		if (!character.direction)
			character.m_sprite.setTexture(character.textures[2]);
		else
			character.m_sprite.setTexture(character.textures[3]);
	}
	else if (character.velocity.x == 0) {
		if (!character.direction)
			character.m_sprite.setTexture(character.textures[0]);
		else
			character.m_sprite.setTexture(character.textures[1]);
	}
	else if ((character.velocity.x > 0 and character.velocity.x == character.maxVelocityX) or (character.velocity.x < 0 and character.velocity.x == -(character.maxVelocityX))) {
		character.currentWalkTexture = (character.currentWalkTexture + 1) % 3;
		if (character.velocity.x > 0)
			character.m_sprite.setTexture(character.textures[character.currentWalkTexture + 5]);
		else if (character.velocity.x < 0)
			character.m_sprite.setTexture(character.textures[character.currentWalkTexture + 8]);
	}
	else {
		if (character.velocity.x > 0)
			character.m_sprite.setTexture(character.textures[11]);
		else if (character.velocity.x < 0)
			character.m_sprite.setTexture(character.textures[12]);
	}
}

void NormalState::crouch(Character& character)
{
	return;
}

SuperState::SuperState(Character& character)
{
	character.breakBrick = true;
}

void SuperState::updateTexture(Character& character)
{
	if (character.crouching) {
		if (!character.direction)
			character.m_sprite.setTexture(character.superTextures[2]);
		else
			character.m_sprite.setTexture(character.superTextures[2]);
		return;
	}
	if (character.velocity.y != 0) {
		if (!character.direction)
			character.m_sprite.setTexture(character.superTextures[4]);
		else
			character.m_sprite.setTexture(character.superTextures[5]);
	}
	else if (character.velocity.x == 0) {
		if (!character.direction)
			character.m_sprite.setTexture(character.superTextures[0]);
		else
			character.m_sprite.setTexture(character.superTextures[1]);
	}
	else if ((character.velocity.x > 0 and character.velocity.x == character.maxVelocityX) or (character.velocity.x < 0 and character.velocity.x == -(character.maxVelocityX))) {
		character.currentWalkTexture = (character.currentWalkTexture + 1) % 3;
		if (character.velocity.x > 0)
			character.m_sprite.setTexture(character.superTextures[character.currentWalkTexture + 8]);
		else if (character.velocity.x < 0)
			character.m_sprite.setTexture(character.superTextures[character.currentWalkTexture + 11]);
	}
	else {
		if (character.velocity.x > 0)
			character.m_sprite.setTexture(character.superTextures[6]);
		else if (character.velocity.x < 0)
			character.m_sprite.setTexture(character.superTextures[7]);
	}
}

void SuperState::crouch(Character& character)
{
	if (character.velocity.y == 0) {
		character.crouching = true;
	}

}

FireState::FireState(Character& character)
{
	character.fireable = true;
}

void FireState::updateTexture(Character& character)
{
	if (character.crouching) {
		if (!character.direction)
			character.m_sprite.setTexture(character.fireTextures[2]);
		else
			character.m_sprite.setTexture(character.fireTextures[2]);
		return;
	}
	if (character.velocity.y != 0) {
		if (!character.direction)
			character.m_sprite.setTexture(character.fireTextures[4]);
		else
			character.m_sprite.setTexture(character.fireTextures[5]);
	}
	else if (character.velocity.x == 0) {
		if (!character.direction)
			character.m_sprite.setTexture(character.fireTextures[0]);
		else
			character.m_sprite.setTexture(character.fireTextures[1]);
	}
	else if ((character.velocity.x > 0 and character.velocity.x == character.maxVelocityX) or (character.velocity.x < 0 and character.velocity.x == -(character.maxVelocityX))) {
		character.currentWalkTexture = (character.currentWalkTexture + 1) % 3;
		if (character.velocity.x > 0)
			character.m_sprite.setTexture(character.fireTextures[character.currentWalkTexture + 8]);
		else if (character.velocity.x < 0)
			character.m_sprite.setTexture(character.fireTextures[character.currentWalkTexture + 11]);
	}
	else {
		if (character.velocity.x > 0)
			character.m_sprite.setTexture(character.fireTextures[6]);
		else if (character.velocity.x < 0)
			character.m_sprite.setTexture(character.fireTextures[7]);
	}
}

void FireState::crouch(Character& character)
{
	if (character.velocity.y == 0) {
		character.crouching = true;
	}

}





Character::Character()
{
	currentState = new NormalState(*this);

	m_sprite.setPosition(300, 300);
	m_sprite.setScale(4, 4);
}

void Character::update(float deltaTime, Map map)
{
	velocity.y += gravity * deltaTime;
	jumping = true;

	std::pair<int, int> nothing = { 0, 0 };
	if (checkObstacle(deltaTime, map, nothing) >= 10)
		jumping = false;

	updateTexture();

	m_sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);

	if (velocity.x > 0) {
		velocity.x -= inertia;
		if (velocity.x < 0)
			velocity.x = 0;
	}
	else if (velocity.x < 0) {
		velocity.x += inertia;
		if (velocity.x > 0)
			velocity.x = 0;
	}

	crouching = false;
}

void Character::updateTexture()
{
	chrono::time_point<chrono::high_resolution_clock> now = chrono::high_resolution_clock::now();
	if (now - lastUpdate >= updateInterval) {
		lastUpdate = now;

		currentState->updateTexture(*this);
	}
}

void Character::moveLeft()
{
	direction = 1;
	velocity.x = -(maxVelocityX);
}

void Character::moveRight()
{
	direction = 0;
	velocity.x = maxVelocityX;
}

void Character::setCrouch()
{
	currentState->crouch(*this);
}





Mario::Mario()
{
	maxVelocityX = 300;

	textures[0].loadFromFile("./Resources/Character/Mario/SmallMario/stand.png", sf::IntRect(3, 16, 14, 16));
	textures[1].loadFromFile("./Resources/Character/Mario/SmallMario/stand.png", sf::IntRect(24, 16, 14, 16));
	textures[2].loadFromFile("./Resources/Character/Mario/SmallMario/jump.png", sf::IntRect(3, 16, 14, 16));
	textures[3].loadFromFile("./Resources/Character/Mario/SmallMario/jump.png", sf::IntRect(24, 16, 14, 16));
	textures[4].loadFromFile("./Resources/Character/Mario/SmallMario/die.png", sf::IntRect(3, 16, 14, 16));
	textures[5].loadFromFile("./Resources/Character/Mario/SmallMario/walk.png", sf::IntRect(3, 16, 14, 16));
	textures[6].loadFromFile("./Resources/Character/Mario/SmallMario/walk.png", sf::IntRect(24, 16, 14, 16));
	textures[7].loadFromFile("./Resources/Character/Mario/SmallMario/walk.png", sf::IntRect(45, 16, 14, 16));
	textures[8].loadFromFile("./Resources/Character/Mario/SmallMario/walk.png", sf::IntRect(66, 16, 14, 16));
	textures[9].loadFromFile("./Resources/Character/Mario/SmallMario/walk.png", sf::IntRect(87, 16, 14, 16));
	textures[10].loadFromFile("./Resources/Character/Mario/SmallMario/walk.png", sf::IntRect(108, 16, 14, 16));
	textures[11].loadFromFile("./Resources/Character/Mario/SmallMario/slide.png", sf::IntRect(3, 16, 14, 16));
	textures[12].loadFromFile("./Resources/Character/Mario/SmallMario/slide.png", sf::IntRect(24, 16, 14, 16));

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

	toSuper[0].loadFromFile("./Resources/Character/Mario/FireMario/fireShoot.png", sf::IntRect(1, 1, 20, 30));

	m_sprite.setTexture(textures[0]);
}

void Mario::jump()
{
	if (!jumping) {
		jumping = true;
		velocity.y = -700;
	}
}





Luigi::Luigi()
{
	maxVelocityX = 350;

	textures[0].loadFromFile("./Resources/Character/Luigi/SmallLuigi/stand.png", sf::IntRect(3, 16, 16, 16));
	textures[1].loadFromFile("./Resources/Character/Luigi/SmallLuigi/stand.png", sf::IntRect(24, 16, 16, 16));
	textures[2].loadFromFile("./Resources/Character/Luigi/SmallLuigi/jump.png", sf::IntRect(3, 16, 16, 16));
	textures[3].loadFromFile("./Resources/Character/Luigi/SmallLuigi/jump.png", sf::IntRect(24, 16, 16, 16));
	textures[4].loadFromFile("./Resources/Character/Luigi/SmallLuigi/die.png", sf::IntRect(3, 16, 16, 16));
	textures[5].loadFromFile("./Resources/Character/Luigi/SmallLuigi/walk.png", sf::IntRect(3, 16, 16, 16));
	textures[6].loadFromFile("./Resources/Character/Luigi/SmallLuigi/walk.png", sf::IntRect(24, 16, 16, 16));
	textures[7].loadFromFile("./Resources/Character/Luigi/SmallLuigi/walk.png", sf::IntRect(45, 16, 16, 16));
	textures[8].loadFromFile("./Resources/Character/Luigi/SmallLuigi/walk.png", sf::IntRect(66, 16, 16, 16));
	textures[9].loadFromFile("./Resources/Character/Luigi/SmallLuigi/walk.png", sf::IntRect(87, 16, 16, 16));
	textures[10].loadFromFile("./Resources/Character/Luigi/SmallLuigi/walk.png", sf::IntRect(108, 16, 16, 16));
	textures[11].loadFromFile("./Resources/Character/Luigi/SmallLuigi/slide.png", sf::IntRect(3, 16, 16, 16));
	textures[12].loadFromFile("./Resources/Character/Luigi/SmallLuigi/slide.png", sf::IntRect(24, 16, 16, 16));

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

void Luigi::jump()
{
	if (!jumping) {
		jumping = true;
		velocity.y = -550;
	}
}