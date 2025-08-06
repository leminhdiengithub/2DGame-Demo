#pragma once

#include "Components.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

class AudioComponent : public Component
{
private:
    Mix_Music *backgroundMusic;
    Mix_Chunk *soudnEffect;

public:
    AudioComponent(std::string id, bool isMusicType)
    {
        if (isMusicType == true)
        {
            setAu(id);
        }
        if (isMusicType == false)
        {
            setSoudE(id);
        }
    }

    ~AudioComponent()
    {
    }

    void setAu(std::string id)
    {
        backgroundMusic = Game::assets->GetMusic(id);
    }

    void setSoudE(std::string id)
    {
        soudnEffect = Game::assets->GetSoundEffect(id);
    }

    void playMusic(int loops = -1)
    {
        if (backgroundMusic)
        {
            if (Mix_PlayMusic(backgroundMusic, loops) == -1)
            {
                std::cerr << "Error playing music: " << Mix_GetError() << std::endl;
            }
        }
    }

    void playSoundEffect(int loops = 0)
    {

        if (Mix_PlayChannel(-1, soudnEffect, loops) == -1)
        {
            std::cerr << "Error playing sound effect: " << Mix_GetError() << std::endl;
            Mix_HaltChannel(0);
            Mix_PlayChannel(0, soudnEffect, 0);
        }
    }

    bool isPlaying() const
    {
        return Mix_PlayingMusic() != 0;
    }

    void stopMusic()
    {
        Mix_HaltMusic();
    }

    void cleanAudio()
    {
        if (backgroundMusic)
        {
            Mix_FreeMusic(backgroundMusic);
            backgroundMusic = nullptr;
        }

        if (soudnEffect)
        {
            Mix_FreeChunk(soudnEffect);
            soudnEffect = nullptr;
        }        
        Mix_CloseAudio();
    }
};
