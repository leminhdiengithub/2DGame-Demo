#pragma once

#include <array>
#include <string>
#include "TextBox.hpp"
#include <SDL2/SDL.h>
#include <TextureManager.hpp>
#include "Game.hpp"
#include <Menu/TextBox.hpp>
#include <Menu/PauseMenu.hpp>

struct titleScreen {
	int pos = 0;
	int n = 3;
	textBox textBoxes[3];

	SDL_Texture *backgroundTexture = nullptr;
    SDL_Rect srcRect, destRect;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	bool on = false;
	
	int mx, my;

	titleScreen();
	~titleScreen();

	void loadAssets();

	void update();
	void render();
	void handleEvents();

};