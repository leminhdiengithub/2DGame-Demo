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

        // Move animation                              (x, y, frames, speed)
        animationManager.addAnimation("Idle", Animation(0, 0, 4, 100));
        animationManager.addAnimation("walk_down", Animation(0, 1, 5, 100));
        animationManager.addAnimation("walk_up", Animation(0, 2, 5, 100));
        animationManager.addAnimation("walk_right", Animation(0, 3, 5, 100));
        animationManager.addAnimation("walk_left", Animation(0, 4, 5, 100));

        // Attack animation
        animationManager.addAnimation("attack", Animation(7, 1, 2, 100));

        animationManager.Play("Idle");
        setTex(id);
    }

    SpriteComponent(std::string id, bool isAnimated, const char* charName)
    {
        animated = isAnimated;

        if(std::string(charName) == "Souls")
        {
            animationManager.addAnimation("Idle", Animation(0, 0, 8, 100));
            animationManager.addAnimation("Dead", Animation(0, 6, 7 ,100));
            animationManager.Play("Idle");
        }
        if (std::string(charName) == "projectile")
        {
            animationManager.addAnimation("Idle", Animation(0, 0, 6, 100));
            animationManager.playOneshot("Idle", true);
        }
        if (std::string(charName) == "treeDemo")
        {
            animationManager.addAnimation("Idle", Animation(0, 0, 16, 100));
            animationManager.Play("Idle");
        }
        if (std::string(charName) == "rockDemo")
        {
            animationManager.addAnimation("Idle", Animation(5, 15, 1, 100));
            animationManager.Play("Idle");
        }
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
            srcRect.x = (animationManager.getXAnimIndex() + animationManager.getCurrentFrame()) * transform->width;
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

    void playOneshot(const char* animName, bool isOneShot = false)
    {
        animationManager.playOneshot(animName, isOneShot);
    }
};
