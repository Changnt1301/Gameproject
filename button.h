#pragma once
#pragma once
#ifndef BUTTONS_H
#define BUTTONS_H
#include <SDL.h>

class LButton
{
public:
	LButton();
	void setPosition(int x, int y);
	void handleEventAgain(SDL_Event* e);
	void handleEventBack(SDL_Event* e);
	void handleEventMute(SDL_Event* e);
	void handleEvent(SDL_Event* e);
	void render(int i, int j);
	void loseRender(int i, int j);
private:
	SDL_Point mPosition;
};
#endif
