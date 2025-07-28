#include "AssetManager.hpp"
#include "ECS/Components.hpp"

AssetManager::AssetManager(Manager* man) : manager(man)
{}

AssetManager::~AssetManager()
{}

void AssetManager::CreateEnimies(Vector2D pos, int posH, int posW, Vector2D col, int colH, int colW, float scale, std::string id)
{
    auto& Enemy (manager->addEntity());
    Enemy.addComponent<TransformComponent>(pos.x, pos.y ,posH ,posW ,scale);
    Enemy.addComponent<SpriteComponent>(id , true, "Souls");
    Enemy.addComponent<ColliderComponent>(id, col.x, col.y, colW, colH);
    Enemy.addComponent<MouseController>();
    Enemy.addGroup(Game::groupEnemies);

}
void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id)
{
    auto& projectle(manager->addEntity());
    projectle.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
    projectle.addComponent<SpriteComponent>(id, true, "projectile");
    projectle.addComponent<AudioComponent>("res/sounds/Projectile_sound.mp3");
    projectle.addComponent<ProjectileComponent>(range, speed, vel);
    projectle.addComponent<ColliderComponent>("projectile");
    projectle.addGroup(Game::groupPorjectiles);
}

void AssetManager::CreateTree(Vector2D pos, int posH, int posW, Vector2D col, int colH, int colW, float scale, std::string id)
{
    auto& tree(manager->addEntity());
    tree.addComponent<TransformComponent>(pos.x, pos.y, posH, posW, scale);
    tree.addComponent<SpriteComponent>(id, true, "treeDemo");
    tree.addComponent<ColliderComponent>(id, col.x, col.y, colW, colH);
    tree.addComponent<MouseController>();
    tree.addGroup(Game::groupObject);
}

void AssetManager::CreateRock(Vector2D pos, int posH, int posW, Vector2D col, int colW, int colH, float scale, std::string id)
{
    auto& rock(manager->addEntity());
    rock.addComponent<TransformComponent>(pos.x, pos.y, posH, posW, scale);
    rock.addComponent<SpriteComponent>(id,true,"rockDemo");
    rock.addComponent<ColliderComponent>(id, col.x, col.y, colW, colH);
    rock.addComponent<MouseController>();
    rock.addGroup(Game::groupObject);
}

void AssetManager::AddTexture(std::string id, const char* path)
{
    textures.emplace(id, TextureManager::loadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
    return textures[id];
}

void AssetManager::AddFont(std::string id, std::string path, int fontSize)
{
    fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}
TTF_Font* AssetManager::GetFont(std::string id)
{
    return fonts[id];
}