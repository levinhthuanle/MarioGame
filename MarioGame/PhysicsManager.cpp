#include "PhysicsManager.h"

void PhysicsManager::addObserver(PhysicsObserver* observer)
{
	if (observer and find(observers.begin(), observers.end(), observer) == observers.end())
		observers.push_back(observer);
}

void PhysicsManager::removeObserver(PhysicsObserver* observer)
{
	observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
}

void PhysicsManager::updatePhysics(float deltaTime, Map map)
{
    for (PhysicsObserver* observer : observers)
        observer->update(deltaTime, map);

    vector<PhysicsObserver*>::iterator it = observers.begin();
    while (it != observers.end()) {
        if ((*it)->isDeleted()) {
            delete (*it);
            it = observers.erase(it);
        }
        else
            ++it;
    }
}



void PhysicsAppliedObject::update(float deltaTime, Map map)
{
	// Apply gravity
	velocity.y += gravity * deltaTime;

    std::pair<int, int> temp = { 0, 0 };
	checkObstacle(deltaTime, map, temp);

	m_sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);
}

// 1 - right, 2 - left, 10 - below
int PhysicsAppliedObject::checkObstacle(float deltaTime, Map map, std::pair<int, int>& pos)
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

    // cout << left << " " << right << " " << top << " " << bottom << endl;

    // Check bounds to prevent out-of-range access
    if (left < 0 || right >= grids.size() || top < 0 || bottom >= grids[0].size()) {
        cout << "Out of bounds access detected!" << endl;
        return 0;
    }

    int ans = 0;

    // right
    if (grids[floor(futureRight)][int(top)].getType() != 0
        or grids[floor(futureRight)][int(bottom)].getType() != 0
        or grids[floor(futureRight)][int(midY)].getType() != 0) {
        velocity.x = 0;
        ans += 1;
    }
    // left
    if (grids[floor(futureLeft)][int(top)].getType() != 0
        or grids[floor(futureLeft)][int(bottom)].getType() != 0
        or grids[floor(futureLeft)][int(midY)].getType() != 0) {
        velocity.x = 0;
        ans += 2;
    }
    // down
    if (grids[int(left)][floor(futureBottom)].getType() != 0
        or grids[int(right)][floor(futureBottom)].getType() != 0
        or grids[int(midX)][floor(futureBottom)].getType() != 0) {
        velocity.y = 0;
        ans += 10;
    }
    // up
    if (grids[int(left)][floor(futureTop)].getType() != 0
        or grids[int(right)][floor(futureTop)].getType() != 0
        or grids[int(midX)][floor(futureTop)].getType() != 0) {
        velocity.y = 0;

        // 1 brick
        // 2 lucky box
        //if (grids[x][y].getType())
        std::string type = "Brick";
        if (grids[int(midX)][floor(futureTop)].getType() == 2)
            type = "Lucky Box";
        if (grids[int(midX)][floor(futureTop)].getType() == 0)
            type = "Nothing";
        std::cout << "Try to break " << type << std::endl;
        pos.first = int(midX);
        pos.second = floor(futureTop);
        return grids[int(midX)][floor(futureTop)].getType();
    }
    return ans;
}

// 0 - not collision below, 1 - collision below, whatUJustTouch - objects that are touched on top, bottom, left, right sequentially
int PhysicsAppliedObject::checkObstacle(float deltaTime, Map map, /*std::pair<int, int>& pos, */vector<vector<GameObject*>>& objMap, vector<pair<int, GameObject*>>& whatUJustTouch)
{
    whatUJustTouch.clear();
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

    // cout << left << " " << right << " " << top << " " << bottom << endl;

    // Check bounds to prevent out-of-range access
    if (left < 0 || right >= grids.size() || top < 0 || bottom >= grids[0].size()) {
        cout << "Out of bounds access detected!" << endl;
        return 0;
    }

    //top
    whatUJustTouch.push_back(make_pair(0, objMap[int(left)][floor(futureTop)]));
    whatUJustTouch.push_back(make_pair(0, objMap[int(midX)][floor(futureTop)]));
    whatUJustTouch.push_back(make_pair(0, objMap[int(right)][floor(futureTop)]));

    //bottom
    whatUJustTouch.push_back(make_pair(1, objMap[int(left)][floor(futureBottom)]));
    whatUJustTouch.push_back(make_pair(1, objMap[int(midX)][floor(futureBottom)]));
    whatUJustTouch.push_back(make_pair(1, objMap[int(right)][floor(futureBottom)]));

    //left
    whatUJustTouch.push_back(make_pair(2, objMap[floor(futureLeft)][int(top)]));
    whatUJustTouch.push_back(make_pair(2, objMap[floor(futureLeft)][int(midY)]));
    whatUJustTouch.push_back(make_pair(2, objMap[floor(futureLeft)][int(bottom)]));

    //right
    whatUJustTouch.push_back(make_pair(3, objMap[floor(futureRight)][int(top)]));
    whatUJustTouch.push_back(make_pair(3, objMap[floor(futureRight)][int(midY)]));
    whatUJustTouch.push_back(make_pair(3, objMap[floor(futureRight)][int(bottom)]));

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

        // 1 brick
        // 2 lucky box
        //if (grids[x][y].getType())
        std::string type = "Brick";
        if (grids[int(midX)][floor(futureTop)].getType() == 2) {
            type = "Lucky Box";
        }
        if (grids[int(midX)][floor(futureTop)].getType() == 0)
            type = "Nothing";
        std::cout << "Try to break " << type << std::endl;
        //pos.first = int(midX);
        //pos.second = floor(futureTop);
        return grids[int(midX)][floor(futureTop)].getType();
    }
    return ground;
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
