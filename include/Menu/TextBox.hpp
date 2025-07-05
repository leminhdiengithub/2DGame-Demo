#pragma once
#include <SDL2/SDL_ttf.h>

struct textBox {

	int x;
	int y;
	SDL_Color c;
	const char* message;
	int size;

	SDL_Rect getRect();

	textBox();
	~textBox();

	void renderText();
};