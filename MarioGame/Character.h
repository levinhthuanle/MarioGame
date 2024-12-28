#pragma once
#include "PhysicsManager.h"
#include "SoundManager.h"
#include "Fireball.h"

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

	vector<sf::Texture> toSuper = vector<sf::Texture>(10);
	vector<sf::Texture> toFire = vector<sf::Texture>(10);
	vector<sf::Texture> Super2Small = vector<sf::Texture>(10);
	vector<sf::Texture> Fire2Small = vector<sf::Texture>(10);

	// Texture's time control attributes
	chrono::high_resolution_clock::time_point lastUpdate = chrono::high_resolution_clock::now();
	const chrono::milliseconds updateInterval{100};

	chrono::high_resolution_clock::time_point lastFire = chrono::high_resolution_clock::now();

	// Constant attributes
	float maxVelocityX = -1;
	int jumpForce = 700;
	int inertia = 20;
	bool breakBrick = 0;
	bool fireable = 0;

	// Temporal attributes
	bool jumping = false;
	bool crouching = false;
	bool direction = 0;	// face direction: 0 - right, 1 - left		
	int currentWalkTexture = 0;	// 0 1 2

public:
	Character();

	CharacterState* getState();

	void setState(CharacterState* newState);

	void setNormalState();

	void setSuperState();

	void setFireState();

	void setVelocity(float x, float y);

	void setJumpForce(int force) {
		this->jumpForce = force;
	}

	bool canUBreakBrick() {
		return this->breakBrick;
	}

	void update(float deltaTime, Map map, vector<vector<GameObject*>>& objMap, Collision* collision) override;

	int checkObstacle(float deltaTime, Map map, vector<vector<GameObject*>>& objMap, Collision* collision) override;

	virtual void updateTexture();

	virtual void jump() = 0;

	void checkAction(PhysicsManager* physicsManager, FireballFactory& fireballFactory);

	void moveLeft();

	void moveRight();

	void setCrouch();

	void fire(PhysicsManager* physicsManager, FireballFactory& fireballFactory);

	void setPosition(sf::Vector2f pos);

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

	~Mario() = default;
};

class Luigi : public Character
{
public:
	Luigi();

	void jump();

	~Luigi() = default;
};
