#pragma once
#include "PhysicsManager.h"
#include "SoundManager.h"
using namespace std;

class Character;

// State
class CharacterState
{
protected:

public:
	virtual void updateTexture(Character& character) = 0;

	virtual void crouch(Character& character) = 0;
};

class NormalState : public CharacterState
{
public:
	NormalState(Character& character);

	void updateTexture(Character& character);

	void crouch(Character& character);
};

class SuperState : public CharacterState
{
public:
	SuperState(Character& character);

	void updateTexture(Character& character);

	void crouch(Character& character);
};

class FireState : public CharacterState
{
public:
	FireState(Character& character);

	void updateTexture(Character& character);

	void crouch(Character& character);
};





class Character : public PhysicsAppliedObject
{
protected:
	CharacterState* currentState;

	// 0-1: stand
	// 2-3: jump
	// 4: die
	// 5-10: walk
	// 11-12: slide
	vector<sf::Texture> textures = vector<sf::Texture>(17);

	// 0-1: stand
	// 2-3: crouch
	// 4-5: jump
	// 6-7: slide
	// 8-13: walk
	// 14-17: climb
	vector<sf::Texture> superTextures = vector<sf::Texture>(14);
	vector<sf::Texture> fireTextures = vector<sf::Texture>(16);

	vector<sf::Texture> currentTexture = textures;

	vector<sf::Texture> toSuper = vector<sf::Texture>(10);
	vector<sf::Texture> toFire = vector<sf::Texture>(10);
	vector<sf::Texture> Super2Small = vector<sf::Texture>(10);
	vector<sf::Texture> Fire2Small = vector<sf::Texture>(10);

	// Texture's time control attributes
	chrono::high_resolution_clock::time_point lastUpdate = chrono::high_resolution_clock::now();
	const chrono::milliseconds updateInterval{100};

	// Constant attributes
	float maxVelocityX = -1;
	int inertia = 15;
	bool breakBrick = 0;
	bool fireable = 0;

	// Temporal attributes
	bool jumping = false;
	bool crouching = false;
	bool direction = 0;	// face direction: 0 - right, 1 - left		
	int currentWalkTexture = 0;	// 0 1 2

public:
	Character();

	void update(float deltaTime, Map map) override;

	virtual void updateTexture();

	virtual void jump() = 0;

	void checkAction() {
		SoundManager* soundManager = SoundManager::getInstance();


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) or sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			this->jump();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			this->moveLeft();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) or sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			this->setCrouch();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			this->moveRight();

	}

	void moveLeft();

	void moveRight();

	void setCrouch();


	virtual ~Character() = default;

	friend class NormalState;
	friend class SuperState;
	friend class FireState;
};





class Mario : public Character
{
public:
	Mario();

	void jump();

	//void setCrouch();

	~Mario() = default;
};

class Luigi : public Character
{
public:
	Luigi();

	void jump();

	//void setCrouch();

	~Luigi() = default;
};