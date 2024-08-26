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

    int getFrames() const { return frames; }
    int getXAnimIndex() const { return xAnimIndex; }
    int getYAnimIndex() const { return yAnimIndex; }
    int getSpeed() const { return speed; }
};
