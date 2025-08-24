#include"Game.hpp"
#include"TextureManager.hpp"
#include"Vector2D.hpp"
#include"ECS/KeyboardController.hpp"
#include"Collision.hpp"
#include"AssetManager.hpp"

extern titleScreen title;
extern pauseMenu pause;
extern GameOverScreen gameOver;

Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::home;
bool Game::isrunning = false;

SDL_Rect Game::camera = { 0,0,WIDTH,HEIGHT};

AssetManager* Game::assets = new AssetManager(&manager);

std::vector<Entity*>& Game::gettiles() {return manager.getGroup(groupMap); }
std::vector<Entity*>& Game::getPlayers() { return manager.getGroup(groupPlayer); }
std::vector<Entity*>& Game::getEnemies() { return manager.getGroup(groupEnemies); }
std::vector<Entity*>& Game::getTileMapColliders() { return manager.getGroup(groupColliders); } //Col TileMap
std::vector<Entity*>& Game::getColiderprojecttiles(){ return manager.getGroup(groupProjectiles); }
std::vector<Entity*>& Game::getColiderprojecttilesP(){ return manager.getGroup(groupProjectilesP); }
std::vector<Entity*>& Game::getObjects() { return manager.getGroup(groupObject); }
std::vector<Entity*>& Game::getLabels()  { return manager.getGroup(groupULlabel); }
std::vector<Entity*>& Game::getAudios()  { return manager.getGroup(groupAudio); }

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

    // Check SDL_Init() for errors
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        std::cerr << " SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        Mix_AllocateChannels(64);
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
    std::cout << "[INFO] Game had set up..." << std::endl;

    isrunning = true;

    player = &manager.addEntity();
    song   = &manager.addEntity();
    label  = &manager.addEntity();


    assets->AddTexture("terrain","res/gfx/TX Tileset Grass.png");//
    assets->AddTexture("terrain2","res/gfx/TX Tileset Wall.png");
    assets->AddTexture("terrain3", "res/gfx/TX Props.png");

    assets->AddTexture("player", "res/gfx/player.png");//
    assets->AddTexture("enemy","res/gfx/Enemy.png");
    assets->AddTexture("projectile","res/gfx/projectile.png");
    assets->AddTexture("projectileP","res/gfx/projectile.png"); 
    assets->AddTexture("fireplace","res/gfx/fireplace.png");

    assets->AddTexture("treeDemo","res/gfx/Pine Tree - GREEN  - Spritesheet.png");
    assets->AddTexture("rockDemo","res/gfx/TX Props.png");
    assets->AddTexture("boxDemo","res/gfx/TX Props.png");

    assets->AddFont("arial", "res/font/EvilEmpire-4BBVK.ttf", 16);

    assets->AddMusic("backgroundMusic", "res/sounds/Monstadt.mp3");
    assets->AddSoundEffect("projectile", "res/sounds/Projectile_sound.wav" );
    assets->AddSoundEffect("projectileP", "res/sounds/Projectile_sound.wav" );

    m_Layer1 = new Map("terrain", 2, 32);
    m_Layer1->setCollisionTileCodes({});
    m_Layer1->LoadMap("res/gfx/mapFile_Layer1.csv", 30, 20, 8);

    m_Layer2 = new Map("terrain2", 2, 32);
    m_Layer2->setCollisionTileCodes({0,21,22,23,37,39,97,98,99,100,49,51});
    m_Layer2->LoadMap("res/gfx/m_layer2.csv", 30, 20, 16);

    m_Layer3 = new Map("terrain3", 2, 32);
    m_Layer3->setCollisionTileCodes({});
    m_Layer3->LoadMap("res/gfx/m_layer3_object.csv", 30, 20, 16);

    player->addComponent<TransformComponent>(1.75);
    player->addComponent<SpriteComponent>("player", true);//
    player->addComponent<KeyboardController>();
    player->addComponent<ColliderComponent>("player");
    player->addGroup(groupPlayer);

    SDL_Color white = { 255, 255, 255, 255 };
    label->addComponent<ULlabel>(20, 10, "Left click: Attack | W A S D: Move","arial", white );
    label->addGroup(groupULlabel);

    assets->CreateEnimies(Vector2D(500, 200), "enemy");
    assets->CreateEnimies(Vector2D(884 ,-43), "enemy");
    assets->CreateEnimies(Vector2D(81 ,661), "enemy");
    assets->CreateEnimies(Vector2D(710 ,861), "enemy");
    assets->CreateEnimies(Vector2D(1321 ,178), "enemy");
    assets->CreateEnimies(Vector2D(1154 ,682), "enemy");

    assets->CreateTree(Vector2D(72, 37), "treeDemo");
    assets->CreateTree(Vector2D(995, -9), "treeDemo");
    assets->CreateTree(Vector2D(553, -2), "treeDemo");
    assets->CreateTree(Vector2D(652, 252), "treeDemo");
    assets->CreateTree(Vector2D(1490, 248), "treeDemo");
    assets->CreateTree(Vector2D(1281, 257), "treeDemo");
    assets->CreateTree(Vector2D(1140, 633), "treeDemo");
    assets->CreateTree(Vector2D(920, 900), "treeDemo");
    
    assets->CreateRock(Vector2D(90,418),"rockDemo");
    assets->CreateRock(Vector2D(160,396),"rockDemo");
    assets->CreateRock(Vector2D(1569,820),"rockDemo");
    assets->CreateRock(Vector2D(1569,904),"rockDemo");
    assets->CreateRock(Vector2D(1569,994),"rockDemo");

    assets->CreateBox(Vector2D(1689, 740), "boxDemo");

    assets->CreateFireLace(Vector2D(351,118),"fireplace");
    assets->CreateFireLace(Vector2D(194,815),"fireplace");
    assets->CreateFireLace(Vector2D(269,875),"fireplace");
    assets->CreateFireLace(Vector2D(119,873),"fireplace");
    assets->CreateFireLace(Vector2D(190,941),"fireplace");

    song->addComponent<AudioComponent>("backgroundMusic", true);
    song->addGroup(groupAudio);
    
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
			// std::cout << "t" << std::endl;
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
    manager.refresh();
    manager.update();

    if (on && Mix_PlayingMusic() == 0)
    {
        song->getComponent<AudioComponent>().playMusic();
    } else if (!on && Mix_PlayingMusic() != 0)
    {
        song->getComponent<AudioComponent>().stopMusic();
    }

    //std::cout << player->getComponent<TransformComponent>().position.x << " + " << player->getComponent<TransformComponent>().position.y << std::endl;


    auto& playerTransform = player->getComponent<TransformComponent>();

    Vector2D playerCenter = playerTransform.getCenter();
    
    for (auto& e : Game::getEnemies())
    {
        auto& enemyTransform = e->getComponent<TransformComponent>();
        auto& enemyE = e->getComponent<EnemyComponent>();

        // Enemy center
        Vector2D enemyCenter = enemyTransform.getCenter();
        enemyE.DistanceChecking(playerCenter,enemyCenter);
    }
    
    for (auto& c : Game::getTileMapColliders())
    {
        if (Collision::AABB(player->getComponent<ColliderComponent>(), c->getComponent<ColliderComponent>()))
        {
            //Block Component
            Collision::ResolveCollision(player->getComponent<ColliderComponent>(), c->getComponent<ColliderComponent>());       
        }
    }

    for (auto& o : Game::getObjects())
    {
        if (Collision::AABB(player->getComponent<ColliderComponent>(), o->getComponent<ColliderComponent>()))
        {
            Collision::ResolveCollision(player->getComponent<ColliderComponent>(), o->getComponent<ColliderComponent>());
        }   
    }

    auto& enemies = Game::getEnemies();
    auto& projectilesP = Game::getColiderprojecttilesP();
    auto& projectiles = Game::getColiderprojecttiles();

    for (auto& p : projectilesP) {
        for (auto& e : enemies) {
            if (e->isEnabled() && Collision::AABB(
                    p->getComponent<ColliderComponent>(), 
                    e->getComponent<ColliderComponent>())) 
            {
                p->destroy();
                e->getComponent<EnemyComponent>().healbath -= 1;
                e->getComponent<EnemyComponent>().isDying = true;
                e->getComponent<EnemyComponent>().isHiting = true;
                break;
            }
        }
    }
    for (auto& p : projectiles)
    {
        if (Collision::AABB(player->getComponent<ColliderComponent>(),
            p->getComponent<ColliderComponent>()))
        {
            --healbath;
            p->destroy();
            break;
        }
    }

    if (healbath <= 0 || getEnemies().empty())
    {
        std::cout << "Player Dead." << std::endl;
        on = false;
        gameOver.on = true;
        clearData(); 
    }

    camera.x = player->getComponent<TransformComponent>().position.x - 480;
    camera.y = player->getComponent<TransformComponent>().position.y - 320;

    // Ensure the camera stays within the bounds
    camera.x = std::max(0, std::min(camera.x, camera.w));
    camera.y = std::max(0, std::min(camera.y, camera.h));
    
}

