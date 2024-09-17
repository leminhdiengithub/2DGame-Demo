#include "AssetManager.hpp"
#include "ECS/Components.hpp"

AssetManager::AssetManager(Manager* man) : manager(man)
{}

AssetManager::~AssetManager()
{}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id)
{
    auto& projectle(manager->addEntity());
    projectle.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
    projectle.addComponent<SpriteComponent>(id);
    projectle.addComponent<ProjectileComponent>(range, speed, vel);
    projectle.addComponent<ColliderComponent>("projectile");
    projectle.addGroup(Game::groupPorjectiles);
}

void AssetManager::AddTexture(std::string id, const char* path)
{
    textures.emplace(id, TextureManager::loadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
    return textures[id];
}