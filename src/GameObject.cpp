#include"GameObject.hpp"
#include"TextureManager.hpp"

GameObject::GameObject(const char* texturesheet, int x, int y)
{
    objTexture = TextureManager::loadTexture(texturesheet);

    xpos = x;
    ypos = y;

}

void GameObject::Update()
{

    xpos++;
    ypos++;

    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2; /* Set độ to nhỏ của hình ảnh */
}

void GameObject::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}