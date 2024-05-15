#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include<iostream>
#include<time.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<string>
#include<vector>

class LTexture
{
public:
	LTexture(SDL_Texture* _mTexture, int _mWidth, int _mHeight);

	~LTexture();

	bool loadFromFile(std::string path);
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

	void free();

	void render(int x, int y, SDL_Rect* clip = NULL);
	int getWidth();
	int getHeight();

private:
    SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};
#endif
