#pragma once

#include"../Game.hpp"
#include"ECS.hpp"
#include"Components.hpp"
#include <cmath>

class KeyboardController : public Component
{


private:
    float lungeSpeed = 4.0f;
    float lungeDirX = 0, lungeDirY = 0;
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

		float length = std::sqrt(deltaX * deltaX + deltaY * deltaY);
		if (length != 0)
		{
			deltaX /= length;
			deltaY /= length;
		}

		bool isAttacking = (mouseButtons & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
		bool attackInProgress = sprite->isPlayingOneshot() && !sprite->isAnimFinished();

		bool moving = false;
		const char* moveAnim = "Idle";

		if (attackInProgress)
		{
			// Không cho WASD điều khiển tự do -> thay bằng lunge theo hướng đã khóa lúc bắt đầu attack
			Uint32 elapsed = SDL_GetTicks() - sprite->getStartTime(); // cần getter này (đã đề cập trước)
			float t = static_cast<float>(elapsed) / 300.0f; // 300ms = tổng thời lượng attack
			float decay = std::max(0.0f, 1.0f - t);          // giảm dần từ 1 -> 0

			transform->velocity.x = lungeDirX * lungeSpeed * decay;
			transform->velocity.y = lungeDirY * lungeSpeed * decay;
		}
		else
		{
			if (keystates[SDL_SCANCODE_W]) { transform->velocity.y = -2; moveAnim = "walk_up";    moving = true; }
			if (keystates[SDL_SCANCODE_S]) { transform->velocity.y =  2; moveAnim = "walk_down";  moving = true; }
			if (keystates[SDL_SCANCODE_D]) { transform->velocity.x =  2; moveAnim = "walk_right"; moving = true; }
			if (keystates[SDL_SCANCODE_A]) { transform->velocity.x = -2; moveAnim = "walk_left";  moving = true; }
		}

		if (isAttacking)
		{
			bool canStartNewAttack = !sprite->isPlayingOneshot() || sprite->isAnimFinished();

			if (canStartNewAttack)
			{
				const char* attackAnim;
				if (std::abs(deltaX) > std::abs(deltaY))
					attackAnim = (deltaX >= 0) ? "attack_right" : "attack_left";
				else
					attackAnim = (deltaY >= 0) ? "attack_down" : "attack_top";

				sprite->playOneshot(attackAnim, true);
				lungeDirX = deltaX; // khóa hướng lao tại thời điểm BẮT ĐẦU attack, không đổi giữa chừng
				lungeDirY = deltaY;
			}

			Uint32 currentTime = SDL_GetTicks();
			if (currentTime > lastShootTime + shootCooldown)
			{
				Vector2D direction(deltaX, deltaY);
				float speed = 3.0f;
				Game::assets->CreateProjectileP(transform->position, direction * speed, 150, 1, "projectileP");
				lastShootTime = currentTime;
			}
		}
		else if (!attackInProgress && moving)
		{
			sprite->Play(moveAnim);
		}
		else if (!attackInProgress)
		{
			sprite->Play("Idle");
		}
	}
};