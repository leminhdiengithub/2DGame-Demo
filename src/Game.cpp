#include"Game.hpp"
#include"TextureManager.hpp"
#include"Map/MapLayer.hpp"
#include"ECS/Components.hpp"
#include"Vector2D.hpp"
#include"ECS/KeyboardController.hpp"
#include"Collision.hpp"

MapLayer* mapLayer;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::home;

SDL_Rect Game::camera = { 0,0,960,640 };

Manager manager;

auto& player(manager.addEntity());
auto& song(manager.addEntity());
auto& enemy(manager.addEntity());

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayer));
auto& enimies(manager.getGroup(Game::groupEnemies));
auto& colliders(manager.getGroup(Game::groupColliders));

Game::Game()
{}

Game::~Game()
{}

void Game::initWindow(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int  flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    // Check SDL_Init() for errors
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Error: " << SDL_GetError() << std::endl;
        return;
    }

    std::cout << " Subssystem Initialised..." << std::endl;

    // Create a window
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (window == nullptr)
    {
        std::cout << "Error: " << SDL_GetError() << std::endl;
        return;
    }

    std::cout << "Window created." << std::endl;

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED && SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cout << "Error: " << SDL_GetError() << std::endl;
        return;
    }

    // Set the renderer draw color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    std::cout << "Renderer created." << std::endl;

    isrunning = true;

}

void Game::setup()
{
    isrunning = true;

    mapLayer->LoadMapLayer();

    player.addComponent<TransformComponent>(1.75);
    player.addComponent<SpriteComponent>("res/gfx/player.png", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayer);

    enemy.addComponent<TransformComponent>(200,200,160,160,3);
    enemy.addComponent<SpriteComponent>("res/gfx/Enemy.png", true, "Souls");
    enemy.addComponent<ColliderComponent>("enemy");
    enemy.addGroup(groupEnemies);

    song.addComponent<AudioComponent>("res/sounds/mskts.mp3");
    song.getComponent<AudioComponent>().playMusic();

    home = false;
}

void Game::handleEvents()
{
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isrunning = false;
        break;
    
    default:
        break;
    }

}

void Game::update()
{
    /*std::cout << "x: " << player.getComponent<TransformComponent>().position.x 
          << " y: " << player.getComponent<TransformComponent>().position.y 
          << std::endl;*/

    SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = player.getComponent<TransformComponent>().position;

    //manager.removeEntity(&enemy);

    manager.refresh();
    manager.update();

    for (auto& c : colliders)
    {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if(Collision::AABB(cCol, playerCol))
        {
            player.getComponent<TransformComponent>().position = playerPos;
        }
    }

    camera.x = player.getComponent<TransformComponent>().position.x - 480;
    camera.y = player.getComponent<TransformComponent>().position.y - 320;

    // Ensure the camera stays within the bounds
    camera.x = std::max(0, std::min(camera.x, camera.w));
    camera.y = std::max(0, std::min(camera.y, camera.h));
    
}


void Game::render()
{
    SDL_RenderClear(renderer);
    for ( auto& t : tiles )
    {
        t->draw();
    }
    
    for( auto& c: colliders)
    {
        c->draw();
    }

    for ( auto& p : players )
    {
        p->draw();
    }

    for ( auto& e : enimies )
    {
        e->draw();
    }

    //hiển thị tất cả nội dung đã được vẽ lên backbuffer vào cửa sổ.
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_CloseAudio();
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}