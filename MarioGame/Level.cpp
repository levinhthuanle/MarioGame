#include "Level.h"
#include "ResourcesManager.h"
#include "Components.h"
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
			character = make_shared<Mario>();
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
			character = make_shared<Luigi>();
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

	physicsManager.addObserver(character.get());

	sf::RenderWindow& window = ResourcesManager::getInstance().getWindow();
	sf::Event event;
		
	sf::Clock clock;
	float deltaTime = 0.025f;

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return 4;
			}
		}

		sf::Time elapsed = clock.restart();
		if (elapsed.asSeconds() < deltaTime) {
			sf::sleep(sf::seconds(deltaTime - elapsed.asSeconds()));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) or sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			character->setForceY(-60);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			character->setForceX(-500);
			//character->m_sprite.move(-60, 0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) or sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			character->setCrouch();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			character->setForceX(500);

		//physicsManager.updatePhysics(deltaTime, map);
		character->update(deltaTime, map);

		window.clear(sf::Color::Cyan);
		map.drawMap(0, window);
		window.draw(character->m_sprite);
		window.display();
	}

	return 0;
}