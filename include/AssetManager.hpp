#pragma once

#include <map>
#include <string>
#include "TextureManager.hpp"
#include "Vector2D.hpp"
#include "ECS/ECS.hpp"
#include"SDL2/SDL_ttf.h"

class AssetManager
{
public:
    AssetManager(Manager* man);
    ~AssetManager();

    //gameproject
    void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);
    void CreateTree(Vector2D pos, int posH, int posW, Vector2D col, int colH, int colW, float scale, std::string id);
    void CreateRock(Vector2D pos, int posH, int posW, Vector2D col, int colH, int colW, float scale, std::string id);

    //texture management
    void AddTexture(std::string id, const char* path);
    SDL_Texture* GetTexture(std::string id);

    void AddFont(std::string id, std::string path, int fontSize);
    TTF_Font* GetFont(std::string id);

private:
    Manager* manager;
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TTF_Font*> fonts;
    
};
