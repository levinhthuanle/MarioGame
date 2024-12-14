#include "Level.h"
#include "ResourcesManager.h"
#include "Components.h"
#include "ConvertSketch.h"
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
			physicsManager.addObserver(character.get());
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
			physicsManager.addObserver(character.get());
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
	
	convertSketch(lv, map, enemies, items);

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
			character->jump();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			character->moveLeft();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) or sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			character->setCrouch();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			character->moveRight();

		physicsManager.updatePhysics(deltaTime, map);

		std::cout << "Game object size: " <<  gameObjects.size() << std::endl;
		std::cout << "Items size: " <<  items.size() << std::endl;
		for (GameObject* o : items)
			o->update(deltaTime);

		sf::RectangleShape border(sf::Vector2f(character->m_sprite.getGlobalBounds().width, character->m_sprite.getGlobalBounds().height));
		border.setPosition(character->m_sprite.getPosition());
		border.setOutlineThickness(5);
		border.setOutlineColor(sf::Color::Red);
		border.setFillColor(sf::Color::Transparent);


		window.clear(sf::Color::Cyan);
		int charPos = (character->m_sprite).getGlobalBounds().left;
		map.drawMap(charPos - WIDTH / 2, window);
		/*for (GameObject* o : items) {
			o->draw(window);
		}*/
		window.draw(character->m_sprite);
		//window.draw(border);
		window.display();
	}

	return 0;
}