#include "PhysicsManager.h"



Collision* Collision::getInstance()
{
    if (!instance)
        instance = new Collision();
    return instance;
}





void PhysicsManager::addObserver(PhysicsObserver* observer)
{
	if (observer and find(observers.begin(), observers.end(), observer) == observers.end())
		observers.push_back(observer);
}

void PhysicsManager::removeObserver(PhysicsObserver* observer)
{
	observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
}

void PhysicsManager::updatePhysics(float deltaTime, Map map, vector<vector<GameObject*>>& objMap, Collision* collision)
{
    collision->character.clear();
    collision->fireball.clear();
    for (PhysicsObserver* observer : observers)
        observer->update(deltaTime, map, objMap, collision);

    vector<PhysicsObserver*>::iterator it = observers.begin();
    while (it != observers.end()) {
        if ((*it)->isDeleted()) {
            it = observers.erase(it);
        }
        else
            ++it;
    }
}



void PhysicsAppliedObject::update(float deltaTime, Map map, vector<vector<GameObject*>>& objMap, Collision* collision)
{
	// Apply gravity
	velocity.y += gravity * deltaTime;

	checkObstacle(deltaTime, map, objMap, collision);

	m_sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);
}

// 1 - right, 2 - left, 10 - below
int PhysicsAppliedObject::checkObstacle(float deltaTime, Map map, vector<vector<GameObject*>>& objMap, Collision* collision)
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

    // right
    if (grids[int(futureRight)][int(top)].getType() != 0
        or grids[int(futureRight)][int(midY)].getType() != 0
        or grids[int(futureRight)][int(bottom)].getType() != 0) {
        velocity.x = 0;
        ans += 1;
    }
    // left
    if (grids[int(futureLeft)][int(top)].getType() != 0
        or grids[int(futureLeft)][int(midY)].getType() != 0
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
    }
    return ans;
}

bool PhysicsAppliedObject::isObjectCollision(GameObject* gameObject)
{
	if (m_sprite.getGlobalBounds().intersects(gameObject->m_sprite.getGlobalBounds()))
		return true;
	return false;
}

bool PhysicsObserver::isDeleted()
{
    return deleteMark;
}