#include "Level.h"
#include "ResourcesManager.h"
#include "Components.h"
#include "ConvertSketch.h"
using namespace std;

// Enemies' textures
TextureManager* TextureManager::instance = nullptr;

Level::Level(vector<GameObject*> objects, Character* c) : gameObjects(objects), character(c)
{
	physicsManager.addObserver(c);
	for (GameObject* o : objects) {
		PhysicsAppliedObject* obj = dynamic_cast<PhysicsAppliedObject*>(o);
		if (obj)
			physicsManager.addObserver(obj);
	}
}

int Level::pause()
{
    sf::RenderWindow pauseWindow(sf::VideoMode(740, 450), "Mario Game", sf::Style::Titlebar | sf::Style::Close);

	Button pauseTxt("./Resources/Background/PagesBackground/GamePauseText.png", 20, 50);
	Button resumeBtn("./Resources/Background/PagesBackground/ContinueText.png", 50, 50);
	Button exitBtn("./Resources/Background/PagesBackground/exitText.png", 50, 150);
    pauseWindow.clear(sf::Color(5, 113, 211)); // Set background color to #0571d3

    while (pauseWindow.isOpen()) {
        sf::Event event;
        while (pauseWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                pauseWindow.close();
                return 4;
            }
			if (resumeBtn.isClicked(pauseWindow, event)) {
				std::cout << "Start Button clicked\n";
				return 1;
			}
			if (resumeBtn.isHover(pauseWindow)) 
				resumeBtn.setOpacity(255);
			else 
				resumeBtn.setOpacity(127);

			if (exitBtn.isClicked(pauseWindow, event)) {
				std::cout << "Start Button clicked\n";
				return 4;
			}
			if (exitBtn.isHover(pauseWindow))
				exitBtn.setOpacity(255);
			else
				exitBtn.setOpacity(127);

        }
		pauseWindow.clear(sf::Color(5, 113, 211));
		pauseTxt.draw(pauseWindow, 130, 5);
		resumeBtn.draw(pauseWindow, 220, 220);
		exitBtn.draw(pauseWindow, 300, 400);	
        pauseWindow.display();
    }

    return 1;
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
			character = new Mario();
			physicsManager.addObserver(character);
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
			character = new Luigi();
			physicsManager.addObserver(character);
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

int Level::win()
{
	sf::RenderWindow winWindow(sf::VideoMode(200, 300), "Mario Game", sf::Style::Titlebar | sf::Style::Close);

	while (winWindow.isOpen()) {
		sf::Event event;
		while (winWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				winWindow.close();
				return 4;
			}
		}

		winWindow.clear();
		winWindow.display();
	}

	return 0;
}

int Level::lose()
{
    sf::RenderWindow loseWindow(sf::VideoMode(700, 400), "Mario Game", sf::Style::Titlebar | sf::Style::Close);

    sf::Texture bgTexture;
	sf::Texture textLoseTexture;
	textLoseTexture.loadFromFile("Resources/Background/loseText.png");
    bgTexture.loadFromFile("Resources/Background/LoseBackground.jpg");
    sf::Sprite bgSprite(bgTexture);
	sf::Sprite textLoseSprite(textLoseTexture);

    // Scale the image to fit the loseWindow
    bgSprite.setScale(static_cast<float>(loseWindow.getSize().x) / bgSprite.getTexture()->getSize().x,
                      static_cast<float>(loseWindow.getSize().y) / bgSprite.getTexture()->getSize().y);
	textLoseSprite.setPosition(90, 10);
	textLoseSprite.setScale(0.5, 0.5);

    while (loseWindow.isOpen()) {
        sf::Event event;
        while (loseWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                loseWindow.close();
                return 4;
            }
        }

        loseWindow.clear();
        loseWindow.draw(bgSprite);
		loseWindow.draw(textLoseSprite);
        loseWindow.display();
    }

    return 0;
}

