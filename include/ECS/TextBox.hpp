#pragma once

#include "ULlabel.hpp"
#include "Components.hpp"
#include "SDL2/SDL.h"

class TextBox : public Component {
public:
    TextBox(int x, int y, std::string text, std::string font, SDL_Color color, int fontSize = 24)
    {
        label = new ULlabel(x, y, text, font, color, fontSize);
        centerText();
    }

    ~TextBox() {
        delete label;
    }

    void draw() override {
        if (focused) {
            SDL_SetRenderDrawColor(Game::renderer, 255, 255, 0, 255);
            SDL_Rect rect = label->getRect();
            SDL_RenderDrawRect(Game::renderer, &rect);
        }
        label->draw();
    }

    void update() override {
        // Nếu muốn có logic nhấp nháy con trỏ nhập văn bản, có thể thêm tại đây
    }

    void handleInput(SDL_Event& e) {
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            int mx, my;
            SDL_GetMouseState(&mx, &my);
            SDL_Rect rect = label->getRect();
            SDL_Point point = { mx, my };
            focused = SDL_PointInRect(&point, &rect); // 
        }

        if (focused && e.type == SDL_TEXTINPUT) {
            appendChar(e.text.text);
        } else if (focused && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE) {
            deleteLastChar();
        }
    }

    void setText(const std::string& msg) {
        label->setLabelText(msg);
        centerText();
    }

    std::string getText() const { return label->getText(); }

private:
    ULlabel* label;
    bool focused = false;

    void centerText() {
        SDL_Rect rect = label->getRect();
        rect.x -= rect.w / 2;
        rect.y -= rect.h / 2;
        label->setPosition(rect.x, rect.y);
    }

    void appendChar(const char* c) {
        std::string newText = label->getText() + c;
        label->setLabelText(newText);
        centerText();
    }

    void deleteLastChar() {
        std::string t = label->getText();
        if (!t.empty()) {
            t.pop_back();
            label->setLabelText(t);
            centerText();
        }
    }
};
