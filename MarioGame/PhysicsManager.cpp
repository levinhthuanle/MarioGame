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

// 0 - not collision below, 1 - collision below, whatUJustTouch - objects that are touched on top, bottom, left, right sequentially
int PhysicsAppliedObject::checkObstacle(float deltaTime, Map map, std::pair<int, int>& pos,vector<vector<GameObject*>>& objMap, vector<GameObject*>& whatUJustTouch)
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

    whatUJustTouch.push_back(objMap[int(midX)][floor(futureTop)]); //top
    whatUJustTouch.push_back(objMap[int(midX)][floor(futureBottom)]); //bottom
    whatUJustTouch.push_back(objMap[floor(futureLeft)][int(midY)]); //left
    whatUJustTouch.push_back(objMap[floor(futureRight)][int(midY)]); //right

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
        pos.first = int(midX);
        pos.second = floor(futureTop);
        return grids[int(midX)][floor(futureTop)].getType();
    }
    return ground;
}

int PhysicsAppliedObject::checkObstacleE(float deltaTime, Map map, vector<vector<GameObject*>>& objMap, Collision* collision, vector<GameObject*>& whatUJustTouch)
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

    whatUJustTouch.push_back(objMap[int(midX)][floor(futureTop)]); //top
    whatUJustTouch.push_back(objMap[int(midX)][floor(futureBottom)]); //bottom
    whatUJustTouch.push_back(objMap[floor(futureLeft)][int(midY)]); //left
    whatUJustTouch.push_back(objMap[floor(futureRight)][int(midY)]); //right

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

bool PhysicsObserver::isDeleted()
{
    return deleteMark;
}