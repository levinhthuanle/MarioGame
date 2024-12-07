#include "PhysicsManager.h"

void PhysicsManager::addObserver(PhysicsObserver* observer)
{
	if (find(observers.begin(), observers.end(), observer) != observers.end())
		observers.push_back(observer);
}

void PhysicsManager::rermoveObserver(PhysicsObserver* observer)
{
	for (vector<PhysicsObserver*>::iterator i = observers.begin(); i != observers.end(); ++i)
		if (*i == observer)
			observers.erase(i);
}

void PhysicsManager::updatePhysics(float deltaTime, Map map)
{
	for (PhysicsObserver* o : observers)
		o->update(deltaTime, map);
}



void PhysicsAppliedObject::update(float deltaTime, Map map)
{
	// Apply gravity
	velocity.y += gravity * deltaTime;

	checkObstacle(deltaTime, map);

	m_sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);
}

void PhysicsAppliedObject::checkObstacle(float deltaTime, Map map)
{
	vector<vector<Cell>> grids = map.getMap();
	sf::FloatRect futureBounds = m_sprite.getGlobalBounds();
	futureBounds.top += velocity.y * deltaTime;
	futureBounds.left += velocity.x * deltaTime;

	int top = futureBounds.top / CELL_SIZE;
	int bot = (futureBounds.top + futureBounds.height) / CELL_SIZE;
	int left = futureBounds.left / CELL_SIZE;
	int right = (futureBounds.left + futureBounds.width) / CELL_SIZE;
	if (!map.isCollectable(grids[left][top]) or !map.isCollectable(grids[right][top])
		or !map.isCollectable(grids[left][bot]) or !map.isCollectable(grids[right][bot])) {
		velocity.x = 0;
		velocity.y = 0;
	}
}

bool PhysicsAppliedObject::isObjectCollision(GameObject* gameObject)
{
	sf::FloatRect bounds = m_sprite.getGlobalBounds();
	if (bounds.intersects(gameObject->m_sprite.getGlobalBounds()))
		return true;
	return false;
}
