#pragma once
/***		Include SFML files			***/
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/***		Include Helper Libraries		***/
#include <windows.h>
#include<iostream>
#include <sstream>
#include<iomanip>
#include<fstream>
#include<map>
#include<string>


using namespace std;
using namespace sf;


/***			Special Variable			***/
typedef enum { SMALL, BIG, SUPER } marioState_t;

typedef enum { COIN, MASHROOM, FLOWER, SPARKL, NONE } item_t;

typedef enum { QUESTION, STONE, BRONZE, SMASH, ROCK } block_t;

typedef enum { BLACK, SMASHED, TURTLE, SHELL } enemy_t;


struct player {
	string name;
	string score;
	string level;
	int lifes;
	float enemiesSpeed;
};

struct area {
	float width;
	float height;
};

struct position {
	float x;
	float y;
};


#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900


/***						Menu						***/
#define MAIN_MENU_FONT "Resource/Fonts/Barkentina_font.ttf"

#define CAIRO_REGULAR "Resource/Fonts/Cairo-Regular.ttf"

#define MAIN_MENU_BACKGROUND "Resource/Textures/Menu/Menu.jpg"

#define LEVELS_LIST_BACKGROUND "Resource/Textures/Menu/levelsList.jpg"

#define PLAYER_NAME_BACKGROUND "Resource/Textures/Menu/playerName.jpg"

#define MENU_SHADOW "Resource/Textures/MenuShadow.png"

#define HIGH_SCORE_BACKGROUND "Resource/Textures/Menu/highScore.jpg"

#define HOW_TO_PLAY_BACKGROUND "Resource/Textures/Menu/howToPlay.jpg"

#define OPTIONS_BACKGROUND "Resource/Textures/Menu/Options.jpg"

#define CREDITS_BACKGROUND "Resource/Textures/Menu/Credits.jpg"

#define MUSIC_BALL "Resource/Textures/Menu/musicBall.png"

#define DIFFICULTY_BALL "Resource/Textures/Menu/difficultyBall.png"

#define CONTROL_BALL "Resource/Textures/Menu/controlBall.png"

#define MENU_SOUND "Resource/Music/MenuMusic.ogg"

#define CHANGING_OPTION_SOUND "Resource/Sounds/fireball.wav"

/**********************************************************/




/***						Mario						***/
#define MARIO_CHARACTER "Resource/Textures/Mario.png"

#define MARIO_SUPER_CHARACTER "Resource/Textures/MarioSuper.png"

#define JUMP_SOUND "Resource/Sounds/jump.wav"

#define DAMAGE_SOUND "Resource/Sounds/damage.wav"

#define DIE_SOUND "Resource/Sounds/mario_die.wav"

/**********************************************************/




/***					GameEngine						***/
#define PLAYERS_FILE "Files/Players.txt"

#define GAME_HEADER_FONT "Resource/Fonts/some_font.ttf"

/**********************************************************/




/***						Items							***/
#define ITEMS "Resource/Textures/Items.png"

#define COIN_SOUND "Resource/Sounds/coin.wav"

#define POWERUP_SOUND "Resource/Sounds/powerup.wav"

#define POWERUP_APPEAR_SOUND "Resource/Sounds/powerup_appears.wav"

/**********************************************************/




/***						Blocks							***/
#define QUESTION_BLOCK "Resource/Textures/AnimTiles.png"

#define STONE_BLOCK "Resource/Textures/Tiles.png"

#define SMASH_STONE_BLOCK "Resource/Textures/Smash/Br"

#define FLOATING_FONT "Resource/Fonts/Floating_font.otf"

#define POPUP_SOUND "Resource/Sounds/pop_up.wav"

#define SMASH_SOUND "Resource/Sounds/smash.wav"
/**********************************************************/




/***						Levels							***/
#define LEVEL_MUSIC "Resource/Music/Levels.wav"

#define LEVEL1_BACKGROUND "Resource/Textures/Backgrounds/Blue.jpg"

#define LEVEL2_BACKGROUND "Resource/Textures/Backgrounds/Red.jpg"

#define LEVEL1_GROUND "Resource/Textures/blueGround.png"

#define LEVEL2_GROUND "Resource/Textures/redGround.png"

/**********************************************************/




/***						Enemy							***/
#define ENEMY "Resource/Textures/Enemies.png"

#define KILL_SOUND "Resource/Sounds/kick.wav"

/**********************************************************/