#pragma once
#pragma once
#include "time.h"
#include <SDL.h>

bool init();
bool loadTexture(LTexture &texture, const std::string &path);
bool loadMedia();
bool loadTextTexture(LTexture &texture, const std::string &text, SDL_Color color);
bool loadMenuMedia();
void InitializeBoard();
void PlaceMines();
void CalculateNumbers();
void CreateBoard();
void setButtonPosition();
void createMenu();
void createModeMenu();
void showMenu();
void showModeChoice();
void handleEvent();
void reveal(int i, int j);
void isPlayerWinning();
void GameManager();
void DisplayLose();
void DisplayWin();
std::string getTime();
void PlayAgain();
void Return();
void MineManager();
void TimeManager();
void setGameMode(int x, int y, int n, int dx, int dy, int d1x, int d1y, int dtx, int& BOARD_SIZE_X, int& BOARD_SIZE_Y, int& NumberOfMines, int& mineCountLeft, int& CountTileLeft, int& distance_x, int& distance_y, int& digit_x, int& digit_y, int& timeDigit_x);
void renderButton();
void renderGame();
void close();
