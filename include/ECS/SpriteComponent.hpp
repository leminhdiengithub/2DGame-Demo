#pragma once
#include "Components.hpp"
#include "SDL2/SDL.h"
#include "../TextureManager.hpp"
#include "Animation.hpp"
#include "AnimationManager.hpp"
#include "../AssetManager.hpp"

class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    bool animated = false;
    AnimationManager animationManager;

public:

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;
    SpriteComponent(std::string id)
    {
        setTex(id);
    }

    SpriteComponent(std::string id, bool isAnimated)
    {
        animated = isAnimated;

        // Move animation                              (y, x, frames, speed)
        animationManager.addAnimation("Idle", Animation(0, 0, 4, 100));
        animationManager.addAnimation("walk_down", Animation(0, 1, 5, 100));
        animationManager.addAnimation("walk_up", Animation(0, 2, 5, 100));
        animationManager.addAnimation("walk_right", Animation(0, 3, 5, 100));
        animationManager.addAnimation("walk_left", Animation(0, 4, 5, 100));

        // Attack animation
        animationManager.addAnimation("attack", Animation(6, 1, 1, 100));

        animationManager.Play("Idle");
        setTex(id);
    }

    SpriteComponent(std::string id, bool isAnimated, const char* charName)
    {
        animated = isAnimated;

        if(charName = "Souls")
        {
            animationManager.addAnimation("Idle", Animation(0, 0, 8, 100));
        }
        animationManager.Play("Idle");
        setTex(id);
    }

    ~SpriteComponent()
    {}

    void setTex(std::string id)
    {
        texture = Game::assets->GetTexture(id);
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
    }

    void update() override
    {
        if (animated)
        {
            srcRect.x = (animationManager.getXAnimIndex() + static_cast<int>((SDL_GetTicks() / animationManager.getSpeed()) % animationManager.getFrames())) * transform->width;
            srcRect.y = animationManager.getYAnimIndex() * transform->height;
        }

        destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
        destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }
    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
    }

    void Play(const char* animName)
    {
        animationManager.Play(animName);
    }
};
