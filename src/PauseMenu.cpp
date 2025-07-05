#include <Menu/PauseMenu.hpp>
#include <SDL2/SDL.h>

extern Game* game;
extern titleScreen title;

pauseMenu::pauseMenu() {
	for (int i = 0;i < n;i++) {
		std::cout << i << std::endl;
		textBoxes[i].x = 960 / 2;
		textBoxes[i].y = (640 - ((n - 1) * 100)) / 2 + i * 100;
	}
	textBoxes[0].message = "Continue";
	textBoxes[1].message = "Options";
	textBoxes[2].message = "Title Screen";
	textBoxes[3].message = "Quit";
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
		
		case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT) {
			int mx = event.button.x;
			int my = event.button.y;
			for (int i = 0; i < n; i++) {
				SDL_Rect rect = textBoxes[i].getRect();
				if (mx >= rect.x && mx <= rect.x + rect.w &&
					my >= rect.y && my <= rect.y + rect.h) {
					pos = i;
					// xử lý click như Enter
					switch (pos) {
						case 0: on = false; game->on = true; break;
						case 1: std::cout << "Options\n"; break;
						case 2: on = false; title.on = true; break;
						case 3: game->isrunning = false; break;
					}
				}
			}
		}
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

	SDL_GetMouseState(&mx, &my);// Get mouse current coordinates
	for (int i = 0;i < n;i++) { //reset all to default
		SDL_Rect rect = textBoxes[i].getRect();

        if (mx >= rect.x && mx <= rect.x + rect.w &&
            my >= rect.y && my <= rect.y + rect.h) {
            pos = i;  // check the line had chose
		
			textBoxes[i].c = { 255,255,255 };
			textBoxes[i].size = 24;
		}

		textBoxes[i].c = {255, 255, 255};
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