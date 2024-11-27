#pragma once
#include "Global.h"
#include "GameObject.h"
#include "Map.h"
#include <vector>
#include <chrono>
#include <cmath>

// Observer

using namespace std;

class PhysicsObserver
{
public:
	virtual void update(float deltaTime) = 0;
};

class PhysicsManager
{
protected:
	vector<PhysicsObserver*> observers;

public:
	void addObserver(PhysicsObserver* observer);

	void rermoveObserver(PhysicsObserver* observer);

	void updatePhysics(float deltaTime);
};

class PhysicsAppliedObject : public GameObject, public PhysicsObserver
{
protected:
	sf::Vector2f velocity;
	const float gravity = 30;

public:
	void update(float deltaTime, Map map);

	void checkObstacle(float deltaTime, Map map);

	bool isObjectCollision(GameObject* gameObject);
};