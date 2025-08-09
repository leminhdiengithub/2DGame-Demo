#pragma once

#include"../Game.hpp"
#include"../Collision.hpp"
#include"ECS.hpp"
#include"Components.hpp"
#include <cmath>

class EnemyComponent : public Component
{
public:

    TransformComponent *transform;
    SpriteComponent *sprite;
    ColliderComponent* collider;
    float startX;
    float speed;
    float range;
    int healbath = 3;
    bool hited = false;
    bool deathStarted = false;
    bool isHiting = false;
    bool isDying = false;
    Uint32 currentTime;
    Uint32 lastTime = 0;
    Uint32 coolTime = 500;

    EnemyComponent(float moveSpeed = 1.0f, float moveRange = 100.0f) : speed(moveSpeed), range(moveRange)
    {}

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
        collider = &entity->getComponent<ColliderComponent>();

        startX = transform->position.x;
        transform->velocity.x = speed;

    }

    void update() override
    {
        if (!deathStarted && !hited ) {
            transform->position.x += transform->velocity.x;

            if (transform->position.x >= startX + range) {
                sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                transform->velocity.x = -speed;
            }
            if (transform->position.x <= startX - range) {
                sprite->spriteFlip = SDL_FLIP_NONE;
                transform->velocity.x = speed;
            }
            sprite->Play("Idle");
        }

        if (isHiting == true)
        {
            hitEnemy();
            return;
        }
        if (isDying == true && healbath <= 0)
        {
            DeadEnemy();
            return;
        }
    }
    void DeadEnemy() 
    {
        currentTime = SDL_GetTicks();

        if (!deathStarted) {
            // Bắt đầu animation chết
            sprite->playOneshot("Dead", true);
            deathStarted = true;
            lastTime = currentTime;
            transform->velocity.x = 0;
        }
        // Sau khi đủ thời gian -> hủy entity
        if (deathStarted && currentTime > lastTime + coolTime) 
        {
            entity->destroy();
        }
    }
    void hitEnemy()
    {
        currentTime = SDL_GetTicks();
        if (!hited)
        {
            sprite->playOneshot("Hit", true);
            hited = true;
            lastTime = currentTime;
            transform->velocity.x = 0;
        }
        if (hited && currentTime > lastTime + coolTime)
        {
            hited = false;
            isHiting = false;
            if (sprite->spriteFlip == SDL_FLIP_HORIZONTAL)
            {
                transform->velocity.x = -speed;
            } else 
            {
                transform->velocity.x = speed;
            }
        }
    }
};
