#pragma once
#include "Animation.hpp"
#include <map>

class AnimationManager
{
private:
    std::map<const char*, Animation> animations;
    int animIndex = 0;
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
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }

    int getFrames() const { return frames; }
    int getAnimIndex() const { return animIndex; }
    int getSpeed() const { return speed; }
};
