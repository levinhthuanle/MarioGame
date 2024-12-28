#include "Level.h"
#include "ResourcesManager.h"
#include "Components.h"
#include "ConvertSketch.h"
using namespace std;

Collision* Collision::instance = nullptr;

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

bool Level::continueScreen() {
	return 1;
}

int Level::win()
{
    sf::RenderWindow winWindow(sf::VideoMode(700, 400), "Mario Game", sf::Style::Titlebar | sf::Style::Close);

    sf::Texture bgTexture;
    sf::Texture textWinTexture;
    textWinTexture.loadFromFile("Resources/Background/youwinText.png");
    bgTexture.loadFromFile("Resources/Background/youWinBackground.jpg");
    sf::Sprite bgSprite(bgTexture);
    sf::Sprite textWinSprite(textWinTexture);

    // Scale the image to fit the winWindow
    bgSprite.setScale(static_cast<float>(winWindow.getSize().x) / bgSprite.getTexture()->getSize().x,
                      static_cast<float>(winWindow.getSize().y) / bgSprite.getTexture()->getSize().y);
    textWinSprite.setPosition(90, 10);
    textWinSprite.setScale(0.5, 0.5);

    while (winWindow.isOpen()) {
        sf::Event event;
        while (winWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                winWindow.close();
                return 4;
            }
        }

        winWindow.clear();
        winWindow.draw(bgSprite);
        winWindow.draw(textWinSprite);
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
	sf::RenderWindow& window = ResourcesManager::getInstance().getWindow();
	texturemanager->loadTextures();

	point = 0;
	lifeHealth = 3;
	Map& map = ResourcesManager::getInstance().getMap();
	std::cout << "Start play game with level " << lv << std::endl;
	selectCharacter();

	Image sketch;
	if (!sketch.loadFromFile("./Resources/Continue/" + lv + ".png") or !continueScreen()) {
		convertSketch("./Resources/Stages/" + lv + "/sketch_edited.png", map, objMap, gameObjects, bricks, luckyblocks, enemies, items, character);
	}
	else {
		convertSketch("./Resources/Continue/" + lv + ".png", map, objMap, gameObjects, bricks, luckyblocks, enemies, items, character);
	}
	

	for (auto x : enemies) {
		PhysicsAppliedObject* obj = dynamic_cast<PhysicsAppliedObject*>(x);
		if (obj)
			physicsManager.addObserver(obj);
	}

	/*map.removeGameObj(objMap, bricks, luckyblocks, items, 17, 10);*/

	if (lv == "3") {
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
				convertToSketch(objMap, map.getMap(), "./Resources/Continue/" + lv + ".png", character);
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

		int view_x = character->m_sprite.getGlobalBounds().left - WIDTH;
		if (view_x < CELL_SIZE) {
			view_x = CELL_SIZE;
		}
		else if (view_x > (objMap.size() - 1) * CELL_SIZE - window.getSize().x) {
			view_x = (objMap.size() - 1) * CELL_SIZE - window.getSize().x;
		}

		int veiw_y = character->m_sprite.getGlobalBounds().top - HEIGHT;
		if (veiw_y < CELL_SIZE) {
			veiw_y = CELL_SIZE;
		}
		else if (veiw_y > (objMap[0].size() - 1) * CELL_SIZE - window.getSize().y) {
			veiw_y = (objMap[0].size() - 1) * CELL_SIZE - window.getSize().y;
		}

		for (auto x : enemies) {
			if (x->m_sprite.getGlobalBounds().left >= view_x && x->m_sprite.getGlobalBounds().left <= view_x + WIDTH * 2
				&& x->m_sprite.getGlobalBounds().top >= veiw_y && x->m_sprite.getGlobalBounds().top <= veiw_y + HEIGHT * 2) {
				if (dynamic_cast<PhysicsAppliedObject*>(x)) {
					PhysicsAppliedObject* obj = dynamic_cast<PhysicsAppliedObject*>(x);
					physicsManager.addObserver(obj);
				}
			}
			else {
				if (dynamic_cast<PhysicsAppliedObject*>(x)) {
					PhysicsAppliedObject* obj = dynamic_cast<PhysicsAppliedObject*>(x);
					physicsManager.removeObserver(obj);
				}
			}
		}

		sf::Time elapsed = clock.restart();
		if (elapsed.asSeconds() < deltaTime) {
			sf::sleep(sf::seconds(deltaTime - elapsed.asSeconds()));
		}

		// Move and jump for character
		character->checkAction(&physicsManager, fireballFactory);

		physicsManager.updatePhysics(deltaTime, map, objMap, Collision::getInstance());

		for (pair<int, GameObject*> x : Collision::getInstance()->character) {
			if (x.second) {
				if (x.first == 0) {
					cout << x.second->m_name << endl;
					if (x.second->m_name == "Lucky Block") {
						x.second->tryBreak();
						map.spawnMushroom(objMap, gameObjects, x.second);
						x.second->m_name = "Steel";
						SoundManager::getInstance()->playSoundBreakBlock();
					}
					else if (x.second->m_name == "Brick" && character->canUBreakBrick()) {
						map.removeGameObj(objMap, bricks, luckyblocks, items, enemies, x.second);
					}
				}

				chrono::high_resolution_clock::time_point now = chrono::high_resolution_clock::now();
				if (x.first == 1) {
					if (x.second->m_name == "Dead") {
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
					else if (x.second->m_name == "Goomba" and now - lastCollisionEnemy >= chrono::milliseconds(500)) {
						lastCollisionEnemy = now;
						physicsManager.removeObserver(dynamic_cast<PhysicsObserver*>(x.second));
						map.removeGameObj(objMap, bricks, luckyblocks, items, enemies, x.second);
						character->setVelocity(0, -400);
					}
					else if (x.second->m_name == "Koopa" and now - lastCollisionEnemy >= chrono::milliseconds(500)) {
						lastCollisionEnemy = now;
						Koopa* koopa = dynamic_cast<Koopa*>(x.second);
						if (koopa->isRolling()) {
							physicsManager.removeObserver(dynamic_cast<PhysicsObserver*>(koopa));
							map.removeGameObj(objMap, bricks, luckyblocks, items, enemies, x.second);
							character->setVelocity(0, -400);
						}
						else {
							koopa->startRolling();
							character->setVelocity(0, -400);
						}
					}
				}

				if (x.first != 1) {
					if (now - lastCollisionEnemy >= chrono::milliseconds(500) and (x.second->m_name == "Goomba" or x.second->m_name == "Koopa")) {
						lastCollisionEnemy = now;
						--lifeHealth;
						if (dynamic_cast<SuperState*>(character->getState()) or dynamic_cast<FireState*>(character->getState()))
							character->setNormalState();
						cout << "Touch " << x.second->m_name << endl;
						cout << "Life health: " << lifeHealth << endl;
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

				if (x.second->m_name == "Flag") {
					std::cout << "Touch " << x.second->m_name << std::endl;
					win();
					return 3;
				}
				if (x.second->m_name == "Coin") {
					std::cout << "Touch " << x.second->m_name << std::endl;
					point += 5;
					SoundManager::getInstance()->playSoundCoin();
					map.removeGameObj(objMap, bricks, luckyblocks, items, enemies, x.second);
					break;
				}
				if (x.second->m_name == "Mushroom") {
					std::cout << "Touch " << x.second->m_name << std::endl;
					map.removeGameObj(objMap, bricks, luckyblocks, items, enemies, x.second);
					if (lifeHealth < 3) lifeHealth++;
					SoundManager::getInstance()->playSoundFireworks();

					if (dynamic_cast<NormalState*>(character->getState()))
						character->setSuperState();
					else if (dynamic_cast<SuperState*>(character->getState()))
						character->setFireState();
					map.removeGameObj(objMap, bricks, luckyblocks, items, enemies, x.second);
					break;
				}
			}
		}

		for (pair<Fireball*, GameObject*> x : Collision::getInstance()->fireball) {
			if (x.second) {
				if (x.second->m_name == "Goomba") {
					physicsManager.removeObserver(dynamic_cast<PhysicsObserver*>(x.second));
					map.removeGameObj(objMap, bricks, luckyblocks, items, enemies, x.second);
				}
				else if (x.second->m_name == "Koopa") {
					physicsManager.removeObserver(dynamic_cast<PhysicsObserver*>(x.second));
					map.removeGameObj(objMap, bricks, luckyblocks, items, enemies, x.second);
				}
			}
		}

		int charPos = (character->m_sprite).getGlobalBounds().left;
		mainView.setCenter(charPos, HEIGHT / 2);

		// Draw items
		window.clear(sf::Color::Cyan);
		window.draw(bg_sprite);
		window.setView(mainView);
		map.drawMap(character->m_sprite, window);
		window.draw(character->m_sprite);
		vector<Fireball*>& fireballs = fireballFactory.getFireballs();

		vector<Fireball*>::iterator it = fireballs.begin();
		while (it != fireballs.end()) {
			if ((*it)->isDeleted()) {
				delete (*it);
				it = fireballs.erase(it);
			}
			else {
				window.draw((*it)->m_sprite);
				++it;
			}
		}

		window.setView(uiView);
		pauseBtn.draw(window, 100, 50);
		pointText.draw(window);
		heartBtn.draw(window);
		if (lifeHealth >= 2) heart1Btn.draw(window);
		else heartWhiteBtn.draw(window);
		if (lifeHealth >= 3) heart2Btn.draw(window);
		else heartwhite2Btn.draw(window);

		window.display();
	}
}
