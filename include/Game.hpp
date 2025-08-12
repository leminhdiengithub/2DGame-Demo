#pragma once

#include <stdio.h>
#include<sdl2/SDL.h>
#include<sdl2/SDL_image.h>
#include<sdl2/SDL_timer.h>
#include<SDL2/SDL_mixer.h>
#include<iostream>
#include<vector>
#include"ECS/ECS.hpp" // Important*
#include"AssetManager.hpp"

#include<Menu/PauseMenu.hpp>
#include<Menu/TextBox.hpp>
#include<Menu/TileScreen.hpp>
#include"Map.hpp"


#define WIDTH 960
#define HEIGHT 640

class ColliderComponent;

class Game
{
public:
    Game();
    ~Game();

    void initWindow(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    
    //setup
    void setup();
    void clearData();

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

    enum groupLabels : std::size_t
    {
        groupMap,
        groupPlayer,
        groupEnemies,
        groupColliders,
        groupProjectiles,
        groupProjectilesP,
        groupULlabel,
        groupObject,
        groupAudio
    };

    static bool isrunning;
    static class AssetManager* assets;
    static bool home;

    bool on = false;
    int cnt = 0;
    bool isMusicPlaying = true;

    Entity* player = nullptr;
    Entity* getPlayer() { return player; }
    
private:
    SDL_Window* window;

    Map* m_Layer1 = nullptr;
    Map* m_Layer2 = nullptr;

    Entity* song = nullptr;
    Entity* label = nullptr;

    std::vector<Entity*>& gettiles();
    std::vector<Entity*>& getPlayers();
    std::vector<Entity*>& getEnemies();
    std::vector<Entity*>& getTileMapColliders();
    std::vector<Entity*>& getColiderprojecttiles();
    std::vector<Entity*>& getColiderprojecttilesP();
    std::vector<Entity*>& getObjects();
    std::vector<Entity*>& getLabels();
    std::vector<Entity*>& getAudios();
};
