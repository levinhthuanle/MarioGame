#include "Level.h"
#include "ResourcesManager.h"
#include "Components.h"
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
	map = loadMap(lv);
	shared_ptr<Character> mario = make_shared<Mario>();


	//while (true) {
	//	this_thread::sleep_for(chrono::microseconds(25));

	//	physicsManager.updatePhysics(0.025);

	//}

	sf::RenderWindow& window = ResourcesManager::getInstance().getWindow();
	sf::Event event;

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return 4;
			}

		}
		window.clear(sf::Color::Black);
		map.drawMap(1200, window);
		window.display();
	}

	return 0;
}