#include"Game.hpp"
#include"TextureManager.hpp"
#include"Map.hpp"
#include"ECS/Components.hpp"
#include"Vector2D.hpp"
#include"ECS/KeyboardController.hpp"
#include"Collision.hpp"
#include"AssetManager.hpp"

extern titleScreen title;
extern pauseMenu pause;

Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::home;
bool Game::isrunning = false;

SDL_Rect Game::camera = { 0,0,WIDTH,HEIGHT};

    Map* m_Layer1 = new Map("terrain", 2, 32);
    Map* m_Layer2 = new Map("terrain1",2, 32);
    Map* m_Layer4 = new Map("terrain2",2,32);

AssetManager* Game::assets = new AssetManager(&manager);

auto& player(manager.addEntity());
auto& song(manager.addEntity());
auto& enemy(manager.addEntity());
auto& label(manager.addEntity());

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayer));
auto& enimies(manager.getGroup(Game::groupEnemies));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projecttiles(manager.getGroup(Game::groupPorjectiles));
auto& labels(manager.getGroup(Game::groupULlabel));

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

    // Check SDL_Init() for errors
    if (TTF_Init() == -1)
    {
        std::cout << "Error: TTF_Init - " << TTF_GetError() << std::endl;
        SDL_Quit();
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
    assets->AddFont("arial", "res/font/EvilEmpire-4BBVK.ttf", 16);

    

    m_Layer1->setCollisionTileCodes({});
    m_Layer1->LoadMap("res/gfx/mapFile_Layer1.csv", 30, 20, 8);

    m_Layer2->setCollisionTileCodes({});
    m_Layer2->LoadMap("res/gfx/m_layer2.csv", 30, 20, 16);

    m_Layer4->setCollisionTileCodes({242});
    m_Layer4->LoadMap("res/gfx/m_layer4.csv", 30, 20, 16);

    player.addComponent<TransformComponent>(1.75);
    player.addComponent<SpriteComponent>("player", true);//
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayer);

    enemy.addComponent<TransformComponent>(200,200,160,160,2);
    enemy.addComponent<SpriteComponent>("enemy", true, "Souls");
    enemy.addComponent<ColliderComponent>("enemy", 130, 125, 70, 95); /* x y w h*/
    enemy.addGroup(groupEnemies);

    SDL_Color white = { 255, 255, 255, 255 };
    label.addComponent<ULlabel>(10, 10, "Game_demo","arial", white );
    label.addGroup(groupULlabel);

    assets->CreateProjectile(Vector2D(600,600), Vector2D(2,0) ,200, 2, "projectile");           

    song.addComponent<AudioComponent>("res/sounds/mskts.mp3");
    

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
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) 
        {
			std::cout << "t" << std::endl;
			/*(game.)*/on = false;
			pause.on = true;
		}
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

    if (on && Mix_PlayingMusic() == 0) // Nếu chưa có nhạc đang phát
    {
        song.getComponent<AudioComponent>().playMusic();
    } else if (!on && Mix_PlayingMusic() != 0)
    {
        song.getComponent<AudioComponent>().stopMusic();
    }

    if (Collision::AABB(player.getComponent<ColliderComponent>(), enemy.getComponent<ColliderComponent>()))
    {
        Collision::ResolveCollision(player.getComponent<ColliderComponent>(), enemy.getComponent<ColliderComponent>());
    }
        
    for (auto& c : colliders)
    {
        if (Collision::AABB(player.getComponent<ColliderComponent>(), c->getComponent<ColliderComponent>()))
        {
            //Block Component
            Collision::ResolveCollision(player.getComponent<ColliderComponent>(), c->getComponent<ColliderComponent>());       
        }
    }

    for ( auto& p : projecttiles)
    {
        if (Collision::AABB(player.getComponent<ColliderComponent>(), p->getComponent<ColliderComponent>()))
        {
            p->destroy();
        }
        if (p->getComponent<ProjectileComponent>().isMakedForDestroy())
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

    for (auto& l : labels)
    {
        l->draw();
    }
    

    //hiển thị tất cả nội dung đã được vẽ lên backbuffer vào cửa sổ.
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    manager.clear();

    delete m_Layer1;
    delete m_Layer2;
    delete m_Layer4;

    delete assets;
    song.destroy();

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    TTF_Quit();        // Dọn dẹp SDL_ttf
    Mix_CloseAudio();  // Dừng âm thanh
    Mix_Quit();        // Dọn dẹp SDL_mixer
    SDL_Quit();        // Dọn dẹp SDL

    std::cout << "Game cleaned" << std::endl;
}
