#include "Menu/TextBox.hpp"
#include<Game.hpp>

textBox::textBox() {
	x = 0;
	y = 0;
	c = { 255,255,255 };
	message = "test";
	size = 24;
};
textBox::~textBox() {};

void textBox::renderText() {

	TTF_Font* Sans = TTF_OpenFont("res/font/EvilEmpire-4BBVK.ttf", size);
	if (!Sans) 
	{
    	std::cout << "Error " << TTF_GetError() << std::endl;
	}
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, message, c);
	if (!surfaceMessage) return;
	TTF_CloseFont(Sans);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage);

	SDL_Rect Message_rect; //create a rect

	Message_rect.w = surfaceMessage->w; // controls the width of the rect
	Message_rect.h = surfaceMessage->h; // controls the height of the rect
	Message_rect.x = x - (Message_rect.w /2);  //controls the rect's x coordinate 
	Message_rect.y = y - (Message_rect.h / 2); // controls the rect's y coordinte

	SDL_RenderCopy(Game::renderer, Message, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

SDL_Rect textBox::getRect() {
    TTF_Font* Sans = TTF_OpenFont("res/font/EvilEmpire-4BBVK.ttf", size);
    if (!Sans) return { x, y, 0, 0 };

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, message, c);
    SDL_Rect rect = {
        x - surfaceMessage->w / 2,
        y - surfaceMessage->h / 2,
        surfaceMessage->w,
        surfaceMessage->h
    };

    SDL_FreeSurface(surfaceMessage);
    TTF_CloseFont(Sans);

    return rect;
}
