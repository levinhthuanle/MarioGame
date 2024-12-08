#pragma once
#include "DEFINITION.h"

class GameEngine
{
private:
    Font headerFont;
    ostringstream scoreStr, timerStr, coinsStr, lifeStr;
    Clock timer, convertTimer, coinTimer;
    int currentTime, levelTime, counterTime, scoreInt, fontSize, coinsInt, remainTime, lifeInt;
    fstream playersFile;
    map<string, int> levelsMap;
    Texture coinTexture;
    Sprite coinSprite, marioLifeSprite;
    SoundBuffer popUpBuffer, smashBuffer, coinBuffer, powerUpBuffer, powerUpAppearBuffer, killBuffer;
    IntRect coinRect;

public:
    bool lifeScreen, gameRunning;
    Mario mario;
    Text timerText, scoreText, coinsText, levelText, lifeText;
    Font floatingTextFont;
    Texture stoneTexture, questionTexture, smashTextures[6], itemTexture, enemyTextrue;
    Sound popUpSound, smashSound, coinSound, powerUpSound, powerUpAppearSound, killSound;
    player currentPlayer;

   
    GameEngine();

   

   
    void updateScore(int IncScore);


   
    void startCountDown();


 
    void updateTimer();


 
    bool isTimerFinished();


  
    void timeToScore();


   
    void draw(RenderWindow& window);


  
    void updateCoins();


    
    void addPlayerInfo();


   
    void setLevelName(std::string levelName);


    
    void startTimeToScore();



    void coinAnimation();


  
    void updateLifes();


   
    void setHeaderPosition(position screenCenter);


 
    void startLifeScreen(RenderWindow& window);
};