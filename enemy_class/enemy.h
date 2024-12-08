#pragma once
#pragma once
#include "DEFINITION.h"
#include "GameEngine.h"

class Enemy
{
	
private:
	GameEngine* gameEngine;
	Sprite* minX;
	Sprite* maxX;
	RectangleShape* ground;
	enemy_t enemyType;
	IntRect enemyRect, blackRect, smashedRect, turtleRect, shellRect;
	Text floatingText;
	Clock timer, textFloatTimer, turtleTimer;
	int CurrentRect, maxRect, floatingSpeed, killScore;
	float speed[2], scale, accSpeed;
	bool faid, isKilled, resetTime, moving, onGround, firstTime;

public:
	Sprite enemySprite;
	bool display;

	Enemy(GameEngine& gameEngine, enemy_t type, Sprite& minX, Sprite& maxX, RectangleShape& ground, float x, float y);


	
	void draw(RenderWindow& window);

private:
	
	void animation();


	
	void changeDirection();


	
	void checkGround();


	
	void TextFloat();


	
	void checkKilled();



	void setKilled();


	
	void checkTurtleFaid();
};