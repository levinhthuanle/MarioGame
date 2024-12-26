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

	character.m_sprite.setTextureRect(sf::IntRect(0, 0, 16, 31));
	character.m_sprite.setScale(4, 4);

	sf::FloatRect b = character.m_sprite.getGlobalBounds();

	if (!character.direction)
		character.m_sprite.setTexture(character.superTextures[0]);
	else
		character.m_sprite.setTexture(character.superTextures[1]);

	character.m_sprite.setPosition(b.left, b.top - 15 * 4);
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

	character.m_sprite.setTextureRect(sf::IntRect(0, 0, 16, 31));
	character.m_sprite.setScale(4, 4);

	sf::FloatRect b = character.m_sprite.getGlobalBounds();

	if (!character.direction)
		character.m_sprite.setTexture(character.fireTextures[0]);
	else
		character.m_sprite.setTexture(character.fireTextures[1]);

	character.m_sprite.setPosition(b.left, b.top - 15 * 4);
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





Character::Character() : currentState(new NormalState(*this))
{
	m_sprite.setPosition(300, 300);
	m_sprite.setScale(4, 4);
}

CharacterState* Character::getState()
{
	return currentState;
}

void Character::setState(CharacterState* newState)
{
	delete currentState;
	currentState = newState;
}

void Character::setSuperState()
{
	setState(new SuperState(*this));
}

void Character::setFireState()
{
	setState(new FireState(*this));
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

Fireball* Character::checkAction() {
	SoundManager* soundManager = SoundManager::getInstance();


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) or sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		jump();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		moveLeft();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) or sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		setCrouch();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		moveRight();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		return fire();
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

Fireball* Character::fire()
{
	if (dynamic_cast<FireState*>(currentState)) {
		chrono::high_resolution_clock::time_point now = chrono::high_resolution_clock::now();
		if (now - lastFire >= chrono::milliseconds(1000)) {
			lastFire = now;

			sf::FloatRect b = m_sprite.getGlobalBounds();
			if (!direction)
				return fireballFactory->createFireball(b.left + 125, b.top + 32, 500);
			else
				return fireballFactory->createFireball(b.left - 33, b.top + 32, -500);
		}
	}
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

	superTextures[0].loadFromFile("./Resources/Character/Mario/BigMario/bigStand.png", sf::IntRect(3, 1, 16, 31));
	superTextures[1].loadFromFile("./Resources/Character/Mario/BigMario/bigStand.png", sf::IntRect(24, 1, 16, 31));
	superTextures[2].loadFromFile("./Resources/Character/Mario/BigMario/bigCrouch.png", sf::IntRect(3, 1, 16, 31));
	superTextures[3].loadFromFile("./Resources/Character/Mario/BigMario/bigCrouch.png", sf::IntRect(24, 1, 16, 31));
	superTextures[4].loadFromFile("./Resources/Character/Mario/BigMario/bigJump.png", sf::IntRect(3, 1, 16, 31));
	superTextures[5].loadFromFile("./Resources/Character/Mario/BigMario/bigJump.png", sf::IntRect(24, 1, 16, 31));
	superTextures[6].loadFromFile("./Resources/Character/Mario/BigMario/bigSlide.png", sf::IntRect(3, 1, 16, 31));
	superTextures[7].loadFromFile("./Resources/Character/Mario/BigMario/bigSlide.png", sf::IntRect(24, 1, 16, 31));
	superTextures[8].loadFromFile("./Resources/Character/Mario/BigMario/bigWalk.png", sf::IntRect(3, 1, 16, 31));
	superTextures[9].loadFromFile("./Resources/Character/Mario/BigMario/bigWalk.png", sf::IntRect(24, 1, 16, 31));
	superTextures[10].loadFromFile("./Resources/Character/Mario/BigMario/bigWalk.png", sf::IntRect(45, 1, 16, 31));
	superTextures[11].loadFromFile("./Resources/Character/Mario/BigMario/bigWalk.png", sf::IntRect(66, 1, 16, 31));
	superTextures[12].loadFromFile("./Resources/Character/Mario/BigMario/bigWalk.png", sf::IntRect(87, 1, 16, 31));
	superTextures[13].loadFromFile("./Resources/Character/Mario/BigMario/bigWalk.png", sf::IntRect(108, 1, 16, 31));

	fireTextures[0].loadFromFile("./Resources/Character/Mario/FireMario/fireStand.png", sf::IntRect(3, 1, 16, 31));
	fireTextures[1].loadFromFile("./Resources/Character/Mario/FireMario/fireStand.png", sf::IntRect(24, 1, 16, 31));
	fireTextures[2].loadFromFile("./Resources/Character/Mario/FireMario/fireCrouch.png", sf::IntRect(3, 1, 16, 31));
	fireTextures[3].loadFromFile("./Resources/Character/Mario/FireMario/fireCrouch.png", sf::IntRect(24, 1, 16, 31));
	fireTextures[4].loadFromFile("./Resources/Character/Mario/FireMario/fireJump.png", sf::IntRect(3, 1, 16, 31));
	fireTextures[5].loadFromFile("./Resources/Character/Mario/FireMario/fireJump.png", sf::IntRect(24, 1, 16, 31));
	fireTextures[6].loadFromFile("./Resources/Character/Mario/FireMario/fireSlide.png", sf::IntRect(3, 1, 16, 31));
	fireTextures[7].loadFromFile("./Resources/Character/Mario/FireMario/fireSlide.png", sf::IntRect(24, 1, 16, 31));
	fireTextures[8].loadFromFile("./Resources/Character/Mario/FireMario/fireWalk.png", sf::IntRect(3, 1, 16, 31));
	fireTextures[9].loadFromFile("./Resources/Character/Mario/FireMario/fireWalk.png", sf::IntRect(24, 1, 16, 31));
	fireTextures[10].loadFromFile("./Resources/Character/Mario/FireMario/fireWalk.png", sf::IntRect(45, 1, 16, 31));
	fireTextures[11].loadFromFile("./Resources/Character/Mario/FireMario/fireWalk.png", sf::IntRect(66, 1, 16, 31));
	fireTextures[12].loadFromFile("./Resources/Character/Mario/FireMario/fireWalk.png", sf::IntRect(87, 1, 16, 31));
	fireTextures[13].loadFromFile("./Resources/Character/Mario/FireMario/fireWalk.png", sf::IntRect(108, 1, 16, 31));

	toSuper[0].loadFromFile("./Resources/Character/Mario/FireMario/fireShoot.png", sf::IntRect(1, 1, 20, 30));

	m_sprite.setTexture(textures[0]);
}

