#pragma once

#include"ECS.hpp"
#include "Components.hpp"

class ProjectileComponent : public Component
{
public:
    ProjectileComponent(int rng, int sp) : range(rng), speed(sp)
    {}
    ~ProjectileComponent()
    {}

    void init() override
    {
        transfrom = &entity->getComponent<TransformComponent>();
    }

    void update() override
    {
        distance += speed;

        if (distance > range)
        {
            entity->destroy();

        } else if ( transfrom->position.x > Game::camera.x + Game::camera.w ||
                    transfrom->position.x < Game::camera.x ||
                    transfrom->position.y > Game::camera.y + Game::camera.h ||
                    transfrom->position.y < Game::camera.y)
        {
            entity->destroy();
        }
    }
private:

    TransformComponent* transfrom;
    int range = 0;
    int speed = 0;
    int distance = 0;

};