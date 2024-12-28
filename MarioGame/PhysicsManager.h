#pragma once
#include "Global.h"
#include "GameObject.h"
#include "Map.h"
#include <vector>
#include <chrono>
#include <cmath>

using namespace std;



class Fireball;

// Singleton
class Collision
{
private:
	static Collision* instance;

	Collision() = default;

	Collision(const Collision&) = delete;

	Collision& operator=(Collision) = delete;

public:
	vector<pair<int, GameObject*>> character;
	vector<pair<Fireball*, GameObject*>> fireball;
	static Collision* getInstance();
};



// Observer
class PhysicsObserver
{
protected:
	bool deleteMark = false;
public:
	virtual void update(float deltaTime, Map map, vector<vector<GameObject*>>& objMap, Collision* collision) = 0;

	bool isDeleted();

	virtual ~PhysicsObserver() = default;
};

class PhysicsManager
{
protected:
	vector<PhysicsObserver*> observers;

public:
	void addObserver(PhysicsObserver* observer);

	void removeObserver(PhysicsObserver* observer);

	void updatePhysics(float deltaTime, Map map, vector<vector<GameObject*>>& objMap, Collision* collision);
};

class PhysicsAppliedObject : public GameObject, public PhysicsObserver
{
protected:
	sf::Vector2f velocity;
	const float gravity = 1000;

public:
	void update(float deltaTime, Map map, vector<vector<GameObject*>>& objMap, Collision* collision) override;

	int checkObstacle(float deltaTime, Map map, std::pair<int, int>& pos);

	int checkObstacleE(float deltaTime, Map map, std::pair<int, int>& pos, vector<vector<GameObject*>>& objMap, vector<GameObject*>& whatUJustTouch);

	int checkObstacle(float deltaTime, Map map, std::pair<int, int>& pos,vector<vector<GameObject*>>& objMap, vector<GameObject*>& whatUJustTouch);

	virtual int checkObstacle(float deltaTime, Map map, vector<vector<GameObject*>>& objMap, Collision* collision);


	bool isObjectCollision(GameObject* gameObject);
};