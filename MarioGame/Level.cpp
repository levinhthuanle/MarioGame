#include "Level.h"

using namespace std;

Level::Level(vector<GameObject*> objects, Character* c) : gameObjects(objects)
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
		this_thread::sleep_for(chrono::microseconds(25));

		physicsManager.updatePhysics(0.025);

	}
}