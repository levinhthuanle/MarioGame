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

	float lastXVelocity;
	bool direction;	// face direction: 0 - right, 1 - left		
	static int currentWalkTexture;	// 0 1 2

	float jumpHeight;
	float inertia;
	float maxVelocityX;
	bool breakBrick = 0;
	bool fire = 0;

	chrono::high_resolution_clock::time_point lastUpdate = chrono::high_resolution_clock::now();
	const chrono::milliseconds updateInterval{250};

public:
	Character();

	void update(float deltaTime, Map map);

	virtual void updateTexture() = 0;

	virtual ~Character() = default;
};

class Mario : public Character
{
public:
	Mario();

	~Mario() = default;
};

class Luigi : public Character
{
public:
	Luigi();

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