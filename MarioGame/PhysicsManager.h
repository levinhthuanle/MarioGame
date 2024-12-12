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
	virtual void update(float deltaTime, Map map) = 0;
};

class PhysicsManager
{
protected:
	vector<PhysicsObserver*> observers;

public:
	void addObserver(PhysicsObserver* observer);

	void rermoveObserver(PhysicsObserver* observer);

	void updatePhysics(float deltaTime, Map map);
};

class PhysicsAppliedObject : public GameObject, public PhysicsObserver
{
protected:
	sf::Vector2f velocity;
	const float gravity = 500;

public:
	virtual void update(float deltaTime, Map map) override;

	int checkObstacle(float deltaTime, Map map);

	bool isObjectCollision(GameObject* gameObject);
};