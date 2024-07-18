#pragma once

#include"Components.hpp"
#include"SDL2/SDL.h"
#include"SDL2/SDL_mixer.h"

class SoundComponent : public Component
{
    private:
        Mix_Music* backgroundMusic;
    public:
        SoundComponent( const char* path, int frequency, Uint16 format, int channels, int chunksize)
        {
            if( Mix_OpenAudio( frequency, format, channels, chunksize ) < 0 )
            {
                std::cout << " SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
            }
            setSound(path);
        }

        ~SoundComponent()
        {
            Mix_FreeMusic(backgroundMusic);
        }

        void setSound(const char* path)
        {
            backgroundMusic = Mix_LoadMUS(path);
            if (!backgroundMusic)
            {
                std::cout << "Failed to load sound: " << Mix_GetError() << std::endl;
            }
        }

        void PlayMusic()
        {
            if (backgroundMusic)
            {
                Mix_PlayMusic(backgroundMusic, -1);
            }
        }
};

