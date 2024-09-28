#pragma once

#include"../Game.hpp"
#include"ECS.hpp"
#include"Components.hpp"

class KeyboardController : public Component
{

public: 
    TransformComponent *transform;
	SpriteComponent *sprite;
	AudioComponent *song;
    const Uint8* keystates = SDL_GetKeyboardState(NULL);


    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		//song = &entity->getComponent<AudioComponent>();
		//song = &entity->addComponent<AudioComponent>("res/sounds/Projectile_sound.mp3");
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
		if (keystates[SDL_SCANCODE_K])
		{
			sprite->Play("attack");
		}
		if (keystates[SDL_SCANCODE_J])
		{
			Game::assets->CreateProjectile(Vector2D(transform->position.x * 0.5, transform->position.y *0.5),Vector2D(2,0) ,200, 2, "projectile");
			//song->playMusic();
		}
	}
};