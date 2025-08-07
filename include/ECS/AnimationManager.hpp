#pragma once
#include "Animation.hpp"
#include <map>

class AnimationManager
{
private:
    std::map<const char*, Animation> animations;
    int xAnimIndex = 0;
    int yAnimIndex = 0;
    int frames = 0;
    int speed = 100;
    
    bool oneShot = false;
    Uint32 startTime = 0;

public:
    AnimationManager() = default;

    void addAnimation(const char* name, Animation anim)
    {
        animations.emplace(name, anim);
    }

    void Play(const char* animName)
    {
        frames = animations[animName].frames;
        xAnimIndex = animations[animName].xIndex;
        yAnimIndex = animations[animName].yIndex;
        speed = animations[animName].speed;
    }

    void playOneshot(const char* animName, bool isOneShot = false)
    {
        frames = animations[animName].frames;
        xAnimIndex = animations[animName].xIndex;
        yAnimIndex = animations[animName].yIndex;
        speed = animations[animName].speed;
        oneShot = isOneShot;
        startTime = SDL_GetTicks(); // đánh dấu thời gian bắt đầu
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
