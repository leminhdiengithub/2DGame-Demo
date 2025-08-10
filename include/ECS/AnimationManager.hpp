#pragma once
#include "Animation.hpp"
#include <map>

class AnimationManager
{
private:
    std::map<std::string, Animation> animations;
    int xAnimIndex = 0;
    int yAnimIndex = 0;
    int frames = 0;
    int speed = 100;
    
    bool oneShot = false;
    Uint32 startTime = 0;
    const char* currentAnimName = nullptr;

public:
    AnimationManager() = default;

    void addAnimation(const char* name, Animation anim)
    {
        animations.emplace(std::string(name), anim);
    }

    void Play(const char* animName)
    {
        std::string key(animName);
        frames = animations[key].frames;
        xAnimIndex = animations[key].xIndex;
        yAnimIndex = animations[key].yIndex;
        speed = animations[key].speed;
        oneShot = false;
        startTime = SDL_GetTicks(); // reset frame
    }

    void playOneshot(const char* animName, bool isOneShot = false)
    {
        std::string key(animName);
        frames = animations[key].frames;
        xAnimIndex = animations[key].xIndex;
        yAnimIndex = animations[key].yIndex;
        speed = animations[key].speed;
        oneShot = isOneShot;
        startTime = SDL_GetTicks();
    }

    int getCurrentFrame() const
    {
        if (oneShot)
        {
            Uint32 elapsed = SDL_GetTicks() - startTime;
            int frame = elapsed / speed;
            if (frame >= frames) frame = frames - 1; // Giữ lại frame cuối
            return frame;
        }
        else
        {
            return (SDL_GetTicks() / speed) % frames;
        }
    }

    int getFrames() const { return frames; }
    int getXAnimIndex() const { return xAnimIndex; }
    int getYAnimIndex() const { return yAnimIndex; }
    int getSpeed() const { return speed; }
};
