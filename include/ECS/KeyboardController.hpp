#pragma once

#include"../Game.hpp"
#include"ECS.hpp"
#include"Components.hpp"
#include <cmath>

class KeyboardController : public Component
{

public: 
    TransformComponent *transform;
	SpriteComponent *sprite;
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

	Uint32 lastShootTime = 0;
	Uint32 shootCooldown = 600;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override {

		transform->velocity.x = 0;
		transform->velocity.y = 0;

		int mouseX, mouseY;
		Uint32 mouseButtons = SDL_GetMouseState(&mouseX, &mouseY);
		float deltaX = mouseX + Game::camera.x - transform->position.x;
		float deltaY = mouseY + Game::camera.y - transform->position.y;

		//normalize a Vector.
		float length = std::sqrt(deltaX * deltaX + deltaY * deltaY);
		if (length != 0)
		{
			deltaX /= length;
			deltaY /= length;
		}

		if (transform->velocity.x == 0 && transform->velocity.y == 0)
		{
			sprite->Play("Idle");
		}
		
		if (keystates[SDL_SCANCODE_W]) {
			transform->velocity.y = -2;
			sprite->Play("walk_up");
		}
		if (keystates[SDL_SCANCODE_S]) {
			transform->velocity.y = 2;
			sprite->Play("walk_down");
		}
		if (keystates[SDL_SCANCODE_D]) {
			transform->velocity.x = 2;
			sprite->Play("walk_right");
		}
		if (keystates[SDL_SCANCODE_A]) {
			transform->velocity.x = -2;
			sprite->Play("walk_left");
		}
		if (mouseButtons & SDL_BUTTON(SDL_BUTTON_LEFT))
		{   
			Uint32 currentTime = SDL_GetTicks(); 
			if (currentTime > lastShootTime + shootCooldown)
			{
				Vector2D direction(deltaX, deltaY);
				float speed = 3.0f;
				Game::assets->CreateProjectileP(transform->position, direction * speed, 150, 1, "projectileP");
				lastShootTime = currentTime;
			}
		}	
	}
};