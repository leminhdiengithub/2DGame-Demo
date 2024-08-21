
#define SDL_MAIN_HANDLED
#include"Game.hpp"


Game* game = nullptr;

int main(int argc, char const *argv[])
{

    const int FPS = 60;
    const int farmeDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
                                                                                    //true để full màn hình
    game->initWindow("shadow knights v.0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 640, false);
    game->setup();

    while (game->running())
    {

        frameStart = SDL_GetTicks();

        game -> handleEvents();
        game -> update();
        game ->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (farmeDelay > frameTime)
        {
            SDL_Delay(farmeDelay - frameTime);
        }
        
    }

    delete game;
    game->clean();

    return 0;
}
