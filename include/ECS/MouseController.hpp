#pragma once

#include"../Game.hpp"
#include"ECS.hpp"
#include"Components.hpp"
#include "Vector2D.hpp"

class MouseController : public Component {
private:
    bool dragging = false;
    Vector2D offset;

public:
    void update() override {
        auto& transform = entity->getComponent<TransformComponent>();

        int mx, my;
        SDL_GetMouseState(&mx, &my);

        // Tính tọa độ chuột theo hệ tọa độ thế giới
        Vector2D mouseWorld(mx + Game::camera.x, my + Game::camera.y);

        // Khi nhấn chuột trái
        if (Game::event.type == SDL_MOUSEBUTTONDOWN && Game::event.button.button == SDL_BUTTON_LEFT) {
            SDL_Rect entityRect = {
                static_cast<int>(transform.position.x),
                static_cast<int>(transform.position.y),
                static_cast<int>(transform.width * transform.scale),
                static_cast<int>(transform.height * transform.scale)
            };

            // Tạo biến SDL_Point để truyền vào hàm
            SDL_Point mousePoint = {
                static_cast<int>(mouseWorld.x),
                static_cast<int>(mouseWorld.y)
            };

            // Nếu chuột nằm trong sprite => bắt đầu kéo
            if (SDL_PointInRect(&mousePoint, &entityRect)) {
                dragging = true;
                offset = mouseWorld - transform.position;
            }
        }

        // Khi thả chuột trái => dừng kéo
        if (Game::event.type == SDL_MOUSEBUTTONUP && Game::event.button.button == SDL_BUTTON_LEFT) {
            dragging = false;
        }

        // Di chuyển entity khi kéo chuột
        if (dragging && Game::event.type == SDL_MOUSEMOTION) {
            transform.position = mouseWorld - offset;

            // In ra vị trí hiện tại (tùy chọn)
            std::cout << "Transform" << " " << "Position: x=" << transform.position.x
                      << " y=" << transform.position.y << std::endl;
        }
    }
};

