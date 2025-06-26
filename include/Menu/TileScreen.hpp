#pragma once

#include <array>
#include <string>
#include "TextBox.hpp"
#include <SDL2/SDL.h>
#include "Game.hpp"
#include <Menu/TextBox.hpp>
#include <Menu/PauseMenu.hpp>

struct titleScreen {
	int pos = 0;
	int n = 3;
	textBox textBoxes[3];

	bool on = false;
	

	titleScreen();
	~titleScreen();

	void update();
	void render();
	void handleEvents();


};