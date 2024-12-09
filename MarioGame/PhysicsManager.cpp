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

// 0 - right, 1 - left, 2 - down, 3 - up
int PhysicsAppliedObject::checkObstacle(float deltaTime, Map map)
{
    const vector<vector<Cell>>& grids = map.getMap();
    //const vector<vector<Sprite>>& sprites = map.getSpriteGrid();
    float x = m_sprite.getPosition().x;
    float y = m_sprite.getPosition().y;

    int midX = static_cast<int>((x + m_sprite.getGlobalBounds().width / 2) / static_cast<float>(CELL_SIZE));
    int midY = static_cast<int>((y + m_sprite.getGlobalBounds().height / 2) / static_cast<float>(CELL_SIZE));
    int left = static_cast<int>(x / static_cast<float>(CELL_SIZE));
    int right = static_cast<int>((x + m_sprite.getGlobalBounds().width) / static_cast<float>(CELL_SIZE));
    int top = static_cast<int>(y / static_cast<float>(CELL_SIZE));
    int bottom = static_cast<int>((y + m_sprite.getGlobalBounds().height) / static_cast<float>(CELL_SIZE));

    cout << left << " " << right << " " << top << " " << bottom << endl;

    // Check bounds to prevent out-of-range access
    if (left < 0 || right >= grids.size() || top < 0 || bottom >= grids[0].size()) {
        cout << "Out of bounds access detected!" << endl;
        return 0;
    }

    // Check collisions and adjust position/velocity
    if (velocity.x > 0) { // Moving right
        if (grids[right][midY].getType() != 0 /*&& sprites[x][y].getLocalBounds().intersects(m_sprite.getLocalBounds())*/) {
            velocity.x = 0;
            return 0;
        }
    }
    else if (velocity.x < 0) { // Moving left
        if (grids[left][midY].getType() != 0) {
            velocity.x = 0;
            return 1;
        }
    }

    if (velocity.y > 0) { // Moving down
        if (grids[midX][bottom].getType() != 0) {
            velocity.y = 0;
            return 2;
        }
    }
    else if (velocity.y < 0) { // Moving up
        if (grids[midX][top].getType() != 0 ) {
            velocity.y = 0;
            return 3;
        }
    }
}

bool PhysicsAppliedObject::isObjectCollision(GameObject* gameObject)
{
	if (m_sprite.getGlobalBounds().intersects(gameObject->m_sprite.getGlobalBounds()))
		return true;
	return false;
}
