#include "Menu/GameOver.hpp"

extern Game* game;
extern titleScreen title;

GameOverScreen::GameOverScreen() {}
GameOverScreen::~GameOverScreen() {}

void GameOverScreen::loadAssets() {
    backgroundTexture = TextureManager::loadTexture("res/gfx/GameOver.png");
    if (!backgroundTexture) {
        std::cerr << "Failed to load GameOver background!\n";
    }

    int imgW, imgH;
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &imgW, &imgH);
    srcRect = { 0, 0, imgW, imgH };
    destRect = { 0, 0, WIDTH, HEIGHT };

    // setup message
    messageBox.x = WIDTH / 2;
    messageBox.y = HEIGHT - 100;
    messageBox.message = "Press H to return to Title";
    messageBox.c = {255, 255, 255};
    messageBox.size = 32;
}

void GameOverScreen::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                game->isrunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_h) {
                    on = false;          
                    game->clearData();   
                    title.on = true;     
                }
                break;
            default:
                break;
        }
    }
}

void GameOverScreen::update() {}

void GameOverScreen::render() {
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Game::renderer);

    if (backgroundTexture) {
        TextureManager::Draw(backgroundTexture, srcRect, destRect, spriteFlip);
    }

    messageBox.renderText();

    SDL_RenderPresent(Game::renderer);
}
