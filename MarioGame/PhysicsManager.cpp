#include "PhysicsManager.h"

void PhysicsManager::addObserver(PhysicsObserver* observer)
{
	if (observer and find(observers.begin(), observers.end(), observer) == observers.end())
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

// 0 - not collision below, 1 - collision below
int PhysicsAppliedObject::checkObstacle(float deltaTime, Map map)
{
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

    cout << left << " " << right << " " << top << " " << bottom << endl;

    // Check bounds to prevent out-of-range access
    if (left < 0 || right >= grids.size() || top < 0 || bottom >= grids[0].size()) {
        cout << "Out of bounds access detected!" << endl;
        return 0;
    }

    bool ground = false;

    // right
    if (grids[floor(futureRight)][int(top)].getType() != 0
        or grids[floor(futureRight)][int(bottom)].getType() != 0
        or grids[floor(futureRight)][int(midY)].getType() != 0) {
        velocity.x = 0;
    }
    // left
    if (grids[floor(futureLeft)][int(top)].getType() != 0
        or grids[floor(futureLeft)][int(bottom)].getType() != 0
        or grids[floor(futureLeft)][int(midY)].getType() != 0) {
        velocity.x = 0;
    }
    // down
    if (grids[int(left)][floor(futureBottom)].getType() != 0
        or grids[int(right)][floor(futureBottom)].getType() != 0
        or grids[int(midX)][floor(futureBottom)].getType() != 0) {
        velocity.y = 0;
        ground = true;
    }
    // up
    if (grids[int(left)][floor(futureTop)].getType() != 0
        or grids[int(right)][floor(futureTop)].getType() != 0
        or grids[int(midX)][floor(futureTop)].getType() != 0) {
        velocity.y = 0;
    }
    return ground;
}

bool PhysicsAppliedObject::isObjectCollision(GameObject* gameObject)
{
	if (m_sprite.getGlobalBounds().intersects(gameObject->m_sprite.getGlobalBounds()))
		return true;
	return false;
}
