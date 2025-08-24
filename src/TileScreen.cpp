#include <Menu/TileScreen.hpp>
#include <SDL2/SDL.h>
#include <Game.hpp>

extern Game* game;
extern pauseMenu pause;

titleScreen::titleScreen() {
    for (int i = 0; i < n; i++) {
        std::cout << i << std::endl;
        textBoxes[i].x = WIDTH / 2;
        textBoxes[i].y = (HEIGHT - ((n - 1) * 100)) / 2 + i * 100;
    }

    textBoxes[0].message = "Play";
    textBoxes[1].message = "Tutorial";
    textBoxes[2].message = "Quit";
}


titleScreen::~titleScreen() {}

void titleScreen::loadAssets(){

	// Load image one time
    backgroundTexture = TextureManager::loadTexture("res/gfx/Background.png");
    if (!backgroundTexture) {
        std::cerr << "Failed to load background image!\n";
    }

    // get image size and set rect
    int imgW, imgH;
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &imgW, &imgH);
    srcRect = { 0, 0, imgW, imgH };
    destRect = { 0, 0, WIDTH, HEIGHT };

}

void titleScreen::handleEvents() { //change parameter "position"

	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {

		case SDL_QUIT:
			game->isrunning = false;
			break;
		
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				int mx = event.button.x;
				int my = event.button.y;
				for (int i = 0; i < n; i++) {
					SDL_Rect rect = textBoxes[i].getRect();
					if (mx >= rect.x && mx <= rect.x + rect.w &&
						my >= rect.y && my <= rect.y + rect.h) {
						pos = i;
						// xử lý click như Enter
						switch (pos) {
							case 0: on = false; game->setup(); game->on = true; break;
							case 1: std::cout << "w a s d to move, left click to shoot\n"; break;
							case 2: game->isrunning = false; break;
						}
					}
				}
			}
			

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				pos -= 1;
				break;
			case SDLK_DOWN:
				pos += 1;
				break;

			case SDLK_RETURN:
				if (pos == 0) { /*(title.)*/on = false; game->setup(); game->on = true; }
				if (pos==1) std::cout << "w a s d to move, left click to shoot" << std::endl;
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
	
}

void titleScreen::render() {
    SDL_SetRenderDrawColor(Game::renderer, 20, 20, 20, 255);
    SDL_RenderClear(Game::renderer); // delete old frame

    // Draw image (if loaded image)
    if (backgroundTexture) {
        TextureManager::Draw(backgroundTexture, srcRect, destRect, SDL_FLIP_NONE);
    }

    // Draw TextBoxs
    for (int i = 0; i < n; i++) {
        textBoxes[i].renderText();
    }

    SDL_RenderPresent(Game::renderer); // Update new frame
}