int Level::run(string lv) {
	TextureManager* texturemanager = TextureManager::getInstance();
	vector<vector<GameObject*>>& objMap = ResourcesManager::getInstance().getObjMap();
	texturemanager->loadTextures();
	point = 0;
	lifeHealth = 3;
	Map& map = ResourcesManager::getInstance().getMap();
	std::cout << "Start play game with level " << lv << std::endl;
	selectCharacter();

	convertSketch(lv, map, objMap, gameObjects, bricks, luckyblocks, enemies, items, character->m_sprite);

	//for (auto x : enemies) {
	//	PhysicsAppliedObject* obj = dynamic_cast<PhysicsAppliedObject*>(x);
	//	if (obj)
	//		physicsManager.addObserver(obj);
	//}

	/*map.removeGameObj(objMap, bricks, luckyblocks, items, 17, 10);*/

	if (lv == "1-3") {
		character->setJumpForce(1400);
	}

	Button pauseBtn("./Resources/Background/PagesBackground/pauseButton.png", 50, 50);
	Button heartBtn("./Resources/item/heart.png", 1450, 30);
	Button heart1Btn("./Resources/item/heart.png", 1500, 30);
	Button heart2Btn("./Resources/item/heart.png", 1550, 30);
	Button heartWhiteBtn("./Resources/item/heartWhite.png", 1500, 30);
	Button heartwhite2Btn("./Resources/item/heartWhite.png", 1550, 30);
	sf::Texture bgTexture;
	bgTexture.loadFromFile("./Resources/background/mariobackground.jpg");
	bg_sprite.setTexture(bgTexture);
	bg_sprite.setPosition(0.f, 0.f);


	TextRemake pointText("Point: " + std::to_string(point), 25, 170, 50);
	pointText.setFillColor(sf::Color::White);

	sf::RenderWindow& window = ResourcesManager::getInstance().getWindow();
	sf::Event event;

	sf::Clock clock;
	float deltaTime = 0.025f;

	sf::View mainView(sf::FloatRect(0, 0, WIDTH, HEIGHT));
	sf::View uiView(sf::FloatRect(0, 0, WIDTH, HEIGHT));

	//for (int i = 0; i < 20; i++) {
	//	map.removeGameObj(gameObjects, gameObjects[i]);
	//}

	while (window.isOpen()) {
		pointText.setText("Point: " + std::to_string(point));
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return 4;
			}

			if (pauseBtn.isClicked(window, event)) {
				SoundManager::getInstance()->playSoundPause();
				std::cout << "Pause clicked!\n";
				int cmd = pause();
				if (cmd == 4) {
					return 3;
				}
			}
		}


		std::pair<int, int> objectBreakPos = { 0, 0 };
		vector<GameObject*> objTouch;
		int objectBreak = character->checkObstacle(deltaTime, map, objectBreakPos, objMap, objTouch);
		if (!objTouch.empty() && objTouch[0] != nullptr) {
			cout<< objTouch[0]->m_name << endl;
			if (objTouch[0]->m_name == "Lucky Block") {
				objTouch[0]->tryBreak();
				map.spawnMushroom(objMap, gameObjects, objTouch[0]);
				objTouch[0]->m_name = "Steel";
				SoundManager::getInstance()->playSoundBreakBlock();
			}
			else if (objTouch[0]->m_name == "Brick" && character->canUBreakBrick()) {
				map.removeGameObj(objMap, bricks, luckyblocks, items, objTouch[0]);
			}
		}

		if (!objTouch.empty() && objTouch[1] != nullptr) {
			if (objTouch[1]->m_name == "Dead") {
				std::cout << "Dead \n";
				lifeHealth--;
				SoundManager::getInstance()->playSoundKick();
				if (lifeHealth == 0) {
					std::cout << "Game Over \n";
					SoundManager::getInstance()->playSoundGameOver();
					lose();
					return 3;
				}
				else {
					character->setVelocity(0, -800);
				}
			}
		}

		//if (objTouch[1] != nullptr && objTouch[1]->m_name == "Pipe") {
		//	std::cout << "Teleport \n";
		//	Pipe* pipe = dynamic_cast<Pipe*>(objTouch[1]);
		//	pipe->teleport(character);
		//	objTouch[1] = nullptr;
		//}

		for (auto x : objTouch) {
			if (x != nullptr) {
				if (x->m_name == "Coin") {
					std::cout << "Touch " << x->m_name << std::endl;
					point += 5;
					SoundManager::getInstance()->playSoundCoin();
					map.removeGameObj(objMap, bricks, luckyblocks, items, x);
					break;
				}
				if (x->m_name == "Mushroom") {
					std::cout << "Touch " << x->m_name << std::endl;
					if (lifeHealth < 3) lifeHealth++;
					SoundManager::getInstance()->playSoundFireworks();
					
					if (dynamic_cast<NormalState*>(character->getState()))
						character->setSuperState();
					map.removeGameObj(objMap, bricks, luckyblocks, items, x);
					break;
				}
				if (x->m_name == "Fire Flower") {
					std::cout << "Touch " << x->m_name << std::endl;
					SoundManager::getInstance()->playSoundFireworks();
					
					character->setFireState();
					map.removeGameObj(objMap, bricks, luckyblocks, items, x);
					break;
				}
			}
		}
		

		sf::Time elapsed = clock.restart();
		if (elapsed.asSeconds() < deltaTime) {
			sf::sleep(sf::seconds(deltaTime - elapsed.asSeconds()));
		}

		// Move and jump for character
		character->checkAction();
		/*std::cout << "Bricks size: " << bricks.size() << std::endl;
		std::cout << "Lucky block size: " << luckyblocks.size() << std::endl;
		std::cout << "Item size: " << items.size() << std::endl;*/

		physicsManager.updatePhysics(deltaTime, map);

		int charPos = (character->m_sprite).getGlobalBounds().left;
		mainView.setCenter(charPos, HEIGHT / 2);

		// Draw items
		window.clear(sf::Color::Cyan);
		window.draw(bg_sprite);
		window.setView(mainView);
		map.drawMap(character->m_sprite, window);
		window.draw(character->m_sprite);

		window.setView(uiView);
		pauseBtn.draw(window, 100, 50); 
		pointText.draw(window);

		heartBtn.draw(window);
		if (lifeHealth >= 2) heart1Btn.draw(window);
			else heartWhiteBtn.draw(window);
		if (lifeHealth == 3) heart2Btn.draw(window);
			else heartwhite2Btn.draw(window);

		window.display();
	}
}
