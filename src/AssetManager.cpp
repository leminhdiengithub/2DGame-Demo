#include "AssetManager.hpp"
#include "ECS/Components.hpp"

AssetManager::AssetManager(Manager *man) : manager(man)
{
}

AssetManager::~AssetManager()
{
}

void AssetManager::CreateEnimies(Vector2D pos, std::string id)
{
    auto &enemy(manager->addEntity());
    enemy.addComponent<TransformComponent>(pos.x, pos.y, 128, 160, 2);
    enemy.addComponent<SpriteComponent>(id, true, "Souls");
    enemy.addComponent<ColliderComponent>(id, 130, 125, 70, 95);
    enemy.addComponent<EnemyComponent>();
    // enemy.addComponent<MouseController>();
    enemy.addGroup(Game::groupEnemies);
}
void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id)
{
    auto &projectle(manager->addEntity());
    projectle.addComponent<TransformComponent>(pos.x, pos.y, 64, 64, 0.75);
    projectle.addComponent<SpriteComponent>(id, true, "projectile");
    projectle.addComponent<AudioComponent>(id, false );
    projectle.addComponent<ProjectileComponent>(range, speed, vel);
    projectle.addComponent<ColliderComponent>("projectile");
    projectle.addGroup(Game::groupProjectiles);
    projectle.getComponent<AudioComponent>().playSoundEffect();
}
void AssetManager::CreateProjectileP(Vector2D pos, Vector2D vel, int range, int speed, std::string id)
{
    auto &projectle(manager->addEntity());
    projectle.addComponent<TransformComponent>(pos.x, pos.y, 64, 64, 0.75);
    projectle.addComponent<SpriteComponent>(id, true, "projectileP");
    projectle.addComponent<AudioComponent>(id, false );
    projectle.addComponent<ProjectileComponent>(range, speed, vel);
    projectle.addComponent<ColliderComponent>("projectileP");
    projectle.addGroup(Game::groupProjectilesP);
    projectle.getComponent<AudioComponent>().playSoundEffect();
}

void AssetManager::CreateTree(Vector2D pos, std::string id)
{
    auto &tree(manager->addEntity());
    tree.addComponent<TransformComponent>(pos.x, pos.y, 96, 53, 2);
    tree.addComponent<SpriteComponent>(id, true, "treeDemo");
    tree.addComponent<ColliderComponent>(id, 45, 140, 16, 16);
    tree.addComponent<MouseController>();
    tree.addGroup(Game::groupObject);
}

void AssetManager::CreateRock(Vector2D pos, std::string id)
{
    auto &rock(manager->addEntity());
    rock.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
    rock.addComponent<SpriteComponent>(id, true, "rockDemo");
    rock.addComponent<ColliderComponent>(id, 0, 0, 32, 32);
    rock.addComponent<MouseController>();
    rock.addGroup(Game::groupObject);
}

void AssetManager::CreateBox(Vector2D pos, std::string id)
{
    auto &box(manager->addEntity());
    box.addComponent<TransformComponent>(pos.x, pos.y, 64, 32, 1);
    box.addComponent<SpriteComponent>(id, true, "boxDemo");
    box.addComponent<ColliderComponent>(id, 0, 32, 32, 32);
    box.addComponent<MouseController>();
    box.addGroup(Game::groupObject);
}

void AssetManager::AddTexture(std::string id, const char *path)
{
    textures.emplace(id, TextureManager::loadTexture(path));
}

SDL_Texture *AssetManager::GetTexture(std::string id)
{
    return textures[id];
}

void AssetManager::AddFont(std::string id, std::string path, int fontSize)
{
    fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}
TTF_Font *AssetManager::GetFont(std::string id)
{
    return fonts[id];
}

void AssetManager::AddMusic(std::string id, const char* path)
{
    Mix_Music* music = Mix_LoadMUS(path);
    if (!music) {
        std::cerr << "Failed to load music: " << path << " Error: " << Mix_GetError() << std::endl;
    }
    musics.emplace(id, music);
}

Mix_Music *AssetManager::GetMusic(std::string id)
{
    return musics[id];
}

void AssetManager::AddSoundEffect(std::string id, const char* path)
{
    Mix_Chunk* sound = Mix_LoadWAV(path);
    if (!sound)
    {
        std::cerr << "Failed to load sound effect: " << path << " Error: " << Mix_GetError() << std::endl;
    }
    soundEffects.emplace(id, sound);
}

Mix_Chunk* AssetManager::GetSoundEffect(std::string id)
{
    return soundEffects[id];
}