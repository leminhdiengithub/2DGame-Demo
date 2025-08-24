#pragma once

#include "TextBox.hpp"
#include <array>
#include <string>
#include <SDL2/SDL.h>
#include <TextureManager.hpp>
#include "Game.hpp"
#include"TileScreen.hpp"

struct pauseMenu {
	int pos = 0;
	bool on = false;

	SDL_Texture* backgroundTexture;
	SDL_Rect srcRect, destRect;
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;


	int n = 3;
	textBox textBoxes[3];
	
	int mx, my;
	
	pauseMenu();
	~pauseMenu();

	void loadAssets();
	
	void update();
	void render();
	void handleEvents();


};