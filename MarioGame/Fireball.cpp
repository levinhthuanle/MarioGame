#include "Fireball.h"

Fireball::Fireball(const shared_ptr<sf::Texture> texture, float x, float y, int vel)
{
	m_sprite.setTexture(*texture.get());
	m_sprite.setScale(4, 4);
	m_sprite.setPosition(x, y);

	velocity.x = vel;
}

void Fireball::update(float deltaTime, Map map, vector<vector<GameObject*>>& objMap, Collision* collision)
{
	checkObstacle(deltaTime, map, objMap, collision);
	m_sprite.move(velocity.x * deltaTime, 0);
}

int Fireball::checkObstacle(float deltaTime, Map map, vector<vector<GameObject*>>& objMap, Collision* collision)
{
	const vector<vector<Cell>>& grids = map.getMap();

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

	// Check bounds to prevent out-of-range access
	if (left < 0 || right >= grids.size() || top < 0 || bottom >= grids[0].size()) {
		cout << "Out of bounds access detected!" << endl;
		return -1;
	}

	collision->getInstance()->fireball.push_back(make_pair(this, objMap[int(futureLeft)][int(midY)]));
	collision->getInstance()->fireball.push_back(make_pair(this, objMap[int(futureRight)][int(midY)]));

	if (grids[int(futureRight)][int(midY)].getType() != 0 or grids[int(futureLeft)][int(midY)].getType() != 0) {
		deleteMark = true;
		return 1;
	}

	return 0;
}


FireballFactory::FireballFactory()
{
	texture = make_shared<sf::Texture>();
	texture->loadFromFile("./Resources/Item/Items_Blocks.png", sf::IntRect(6, 83, 8, 8));
}

Fireball* FireballFactory::createFireball(PhysicsManager* physicsManager, float x, float y, int vel)
{
	Fireball* fireball = new Fireball(texture, x, y, vel);
	fireballs.push_back(fireball);
	physicsManager->addObserver(fireball);
	return fireball;
}

vector<Fireball*>& FireballFactory::getFireballs()
{
	return fireballs;
}