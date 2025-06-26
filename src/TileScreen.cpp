#include <Menu/TileScreen.hpp>
#include <SDL2/SDL.h>
#include <Game.hpp>

extern Game* game;
extern pauseMenu pause;

titleScreen::titleScreen() {


	for (int i = 0;i < n;i++) {
		std::cout << i << std::endl;
		textBoxes[i].x = 960/2;
		textBoxes[i].y = (640-((n-1) * 100)) / 2 + i * 100;
	}

	textBoxes[0].message = "Play";
	textBoxes[1].message = "Options";
	textBoxes[2].message = "Quit";

}

titleScreen::~titleScreen() {}

void titleScreen::handleEvents() { //change parameter "position"

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
			if (pos==1) std::cout << "options" << std::endl;
			if (pos==2) game->isrunning = false;
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
}

void titleScreen::update() { //animate the option selected (change the size)

	for (int i = 0;i < n;i++) { //reset all to default
		textBoxes[i].c = {255,255,255};
		textBoxes[i].size = 24;
	}

	textBoxes[pos].c = { 255,255,0 }; //put yellow for the one selected
	textBoxes[pos].size =42;
	
}

void titleScreen::render() {
	SDL_SetRenderDrawColor(Game::renderer, 20, 20, 20, 255);
	SDL_RenderClear(Game::renderer);

	SDL_Color White = { 255,255,255 };
	for (int i = 0;i < n;i++) {
		textBoxes[i].renderText();
	}


	SDL_RenderPresent(Game::renderer);

}