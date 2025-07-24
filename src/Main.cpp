
#define SDL_MAIN_HANDLED
#include"Game.hpp"
#include <chrono>  

Game* game = nullptr;
pauseMenu pause;
titleScreen title;

int main(int argc, char const* argv[])
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->initWindow("shadow knights v.0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 640, false);
    game->setup();
    title.loadAssets();
    pause.loadAssets();

    title.on = true;
    pause.on = false;
    game->on = false;         
    game->isrunning = true;

    while (game->running())
    {
        frameStart = SDL_GetTicks();

        if (title.on)
        {
            if (game->resetSetup == true )
            {
                game->clearData();
                game->setup();
                game->resetSetup = false;
            }
            
            title.handleEvents();
            title.update();
            title.render();
        }
        else if (pause.on)
        {
            pause.handleEvents();
            pause.update();
            pause.render();
        }
        else if (game->on)
        {
            game->handleEvents();
            game->update();
            game->render();
            if (title.on == true)
            {
                game->on = false;
                pause.on = false;
                game->resetSetup = true;
            }
            
        }

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    
    game->clean();
    delete game;

    return 0;
}

