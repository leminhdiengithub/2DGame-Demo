#pragma once

#include <stdio.h>
#include<sdl2/SDL.h>
#include<sdl2/SDL_image.h>
#include<sdl2/SDL_timer.h>
#include<SDL2/SDL_mixer.h>
#include<iostream>
#include<vector>
#include"AssetManager.hpp"

class ColliderComponent;

class Game
{
public:
    Game();
    ~Game();

    void initWindow(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    
    //setup
    void setup();

    void handleEvents();
    bool running() { return isrunning;}
    //update
    void update();
    //render
    void render();
    void clean();

    static SDL_Renderer* renderer;
    static SDL_Event event; 
    static SDL_Rect camera;
    static bool home;
    static class AssetManager* assets;

    enum groupLabels : std::size_t
    {
        groupMap,
        groupPlayer,
        groupEnemies,
        groupColliders
    };

private:
    int cnt = 0;
    bool isrunning;
    SDL_Window* window;
};
