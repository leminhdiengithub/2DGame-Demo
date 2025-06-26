#pragma once

#include "ECS/ECS.hpp"
#include "../AssetManager.hpp"
#include "../Game.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class ULlabel : public Component {
public:
    ULlabel(int xpos, int ypos, std::string text, std::string font, SDL_Color colour, int fontSize = 24)
        : labelText(text), labelFont(font), textColour(colour), fontSize(fontSize)
    {
        position.x = xpos;
        position.y = ypos;
        updateTexture();
    }

    virtual ~ULlabel() {
        if (labelTexture) SDL_DestroyTexture(labelTexture);
    }

    virtual void draw() override {
        SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
    }

    void setLabelText(const std::string& text) {
        labelText = text;
        updateTexture();
    }

    std::string getText() const { return labelText; }

    SDL_Rect getRect() const { return position; }

    void setPosition(int x, int y) {
        position.x = x;
        position.y = y;
    }

protected:
    void updateTexture() {
        SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(labelFont), labelText.c_str(), textColour);
        if (labelTexture) SDL_DestroyTexture(labelTexture);
        labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
        SDL_FreeSurface(surf);

        SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
    }

protected:
    SDL_Rect position;
    std::string labelText;
    std::string labelFont;
    SDL_Color textColour;
    SDL_Texture* labelTexture = nullptr;
    int fontSize;
};