void Mario::jump()
{
	if (!jumping) {
		jumping = true;
		velocity.y = -jumpForce; //map 3 need higher jump
	}
}

void Character::setVelocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}




Luigi::Luigi()
{
	maxVelocityX = 350;

	textures[0].loadFromFile("./Resources/Character/Luigi/SmallLuigi/stand.png", sf::IntRect(3, 16, 14, 16));
	textures[1].loadFromFile("./Resources/Character/Luigi/SmallLuigi/stand.png", sf::IntRect(24, 16, 14, 16));
	textures[2].loadFromFile("./Resources/Character/Luigi/SmallLuigi/jump.png", sf::IntRect(3, 16, 14, 16));
	textures[3].loadFromFile("./Resources/Character/Luigi/SmallLuigi/jump.png", sf::IntRect(24, 16, 14, 16));
	textures[4].loadFromFile("./Resources/Character/Luigi/SmallLuigi/die.png", sf::IntRect(3, 16, 14, 16));
	textures[5].loadFromFile("./Resources/Character/Luigi/SmallLuigi/walk.png", sf::IntRect(3, 16, 14, 16));
	textures[6].loadFromFile("./Resources/Character/Luigi/SmallLuigi/walk.png", sf::IntRect(24, 16, 14, 16));
	textures[7].loadFromFile("./Resources/Character/Luigi/SmallLuigi/walk.png", sf::IntRect(45, 16, 14, 16));
	textures[8].loadFromFile("./Resources/Character/Luigi/SmallLuigi/walk.png", sf::IntRect(66, 16, 14, 16));
	textures[9].loadFromFile("./Resources/Character/Luigi/SmallLuigi/walk.png", sf::IntRect(87, 16, 14, 16));
	textures[10].loadFromFile("./Resources/Character/Luigi/SmallLuigi/walk.png", sf::IntRect(108, 16, 14, 16));
	textures[11].loadFromFile("./Resources/Character/Luigi/SmallLuigi/slide.png", sf::IntRect(3, 16, 14, 16));
	textures[12].loadFromFile("./Resources/Character/Luigi/SmallLuigi/slide.png", sf::IntRect(24, 16, 14, 16));

	superTextures[0].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigStand.png", sf::IntRect(3, 1, 16, 31));
	superTextures[1].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigStand.png", sf::IntRect(24, 1, 16, 31));
	superTextures[2].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigCrouch.png", sf::IntRect(3, 1, 16, 31));
	superTextures[3].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigCrouch.png", sf::IntRect(24, 1, 16, 31));
	superTextures[4].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigJump.png", sf::IntRect(3, 1, 16, 31));
	superTextures[5].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigJump.png", sf::IntRect(24, 1, 16, 31));
	superTextures[6].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigSlide.png", sf::IntRect(3, 1, 16, 31));
	superTextures[7].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigSlide.png", sf::IntRect(24, 1, 16, 31));
	superTextures[8].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigWalk.png", sf::IntRect(3, 1, 16, 31));
	superTextures[9].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigWalk.png", sf::IntRect(24, 1, 16, 31));
	superTextures[10].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigWalk.png", sf::IntRect(45, 1, 16, 31));
	superTextures[11].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigWalk.png", sf::IntRect(66, 1, 16, 31));
	superTextures[12].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigWalk.png", sf::IntRect(87, 1, 16, 31));
	superTextures[13].loadFromFile("./Resources/Character/Luigi/BigLuigi/bigWalk.png", sf::IntRect(108, 1, 16, 31));

	fireTextures[0].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireStand.png", sf::IntRect(3, 1, 16, 31));
	fireTextures[1].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireStand.png", sf::IntRect(24, 1, 16, 31));
	fireTextures[2].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireCrouch.png", sf::IntRect(3, 1, 16, 31));
	fireTextures[3].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireCrouch.png", sf::IntRect(24, 1, 16, 31));
	fireTextures[4].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireJump.png", sf::IntRect(3, 1, 16, 31));
	fireTextures[5].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireJump.png", sf::IntRect(24, 1, 16, 31));
	fireTextures[6].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireSlide.png", sf::IntRect(3, 1, 16, 31));
	fireTextures[7].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireSlide.png", sf::IntRect(24, 1, 16, 31));
	fireTextures[8].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireWalk.png", sf::IntRect(3, 1, 16, 31));
	fireTextures[9].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireWalk.png", sf::IntRect(24, 1, 16, 31));
	fireTextures[10].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireWalk.png", sf::IntRect(45, 1, 16, 31));
	fireTextures[11].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireWalk.png", sf::IntRect(66, 1, 16, 31));
	fireTextures[12].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireWalk.png", sf::IntRect(87, 1, 16, 31));
	fireTextures[13].loadFromFile("./Resources/Character/Luigi/FireLuigi/fireWalk.png", sf::IntRect(108, 1, 16, 31));
}

void Luigi::jump()
{
	if (!jumping) {
		jumping = true;
		velocity.y = -550;
	}
}





Fireball::Fireball(const shared_ptr<sf::Texture>& texture, float x, float y, int vel)
{
	m_sprite.setTexture(*texture.get());
	m_sprite.setScale(4, 4);
	m_sprite.setPosition(x, y);

	velocity.x = vel;
}

void Fireball::update(float deltaTime, Map map)
{
	m_sprite.move(velocity.x * deltaTime, 0);
}

FireballFactory::FireballFactory()
{
	fireballTexture = make_shared<sf::Texture>();
	fireballTexture->loadFromFile("./Resources/Item/Items_Blocks.png", sf::IntRect(6, 83, 8, 8));
}

Fireball* FireballFactory::createFireball(float x, float y, int vel)
{
	return new Fireball(fireballTexture, x, y, vel);
}