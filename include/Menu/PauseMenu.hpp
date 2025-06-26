#pragma once

#include "TextBox.hpp"
#include <array>
#include <string>
#include <SDL2/SDL.h>
#include "Game.hpp"
#include"TileScreen.hpp"

struct pauseMenu {
	int pos = 0;
	bool on = false;

	int n = 4;
	textBox textBoxes[4];

	pauseMenu();
	~pauseMenu();

	void update();
	void render();
	void handleEvents();


};