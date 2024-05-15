#include "variables.h"
#include<iostream>

bool isRunning = false;
bool showmenu = false;
bool isChoosing = true;
bool mainLoop = true;

bool isWinning = false;
bool lose = false;

int mineCountLeft = NumberOfMines;
int CountTileLeft = BOARD_SIZE_X * BOARD_SIZE_Y;

LTexture menuTheme(NULL, 0, 0);
LTexture levelTheme(NULL, 0, 0);
LTexture easyTable(NULL, 0, 0);
LTexture mediumTable(NULL, 0, 0);
LTexture hardTable(NULL, 0, 0);

LTexture back(NULL, 0, 0);
LTexture sound_on(NULL, 0, 0);
LTexture sound_off(NULL, 0, 0);

LTexture winFace(NULL,0,0);
LTexture playingFace(NULL,0,0);
LTexture loseFace(NULL,0,0);

LTexture startButton(NULL, 0, 0);
LTexture exitButton(NULL, 0, 0);
LTexture startButtonColor(NULL, 0, 0);
LTexture exitButtonColor(NULL, 0, 0);
LTexture easyChoice(NULL, 0, 0);
LTexture mediumChoice(NULL, 0, 0);
LTexture hardChoice(NULL, 0, 0);

LTexture easyChoiceColor(NULL, 0, 0);
LTexture mediumChoiceColor(NULL, 0, 0);
LTexture hardChoiceColor(NULL, 0, 0);

std::vector <std::vector<int> > sBoard(3, std::vector<int>(2,0));
std::vector <std::vector<int> > board(3, std::vector<int>(2, 0));

LTexture Tiles_image(NULL, 0, 0);
SDL_Rect Tilesprites[12] = {};

bool mute = false;
Mix_Chunk* click = NULL;
Mix_Music* loseMusic = NULL;
Mix_Music* winMusic = NULL;

int distance_x = 0;
int distance_y = 0;
int digit_x = 0;
int digit_y = 0;
int timeDigit_x = 0;

LTexture Digits(NULL, 0, 0);
SDL_Rect Digitsprites[10] = {};

int BOARD_SIZE_X = 0;
int BOARD_SIZE_Y = 0;
int NumberOfMines = 0;

bool playAgain = false;
bool start = false;
bool easy = false;
bool medium = false;
bool hard = false;


