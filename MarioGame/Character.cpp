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

	if (!character.direction)
		character.m_sprite.setTexture(character.fireTextures[0]);
	else
		character.m_sprite.setTexture(character.fireTextures[1]);
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

void Character::setNormalState()
{
	setState(new NormalState(*this));

	m_sprite.setTextureRect(sf::IntRect(0, 0, 14, 16));
	m_sprite.setScale(4, 4);

	sf::FloatRect b = m_sprite.getGlobalBounds();

	if (!direction)
		m_sprite.setTexture(superTextures[0]);
	else
		m_sprite.setTexture(superTextures[1]);
}

void Character::setSuperState()
{
	setState(new SuperState(*this));
}

void Character::setFireState()
{
	setState(new FireState(*this));
}

void Character::update(float deltaTime, Map map, vector<vector<GameObject*>>& objMap, Collision* collision)
{
	velocity.y += gravity * deltaTime;
	jumping = true;

	if (checkObstacle(deltaTime, map, objMap, collision) >= 10)
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

int Character::checkObstacle(float deltaTime, Map map, vector<vector<GameObject*>>& objMap, Collision* collision)
{
	collision->getInstance()->character.clear();
	const vector<vector<Cell>>& grids = map.getMap();
	//const vector<vector<Sprite>>& sprites = map.getSpriteGrid();

	// Changing these float to int would create gaps before collisions.
	// Consult Phan Tan Dat before change it. Please!
	float x = m_sprite.getPosition().x;
	float y = m_sprite.getPosition().y;

	float left = x / static_cast<float>(CELL_SIZE);
	float right = (x + m_sprite.getGlobalBounds().width) / static_cast<float>(CELL_SIZE);
	float top = y / static_cast<float>(CELL_SIZE);
	float bottom = (y + m_sprite.getGlobalBounds().height) / static_cast<float>(CELL_SIZE);
	float midX = (left + right) / 2;
	float midY = (top + bottom) / 2;

	float futureX = x + velocity.x * deltaTime;
	float futureY = y + velocity.y * deltaTime;

	float futureLeft = futureX / static_cast<float>(CELL_SIZE);
	float futureRight = (futureX + m_sprite.getGlobalBounds().width) / static_cast<float>(CELL_SIZE);
	float futureTop = futureY / static_cast<float>(CELL_SIZE);
	float futureBottom = (futureY + m_sprite.getGlobalBounds().height) / static_cast<float>(CELL_SIZE);
	float futureMidX = (futureLeft + futureRight) / 2;
	float futureMidY = (futureTop + futureBottom) / 2;

	// Check bounds to prevent out-of-range access
	if (left < 0 || right >= grids.size() || top < 0 || bottom >= grids[0].size()) {
		cout << "Out of bounds access detected!" << endl;
		return 0;
	}

	int ans = 0;

	//top
	collision->getInstance()->character.push_back(make_pair(0, objMap[int(left)][int(futureTop)]));
	collision->getInstance()->character.push_back(make_pair(0, objMap[int(midX)][int(futureTop)]));
	collision->getInstance()->character.push_back(make_pair(0, objMap[int(right)][int(futureTop)]));

	//bottom
	collision->getInstance()->character.push_back(make_pair(1, objMap[int(left)][int(futureBottom)]));
	collision->getInstance()->character.push_back(make_pair(1, objMap[int(midX)][int(futureBottom)]));
	collision->getInstance()->character.push_back(make_pair(1, objMap[int(right)][int(futureBottom)]));

	//left
	collision->getInstance()->character.push_back(make_pair(2, objMap[int(futureLeft)][int(top)]));
	collision->getInstance()->character.push_back(make_pair(2, objMap[int(futureLeft)][int(midY)]));
	collision->getInstance()->character.push_back(make_pair(2, objMap[int(futureLeft)][int(bottom)]));

	//right
	collision->getInstance()->character.push_back(make_pair(3, objMap[int(futureRight)][int(top)]));
	collision->getInstance()->character.push_back(make_pair(3, objMap[int(futureRight)][int(midY)]));
	collision->getInstance()->character.push_back(make_pair(3, objMap[int(futureRight)][int(bottom)]));

	// right
	if (grids[int(futureRight)][int(top)].getType() != 0
		or grids[int(futureRight)][int((top + midY) / 2)].getType() != 0
		or grids[int(futureRight)][int(midY)].getType() != 0
		or grids[int(futureRight)][int((midY + bottom) / 2)].getType() != 0
		or grids[int(futureRight)][int(bottom)].getType() != 0) {
		velocity.x = 0;
		ans += 1;
	}
	// left
	if (grids[int(futureLeft)][int(top)].getType() != 0
		or grids[int(futureLeft)][int((top + midY) / 2)].getType() != 0
		or grids[int(futureLeft)][int(midY)].getType() != 0
		or grids[int(futureLeft)][int((midY + bottom) / 2)].getType() != 0
		or grids[int(futureLeft)][int(bottom)].getType() != 0) {
		velocity.x = 0;
		ans += 2;
	}
	// down
	if (grids[int(left)][int(futureBottom)].getType() != 0
		or grids[int(right)][int(futureBottom)].getType() != 0
		or grids[int(midX)][int(futureBottom)].getType() != 0) {
		velocity.y = 0;
		ans += 10;
	}
	// up
	if (grids[int(left)][int(futureTop)].getType() != 0
		or grids[int(right)][int(futureTop)].getType() != 0
		or grids[int(midX)][int(futureTop)].getType() != 0) {
		velocity.y = 0;

		// 1 brick
		// 2 lucky box
		//if (grids[x][y].getType())
		std::string type = "Brick";
		if (grids[int(midX)][int(futureTop)].getType() == 2)
			type = "Lucky Box";
		if (grids[int(midX)][int(futureTop)].getType() == 0)
			type = "Nothing";
		std::cout << "Try to break " << type << std::endl;
		return grids[int(midX)][int(futureTop)].getType();
	}
	return ans;
}

void Character::updateTexture()
{
	chrono::time_point<chrono::high_resolution_clock> now = chrono::high_resolution_clock::now();
	if (now - lastUpdate >= updateInterval) {
		lastUpdate = now;

		currentState->updateTexture(*this);
	}
}

void Character::checkAction(PhysicsManager* physicsManager, FireballFactory& fireballFactory) {
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
		fire(physicsManager, fireballFactory);
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

void Character::fire(PhysicsManager* physicsManager, FireballFactory& fireballFactory)
{
	if (dynamic_cast<FireState*>(currentState)) {
		chrono::high_resolution_clock::time_point now = chrono::high_resolution_clock::now();
		if (now - lastFire >= chrono::milliseconds(1000)) {
			lastFire = now;

			sf::FloatRect b = m_sprite.getGlobalBounds();
			cout << b.width << endl;
			if (!direction)
				fireballFactory.createFireball(physicsManager, b.left + 50, b.top + 70, 500);
			else
				fireballFactory.createFireball(physicsManager, b.left - 20, b.top + 70, -500);
		}
	}
}

void Character::setPosition(sf::Vector2f pos) {
	this->m_sprite.setPosition(pos);
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

	m_sprite.setTexture(textures[0]);
}

void Mario::jump()
{
	if (!jumping) {
		jumping = true;
		SoundManager::getInstance()->playSoundJumpSmall();
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
	maxVelocityX = 200;

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
		velocity.y = -jumpForce-200 ;
	}
}