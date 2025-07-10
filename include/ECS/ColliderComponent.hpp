#pragma once
#include<string>
#include"SDL2/SDL.h"
#include "Components.hpp"
#include"../TextureManager.hpp"

class ColliderComponent : public Component
{
public:
    SDL_Rect collider;
    std::string tag;

    SDL_Texture* tex;
    SDL_Rect srcR, destR;

    TransformComponent* transform;

    int offsetX = 0, offsetY = 0, customW = 0, customH = 0;

    // --- Constructor for Entities
    ColliderComponent(std::string t, int offX, int offY, int cW, int cH)
    : tag(t), offsetX(offX), offsetY(offY), customW(cW), customH(cH)
    {}

    // --- Constructor for player only ---
    ColliderComponent(std::string t)
        : tag(t), offsetX(0), offsetY(0), customW(0), customH(0)
    {}

    // --- Constructor for tilemap (No need Transform) ---
    ColliderComponent(std::string t, int xpos, int ypos, int size)
    {
        tag = t;
        collider.x = xpos;
        collider.y = ypos;
        collider.h = collider.w = size;
    }

    void init() override
    {
        if (!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>();
        }

        transform = &entity->getComponent<TransformComponent>();

        tex = TextureManager::loadTexture("res/gfx/coltex.png");
        
        srcR = { 0, 0, 32, 32 };
        destR = {collider.x, collider.y, collider.w, collider.h};

    }

    void update() override
    {        
        if (tag != "terrain")
        {
            collider.x = static_cast<int>(transform->position.x + offsetX);
            collider.y = static_cast<int>(transform->position.y + offsetY);
            collider.w = (customW > 0) ? customW : transform->width * transform->scale;
            collider.h = (customH > 0) ? customH : transform->height * transform->scale;
        }
        
        destR = {
            collider.x - Game::camera.x,
            collider.y - Game::camera.y,
            collider.w,
            collider.h
        };
    }

    void draw() override
    {
        TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
    }
};
