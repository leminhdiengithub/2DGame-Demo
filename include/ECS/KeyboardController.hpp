#pragma once

#include"../Game.hpp"
#include"ECS.hpp"
#include"Components.hpp"

class KeyboardController : public Component
{

public: 
    TransformComponent *transform;
	SpriteComponent *sprite;
    const Uint8* keystates = SDL_GetKeyboardState(NULL); 


    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override {

		transform->velocity.x = 0;
		transform->velocity.y = 0;
		if (transform->velocity.x == 0 && transform->velocity.y == 0)
		{
			sprite->Play("Idle");
		}
		
		if (keystates[SDL_SCANCODE_W]) {
			transform->velocity.y = -1;
			sprite->Play("walk_up");
		}
		if (keystates[SDL_SCANCODE_S]) {
			transform->velocity.y = 1;
			sprite->Play("walk_down");
		}
		if (keystates[SDL_SCANCODE_D]) {
			transform->velocity.x = 1;
			sprite->Play("walk_right");
		}
		if (keystates[SDL_SCANCODE_A]) {
			transform->velocity.x = -1;
			sprite->Play("walk_left");
		}
	}
};