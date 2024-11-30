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

int Level::selectCharacter()
{
	std::cout << "Select Character! \n";
	Button chooseCharacterTxt("./Resources/Background/PagesBackground/ChooseCharacterTxt.png");
	Button marioBtn("./Resources/Background/PagesBackground/mario.png");
	Button luigiBtn("./Resources/Background/PagesBackground/luigi.png");
	sf::RenderWindow chooseWindow(sf::VideoMode(800, 800), "Choose Character", sf::Style::Titlebar | sf::Style::Close);

	while (chooseWindow.isOpen()) {
		// Process events
		sf::Event event;
		while (chooseWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				chooseWindow.close();
			}
		}

		if (marioBtn.isClicked(chooseWindow, event)) {
			std::cout << "Choose Mario! \n";
			return 1;
		}
		if (marioBtn.isHover(chooseWindow)) {
			marioBtn.setOpacity(255);
		}
		else {
			marioBtn.setOpacity(128);
		}

		if (luigiBtn.isClicked(chooseWindow, event)) {
			std::cout << "Choose Luigi! \n";
			return 2;
		}
		if (luigiBtn.isHover(chooseWindow)) {
			luigiBtn.setOpacity(255);
		}
		else {
			luigiBtn.setOpacity(128);
		}

		chooseWindow.clear();
		chooseCharacterTxt.draw(chooseWindow, 130, 30);
		marioBtn.draw(chooseWindow, 50, 200);
		luigiBtn.draw(chooseWindow, 450, 170);

		chooseWindow.display();
	}


	return 0;
}

int Level::run(string lv)
{
	std::cout << "Start play game with level " << lv << std::endl;
	selectCharacter();
	map = loadMap(lv);
	//shared_ptr<Character> mario = make_shared<Mario>();
	//physicsManager.addObserver(mario.get());



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