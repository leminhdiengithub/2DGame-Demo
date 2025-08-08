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
    Uint32 currentTime = SDL_GetTicks();

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

        transform->position.x += transform->velocity.x;

        if (transform->position.x >= startX + range)
        {
            sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
            transform->velocity.x = -speed;
        }

        if (transform->position.x <= startX - range)
        {
            sprite->spriteFlip = SDL_FLIP_NONE;
            transform->velocity.x =  speed;
        }   

    }

};
