#include"Game.hpp"
#include"TextureManager.hpp"
#include"Map.hpp"
#include"ECS/Components.hpp"
#include"Vector2D.hpp"
#include"ECS/KeyboardController.hpp"
#include"Collision.hpp"
#include"AssetManager.hpp"

Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::home;

SDL_Rect Game::camera = { 0,0,960,640 };

AssetManager* Game::assets = new AssetManager(&manager);

auto& player(manager.addEntity());
auto& song(manager.addEntity());
auto& enemy(manager.addEntity());

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayer));
auto& enimies(manager.getGroup(Game::groupEnemies));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projecttiles(manager.getGroup(Game::groupPorjectiles));

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

    assets->AddTexture("terrain","res/gfx/TX Tileset Grass.png");//
    assets->AddTexture("terrain1","res/gfx/TX Plant.png");
    assets->AddTexture("terrain2","res/gfx/TX Props.png");
    assets->AddTexture("player", "res/gfx/player.png");//
    assets->AddTexture("enemy","res/gfx/Enemy.png");
    assets->AddTexture("projectile","res/gfx/proj.png");

    Map* m_Layer1 = new Map("terrain", 2, 32);//
    Map* m_Layer2 = new Map("terrain1",2, 32);
    Map* m_Layer4 = new Map("terrain2",2,32);

    m_Layer1->setCollisionTileCodes({});
    m_Layer1->LoadMap("res/gfx/mapFile_Layer1.csv", 30, 20, 8);

    m_Layer2->setCollisionTileCodes({70});
    m_Layer2->LoadMap("res/gfx/m_layer2.csv", 30, 20, 16);

    m_Layer4->setCollisionTileCodes({242});
    m_Layer4->LoadMap("res/gfx/m_layer4.csv", 30, 20, 16);

    player.addComponent<TransformComponent>(1.75);
    player.addComponent<SpriteComponent>("player", true);//
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayer);

    enemy.addComponent<TransformComponent>(200,200,160,160,3);
    enemy.addComponent<SpriteComponent>("enemy", true, "Souls");
    enemy.addComponent<ColliderComponent>("enemy");
    enemy.addGroup(groupEnemies);

    assets->CreateProjectile(Vector2D(600,600), Vector2D(2,0) ,200, 2, "projectile");

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

    
    manager.refresh();
    manager.update();

    for (auto& c : colliders)
    {
        if (Collision::AABB(player.getComponent<ColliderComponent>(), c->getComponent<ColliderComponent>()))
        {
            Collision::ResolveCollision(player.getComponent<ColliderComponent>(), c->getComponent<ColliderComponent>());
        }
    }

    for ( auto& p : projecttiles)
    {
        if (Collision::AABB(player.getComponent<ColliderComponent>(), p->getComponent<ColliderComponent>()))
        {
            p->destroy();
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

    for ( auto& p : projecttiles )
    {
        p->draw();
    }

    //hiển thị tất cả nội dung đã được vẽ lên backbuffer vào cửa sổ.
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_CloseAudio();//
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}