#pragma once

#include "ECS.hpp"
#include "Components.hpp"
#include "../Vector2D.hpp"

class ProjectileComponent : public Component
{
public:
    ProjectileComponent(int rng, int sp, Vector2D vel) : range(rng), speed(sp), velocity(vel)
    {
    }
    ~ProjectileComponent()
    {
    }

    void init() override
    {
        /* Để có thể sử dụng transfrom và projectile thì entity(projectile) phải được thêm TransformComponent
        và AudioComponent*/
        transfrom = &entity->getComponent<TransformComponent>();
        transfrom->velocity = velocity;
        if (entity->hasComponent<SpriteComponent>())
        {
            sprite = &entity->getComponent<SpriteComponent>();
        }
        audio =  &entity->getComponent<AudioComponent>();     
    }

    void update() override
    {
        if (!hitted)
        {
            distance += speed;

            if (distance > range)
            {
                std::cout << "Out of Range" << std::endl;
                StartDestroy();
            }
            else if (transfrom->position.x > Game::camera.x + Game::camera.w ||
                    transfrom->position.x < Game::camera.x ||
                    transfrom->position.y > Game::camera.y + Game::camera.h ||
                    transfrom->position.y < Game::camera.y)
            {
                std::cout << "Out of bounds" << std::endl;
                StartDestroy();
            }
        }
        else
        {
            currentTime = SDL_GetTicks();
            if (currentTime > lastTime + coolTime)
            {
                entity->destroy();
            }
        }
    }

    void StartDestroy()
    {
        if (!hitted)
        {
            if (sprite) sprite->playOneshot("destroy", true);
            // if (audio) audio->play("explode");
            transfrom->velocity = {0, 0};
            hitted = true;
            lastTime = SDL_GetTicks();
        }
    }

private:
    SpriteComponent* sprite = nullptr;
    TransformComponent *transfrom;
    AudioComponent *audio;  
    int range = 0;
    int speed = 0;
    int distance = 0;
    bool hitted = false;
    Uint32 currentTime;
    Uint32 lastTime = 0;
    Uint32 coolTime = 500;
    Vector2D velocity;
};