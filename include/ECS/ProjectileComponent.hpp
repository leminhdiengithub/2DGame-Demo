#pragma once

#include"ECS.hpp"
#include "Components.hpp"
#include "../Vector2D.hpp"

class ProjectileComponent : public Component
{
public:
    ProjectileComponent(int rng, int sp, Vector2D vel) : range(rng), speed(sp), velocity(vel)
    {}
    ~ProjectileComponent()
    {}

    void init() override
    {
        transfrom = &entity->getComponent<TransformComponent>();
        transfrom->velocity = velocity;
    }

    void update() override
    {
        distance += speed;

        if (distance > range)
        {
            std::cout << "Out of Range" << std::endl;
            entity->destroy();

        } else if ( transfrom->position.x > Game::camera.x + Game::camera.w ||
                    transfrom->position.x < Game::camera.x ||
                    transfrom->position.y > Game::camera.y + Game::camera.h ||
                    transfrom->position.y < Game::camera.y)
        {
            std::cout << "Out of bounds" << std::endl;
            entity->destroy();
        }
    }
private:

    TransformComponent* transfrom;
    int range = 0;
    int speed = 0;
    int distance = 0;
    Vector2D velocity;

};