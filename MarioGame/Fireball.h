#pragma once
#include "PhysicsManager.h"

// Flyweight Factory
class Fireball : public PhysicsAppliedObject {
protected:

public:
	Fireball(const shared_ptr<sf::Texture> texture, float x, float y, int vel);

	void update(float deltaTime, Map map, vector<vector<GameObject*>>& objMap, Collision* collision) override;

	int checkObstacle(float deltaTime, Map map, vector<vector<GameObject*>>& objMap, Collision* collision);
};

class FireballFactory {
private:
	vector<Fireball*> fireballs;
	shared_ptr<sf::Texture> texture;

public:
	FireballFactory();

	Fireball* createFireball(PhysicsManager* physicsManager, float x, float y, int vel);

	vector<Fireball*>& getFireballs();
};