#pragma once
#include "PhysicsManager.h"

using namespace std;

class Character : public PhysicsAppliedObject
{
protected:
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
	vector<sf::Texture> superTextures = vector<sf::Texture>(18);
	vector<sf::Texture> fireTextures = vector<sf::Texture>(10);

	vector<sf::Texture> currentTexture = textures;

	vector<sf::Texture> toSuper = vector<sf::Texture>(10);

	// Texture's time control attributes
	//chrono::high_resolution_clock::time_point lastUpdate = chrono::high_resolution_clock::now();
	//const chrono::milliseconds updateInterval{250};

	// Information attributes
	float jumpHeight = -1;
	float inertia = -1;
	float maxVelocityX = -1;
	bool breakBrick = 0;
	bool fire = 0;

	// User control attributes
	float forceX = 0;
	float forceY = 0;

	// Support attributes
	bool crouch = false;
	float lastXVelocity = 0;
	bool direction = 0;	// face direction: 0 - right, 1 - left		
	int currentWalkTexture = 0;	// 0 1 2

public:
	Character();

	void setForceX(float x);

	void setForceY(float y);

	void update(float deltaTime, Map map);

	virtual void updateTexture() = 0;

	virtual void setCrouch() = 0;

	virtual ~Character() = default;
};

class Mario : public Character
{
public:
	Mario();

	void setCrouch();

	~Mario() = default;
};

class Luigi : public Character
{
public:
	Luigi();

	void setCrouch();

	~Luigi() = default;
};


class Decorator : public Character
{
protected:
	shared_ptr<Character> character;
	vector<sf::Texture> altTextures = vector<sf::Texture>(10);

public:
	Decorator();

	Decorator(shared_ptr<Character> c);

	void updateTexture();

	void setCrouch();

	virtual ~Decorator() = default;
};

class SuperDecorator : public Decorator
{
public:
	SuperDecorator(shared_ptr<Character> c);

	void toSmall();

	void toFire();
};

class FireDecorator : public Decorator
{
public:
	FireDecorator(shared_ptr<Character> c);

	void toSmall();
};