#pragma once
#include "Components.hpp"
#include "SDL2/SDL.h"
#include "../TextureManager.hpp"
#include "Animation.hpp"
#include "AnimationManager.hpp"

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
    SpriteComponent(const char* path)
    {
        setTex(path);
    }

    SpriteComponent(const char* path, bool isAnimated)
    {
        animated = isAnimated;

        animationManager.addAnimation("Idle", Animation(0, 4, 100));
        animationManager.addAnimation("walk_up", Animation(2, 7, 100));
        animationManager.addAnimation("walk_down", Animation(1, 6, 100));
        animationManager.addAnimation("walk_right", Animation(3, 3, 100));
        animationManager.addAnimation("walk_left", Animation(4, 3, 100));

        animationManager.Play("Idle");
        setTex(path);
    }

    SpriteComponent(const char* path, bool isAnimated, const char* charName)
    {
        animated = isAnimated;

        if(charName = "Souls")
        {
            animationManager.addAnimation("Idle", Animation(0, 8, 100));
        }
        animationManager.Play("Idle");
        setTex(path);
    }

    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
    }

    void setTex(const char* path)
    {
        texture = TextureManager::loadTexture(path);
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
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / animationManager.getSpeed()) % animationManager.getFrames());
        }

        srcRect.y = animationManager.getAnimIndex() * transform->height;

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