void Game::render()
{
    SDL_RenderClear(renderer);

    for (auto& t : Game::gettiles()) { t->draw(); }

    // Gom object và player để sắp xếp theo x (Z-order ngang)
    std::vector<Entity*> drawables = Game::getObjects();
    for (auto& p : Game::getPlayers()) { drawables.push_back(p); }

    std::sort(drawables.begin(), drawables.end(), [](Entity* a, Entity* b) {
        return (a->getComponent<ColliderComponent>().collider.y + a->getComponent<ColliderComponent>().collider.h) / 2 <
               (b->getComponent<ColliderComponent>().collider.y + b->getComponent<ColliderComponent>().collider.h) / 2;
    });

    for (auto& d : drawables) { d->draw(); }

    for (auto& c : Game::getTileMapColliders()) { c->draw(); }
    for (auto& e : Game::getEnemies()) { e->draw(); }
    for (auto& p : Game::getColiderprojecttiles()) { p->draw(); }
    for (auto& pP : Game::getColiderprojecttilesP()) { pP->draw(); }    
    for (auto& l : Game::getLabels()) { l->draw(); }

    SDL_RenderPresent(renderer);
}

void Game::clearData()
{
    // std::cout << "[INFO] Clearing game data..." << std::endl;

    manager.refresh();
    manager.clear();

    getPlayers().clear();
    gettiles().clear();
    getEnemies().clear();
    getTileMapColliders().clear();
    getColiderprojecttiles().clear();
    getColiderprojecttilesP().clear();
    getObjects().clear();
    getLabels().clear();
    getAudios().clear();

    delete m_Layer1; m_Layer1 = nullptr;
    delete m_Layer2; m_Layer2 = nullptr;
    delete m_Layer3; m_Layer3 = nullptr;

    delete assets;
    assets = new AssetManager(&manager);  // Gán lại sau khi xóa

    if (song) {
        song->destroy();
        song = nullptr;
    }
    healbath = maxHeal; 

    // std::cout << "[INFO] Game data cleared.\n";
}

void Game::clean()
{
    manager.clear();

    getPlayers().clear();
    gettiles().clear();
    getEnemies().clear();
    getTileMapColliders().clear();
    getColiderprojecttiles().clear();
    getColiderprojecttilesP().clear();
    getLabels().clear();
    getObjects().clear();
    getAudios().clear();

    delete m_Layer1; m_Layer1 = nullptr;
    delete m_Layer2; m_Layer2 = nullptr;
    delete m_Layer3; m_Layer3 = nullptr;

    delete assets;

    if (song) {
        song->destroy();
        song = nullptr;
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    TTF_Quit();        // Dọn dẹp SDL_ttf
    Mix_CloseAudio();  // Dừng âm thanh
    Mix_Quit();        // Dọn dẹp SDL_mixer
    SDL_Quit();        // Dọn dẹp SDL

    std::cout << "Game cleaned" << std::endl;
}
