#pragma once
#ifndef VARIABLES_H
#define VARIABLES_H

#include "texture.h"
#include "constant.h"
#include "button.h"

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern bool isRunning;
extern bool showmenu;
extern bool isChoosing;
extern bool mainLoop;

extern bool isWinning;
extern bool lose;

extern LTexture menuTheme;
extern LTexture levelTheme;
extern LTexture easyTable;
extern LTexture mediumTable;
extern LTexture hardTable;

extern LTexture back;
extern LTexture sound_on;
extern LTexture sound_off;

extern LTexture winFace;
extern LTexture playingFace;
extern LTexture loseFace;

extern LTexture Tiles_image;
extern SDL_Rect Tilesprites[12];

extern LTexture startButton;
extern LTexture exitButton;
extern LTexture startButtonColor;
extern LTexture exitButtonColor;

extern LTexture easyChoice;
extern LTexture mediumChoice;
extern LTexture hardChoice;

extern LTexture easyChoiceColor;
extern LTexture mediumChoiceColor;
extern LTexture hardChoiceColor;
extern TTF_Font* gFont;

extern std::vector <std::vector<int> > sBoard;
extern std::vector <std::vector<int> > board;

extern int mineCountLeft;
extern int CountTileLeft;

extern bool mute;
extern Mix_Chunk* click;
extern Mix_Music* loseMusic;
extern Mix_Music* winMusic;

extern int distance_x;
extern int distance_y;
extern int digit_x;
extern int digit_y;
extern int timeDigit_x;

extern LTexture Digits;
extern SDL_Rect Digitsprites[10];

extern int BOARD_SIZE_X;
extern int BOARD_SIZE_Y;
extern int NumberOfMines;

extern bool playAgain;
extern bool saveScore;
extern bool start;
extern bool easy;
extern bool medium;
extern bool hard;

#endif
