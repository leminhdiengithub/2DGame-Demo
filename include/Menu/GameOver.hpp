#pragma once

#include "TextBox.hpp"
#include <array>
#include <string>
#include <SDL2/SDL.h>
#include "TextureManager.hpp"
#include "Game.hpp"
#include"TileScreen.hpp"

struct GameOverScreen {
    bool on = false;
    SDL_Texture* backgroundTexture = nullptr;
    SDL_Rect srcRect, destRect;
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    textBox messageBox;

    GameOverScreen();
    ~GameOverScreen();

    void loadAssets();
    void handleEvents();
    void update();
    void render();
};
