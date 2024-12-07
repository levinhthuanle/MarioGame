#include "Level.h"

using namespace std;

Level::Level(vector<GameObject*> objects, Character* c) : gameObjects(objects), character(c)
{
	physicsManager.addObserver(c);
	for (GameObject* o : objects) {
		PhysicsAppliedObject* obj = dynamic_cast<PhysicsAppliedObject*>(o);
		if (obj)
			physicsManager.addObserver(obj);
	}
}

int Level::run(string lv)
{
	while (true) {
		float deltaTime = 0.025;

		this_thread::sleep_for(chrono::microseconds(25));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) or sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			character->setForceY(-60);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			character->setForceX(-30);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) or sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			character->setForceY(-60);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			character->setForceX(30);

		physicsManager.updatePhysics(deltaTime, map);
	}
}