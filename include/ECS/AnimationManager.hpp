#pragma once
#include "Animation.hpp"
#include <map>

class AnimationManager
{
private:
    std::map<std::string, Animation> animations;// const char* to std::string
    int xAnimIndex = 0;
    int yAnimIndex = 0;
    int frames = 0;
    int speed = 100;
    int frameWidth  = -1;
    int frameHeight = -1;
    
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
        const Animation& anim = animations.at(key); // ném exception rõ ràng nếu key sai
        frames = animations[key].frames;
        xAnimIndex = animations[key].xIndex;
        yAnimIndex = animations[key].yIndex;
        speed = animations[key].speed;
        frameWidth  = animations[key].frameWidth;   // thêm mới
        frameHeight = animations[key].frameHeight;  // thêm mới
        oneShot = false;
        startTime = SDL_GetTicks(); // reset frame
    }

    void playOneshot(const char* animName, bool isOneShot = false)
    {
        std::string key(animName);
        const Animation& anim = animations.at(key); // ném exception rõ ràng nếu key sai
        frames = animations[key].frames;
        xAnimIndex = animations[key].xIndex;
        yAnimIndex = animations[key].yIndex;
        speed = animations[key].speed;
        frameWidth  = animations[key].frameWidth;   // thêm mới
        frameHeight = animations[key].frameHeight;  // thêm mới
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

    bool isAnimFinished() const
    {
        if (!oneShot) return false;
        Uint32 elapsed = SDL_GetTicks() - startTime;
        return elapsed >= static_cast<Uint32>(frames * speed);
        
    }

    bool isPlayingOneshot() const { return oneShot; }
    int getStartTime() const {return startTime; }
    int getFrameWidth() const  { return frameWidth; }   // thêm mới
    int getFrameHeight() const { return frameHeight; }  // thêm mới
    int getFrames() const { return frames; }
    int getXAnimIndex() const { return xAnimIndex; }
    int getYAnimIndex() const { return yAnimIndex; }
    int getSpeed() const { return speed; }
};
