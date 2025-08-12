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
    int healbath = 7;
    bool hited = false;
    bool deathStarted = false;
    bool targeted = false;
    bool isHiting = false;
    bool isDying = false;
    bool isTarget = false;
    Uint32 currentTime;
    Uint32 lastTime = 0;
    Uint32 coolTime = 500;

    EnemyComponent(float moveSpeed = 0.5f, float moveRange = 100.0f) : speed(moveSpeed), range(moveRange)
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
        if (isDying && healbath <= 0) {
            DeadEnemy();
            return;
        }

        if (isHiting) {
            hitEnemy();
            return;
        }

        if (isTarget)
        {
            EnemyTarget();
            return;
        }
        
        // Only move if not dying or being hit
        if (!deathStarted && !hited) {
            transform->position.x += transform->velocity.x;

            if (transform->position.x >= startX + range) {
                sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                transform->velocity.x = -speed;
            }
            if (transform->position.x <= startX - range) {
                sprite->spriteFlip = SDL_FLIP_NONE;
                transform->velocity.x = speed;
            }
        }
    }

    void DeadEnemy() 
    {
        currentTime = SDL_GetTicks();

        if (!deathStarted) {
            sprite->playOneshot("Dead", true);
            deathStarted = true;
            lastTime = currentTime;
            transform->velocity.x = 0;
        }
        // Destroy entity after animation
        if (deathStarted && currentTime > lastTime + coolTime) 
        {
            entity->destroy();
            isDying = false; // Reset dying flag (optional, since entity is destroyed)
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
            // Resume movement after hit
            if (sprite->spriteFlip == SDL_FLIP_HORIZONTAL)
                transform->velocity.x = -speed;
            else 
                transform->velocity.x = speed;
            sprite->Play("walk");
        }
    }

    void EnemyTarget()
    {
        currentTime = SDL_GetTicks();
        if (!targeted)
        {
            sprite->Play("Idle");
            targeted = true;
            lastTime = currentTime;
            transform->velocity.x = 0;
        }

        if (targeted && currentTime > lastTime + coolTime)
        {
            targeted = false;
            isTarget = false;
            // Resume movement
            if (sprite->spriteFlip == SDL_FLIP_HORIZONTAL)
                transform->velocity.x = -speed;
            else 
                transform->velocity.x = speed;
            sprite->Play("walk");
        }
    } 
    
    void EnemyAttack(const Vector2D& playerCenter, const Vector2D& enemyCenter) 
    {
        currentTime = SDL_GetTicks();
        Uint32 coolTimeShoot = 1300;

        //Enemy center
        float enemyCenterX = transform->position.x + (transform->width * transform->scale) / 2.0f;
        float enemyCenterY = transform->position.y + (transform->height * transform->scale) / 2.0f;

        float deltaX = playerCenter.x - enemyCenterX;
        float deltaY = playerCenter.y - enemyCenterY;

        // Chuẩn hóa vector
        float length = std::sqrt(deltaX * deltaX + deltaY * deltaY);
        if (length != 0)
        {
            deltaX /= length;
            deltaY /= length;
        }

        // Shoot
        if (currentTime > lastTime + coolTimeShoot)
        {
            transform->velocity.x = 0;
            sprite->playOneshot("Attack", true);
            Vector2D direction(deltaX, deltaY);
            float speed = 3.0f;
            Game::assets->CreateProjectile(
                enemyCenter,
                direction * speed,
                150, 1, "projectile"
            );
            lastTime = currentTime;
        } 
    }
};
