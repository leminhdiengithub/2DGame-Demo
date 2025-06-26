class ULlabel : public Component
{
public:
    ULlabel(int xpos, int ypos, std::string text, std::string font, SDL_Color colour, int fontSize = 24)
        : labelText(text), labelFont(font), textColour(colour), fontSize(fontSize)
    {
        position.x = xpos;
        position.y = ypos;
        setLabelText(labelText);
    }

    virtual ~ULlabel() {
        if (labelTexture) SDL_DestroyTexture(labelTexture);
    }

    virtual void setLabelText(const std::string& text)
    {
        labelText = text;
        SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(labelFont), text.c_str(), textColour);
        if (labelTexture) SDL_DestroyTexture(labelTexture);
        labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
        SDL_FreeSurface(surf);

        SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
    }

    virtual void draw() override {
        SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
    }

protected:
    SDL_Rect& getPosition() { return position; }

protected:
    SDL_Rect position;
    std::string labelText;
    std::string labelFont;
    SDL_Color textColour;
    SDL_Texture* labelTexture = nullptr;
    int fontSize;
};
