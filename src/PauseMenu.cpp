#include <Menu/PauseMenu.hpp>
#include <SDL2/SDL.h>

extern Game* game;
extern titleScreen title;

pauseMenu::pauseMenu() {
	for (int i = 0;i < n;i++) {
		std::cout << i << std::endl;
		textBoxes[i].x = 800 / 2;
		textBoxes[i].y = (640 - ((n - 1) * 100)) / 2 + i * 100;  //neatly centered :)  Some of it is done in textbox.cpp because i need the surface size
		//and I can't be bothered to change all the code to have it here
		textBoxes[0].message = "Continue";
		textBoxes[1].message = "Options";
		textBoxes[2].message = "Title Screen";
		textBoxes[3].message = "Quit";
	}
};
	pauseMenu::~pauseMenu() {};

	




void pauseMenu::handleEvents() {
	//std::cout << "hi" << std::endl;
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {

	case SDL_QUIT:
		game->isrunning = false;
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			pos -= 1;
			break;
		case SDLK_DOWN:
			pos += 1;
			break;

		case SDLK_RETURN:
			if (pos == 0) { /*(title.)*/on = false;game->on = true; }
			if (pos == 1) std::cout << "options" << std::endl;
			if (pos == 2) { 
				on = false; 
				title.on = true; 
				//player.x=400;
				//player.y =320;
	
			}

			if (pos == 3) game->isrunning = false;
			break;

		default:
			break;
		}
		if (pos == n) pos = 0;
		if (pos < 0) pos = n - 1;

		break;


	default:
		break;
	}
	
};

void pauseMenu::update() {
	for (int i = 0;i < n;i++) { //reset all to default
		textBoxes[i].c = { 255,255,255 };
		textBoxes[i].size = 24;
	}

	textBoxes[pos].c = { 255,255,0 }; //put yellow for the one selected
	textBoxes[pos].size = 42;
};
void pauseMenu::render() {
	SDL_SetRenderDrawColor(Game::renderer, 20, 20, 20, 255);
	SDL_RenderClear(Game::renderer);

	SDL_Color White = { 255,255,255 };
	for (int i = 0;i < n;i++) {
		textBoxes[i].renderText();
	}


	SDL_RenderPresent(Game::renderer);
};