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

    int frameW = 0, frameH = 0;

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
        animationManager.addAnimation("attack_down",  Animation(0, 5, 3, 100, 96, 80));
        animationManager.addAnimation("attack_top", Animation(0, 6, 3, 100, 96, 80));
        animationManager.addAnimation("attack_right", Animation(0, 7, 3, 100, 96, 80));
        animationManager.addAnimation("attack_left",  Animation(0, 8, 3, 100, 96, 80));

        animationManager.Play("Idle");
        setTex(id);
    }

    SpriteComponent(std::string id, bool isAnimated, const char* charName)
    {
        animated = isAnimated;

        if(std::string(charName) == "Souls")
        {
            animationManager.addAnimation("Idle", Animation(0, 0, 8, 100));
            animationManager.addAnimation("walk", Animation(0, 1, 8, 100));
            animationManager.addAnimation("Attack", Animation(0, 2, 13, 100));
            animationManager.addAnimation("Hit", Animation(0, 5, 5, 100));
            animationManager.addAnimation("Dead", Animation(0, 6, 7 ,100));
            animationManager.Play("walk");
            setTex(id);
        }
        if (std::string(charName) == "projectile")
        {
            animationManager.addAnimation("Idle", Animation(0, 8, 6, 50));
            animationManager.addAnimation("destroy", Animation(5, 8, 6, 50));
            animationManager.playOneshot("Idle", true);
            setTex(id);
        }
        if (std::string(charName) == "projectileP")
        {
            animationManager.addAnimation("Idle", Animation(0, 0, 6, 50));
            animationManager.addAnimation("destroy", Animation(5, 0, 6, 50));
            animationManager.playOneshot("Idle", true);
            setTex(id);
        }
        if (std::string(charName) == "treeDemo")
        {
            animationManager.addAnimation("Idle", Animation(0, 0, 16, 100));
            animationManager.Play("Idle");
            setTex(id);
        }
        if (std::string(charName) == "rockDemo")
        {
            animationManager.addAnimation("Idle", Animation(5, 15, 1, 100));
            animationManager.Play("Idle");
            setTex(id);
        }
        if (std::string(charName) == "boxDemo")
        {
            animationManager.addAnimation("Idle", Animation(3, 0, 1, 100));
            animationManager.Play("Idle");
            setTex(id);
        }
        if (std::string(charName) == "fireplace")
        {
            animationManager.addAnimation("Idle", Animation(0, 0, 6, 100));
            animationManager.Play("Idle");
            setTex(id);
        }
        
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
            int fw = animationManager.getFrameWidth();
            int fh = animationManager.getFrameHeight();
            fw = (fw > 0) ? fw : transform->width;
            fh = (fh > 0) ? fh : transform->height;

            srcRect.w = fw;
            srcRect.h = fh;
            srcRect.x = animationManager.getXAnimIndex() * transform->width
                    + animationManager.getCurrentFrame() * fw;
            srcRect.y = animationManager.getYAnimIndex() * transform->height;
            destRect.w = fw * transform->scale;
            destRect.h = fh * transform->scale;
        }

        destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
        destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;

        if (!animated) // sprite tĩnh vẫn dùng transform->width/height như cũ
        {
            destRect.w = transform->width * transform->scale;
            destRect.h = transform->height * transform->scale;
        }
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
   
    bool isPlayingOneshot() const { return animationManager.isPlayingOneshot(); }
    bool isAnimFinished() const {return animationManager.isAnimFinished();}
    int getStartTime() const {return animationManager.getStartTime();}
};
