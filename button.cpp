#include "variables.h"
#include "constant.h"
#include "button.h"
#include "function.h"

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;
}

void LButton::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEventAgain(SDL_Event* e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;
		if (x < mPosition.x || x > mPosition.x + 42)
		{
			inside = false;
		}
		else if (y < mPosition.y || y > mPosition.y + 42)
		{
			inside = false;
		}
		if (inside)
		{
			if (e->button.button == SDL_BUTTON_LEFT)
			{
				PlayAgain();
			}
		}
	}
}

void LButton::handleEventBack(SDL_Event* e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;
		if (x < mPosition.x || x > mPosition.x + 50 )
		{
			inside = false;
		}
		else if (y < mPosition.y || y > mPosition.y + 50)
		{
			inside = false;
		}
		if (inside)
		{
			if (e->button.button == SDL_BUTTON_LEFT)
			{
				Return();
			}
		}
	}
}

void LButton::handleEventMute(SDL_Event* e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;
		if (x < mPosition.x || x > mPosition.x + 50)
		{
			inside = false;
		}
		else if (y < mPosition.y || y > mPosition.y + 50)
		{
			inside = false;
		}
		if (inside)
		{
			if (e->button.button == SDL_BUTTON_LEFT)
			{
				if (mute == true) mute = false;
				else mute = true;
			}
		}
	}
}

void LButton::handleEvent(SDL_Event* e)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		int i =  ( x - distance_x)  / TILE_SIZE;
		int j = (y - distance_y) / TILE_SIZE;
		bool inside = true;
		if (x < mPosition.x || x > mPosition.x + TILE_SIZE)
		{
			inside = false;
		}
		else if (y < mPosition.y || y > mPosition.y + TILE_SIZE)
		{
			inside = false;
		}
		if (inside)
		{
			if (e->type == SDL_MOUSEBUTTONDOWN)
			{
				switch (e->button.button)
				{
				case SDL_BUTTON_LEFT:
				{
					reveal(i, j);
					if (CountTileLeft == NumberOfMines)
					{
						Mix_PlayMusic(winMusic, 1);
					}
					if (sBoard[i][j] == 9)
					{
						lose = true;
						Mix_PlayMusic(loseMusic, 1);
					}
					else
					{
						Mix_PlayChannel(-1, click, 0);
					}
					break;
				}
				case SDL_BUTTON_RIGHT:
				{
					Mix_PlayChannel(-1, click, 0);
					if (sBoard[i][j] >= 10)
					{
						if (sBoard[i][j] == 11)
						{
							sBoard[i][j] = 10;
							mineCountLeft++;
						}
						else
						{
							sBoard[i][j] = 11;
							mineCountLeft--;
						}
					}
					else break;
					break;
				}
				}
			}
		}
	}
}

void LButton::render(int i, int j)
{
	Tiles_image.render(mPosition.x, mPosition.y, &Tilesprites[sBoard[i][j]]);
}
void LButton::loseRender(int i, int j)
{
	Tiles_image.render(mPosition.x, mPosition.y, &Tilesprites[board[i][j]]);
}
