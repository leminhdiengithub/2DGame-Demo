#pragma once

#include"Components.hpp"
#include"SDL2/SDL.h"
#include"SDL2/SDL_mixer.h"

class AudioComponent : public Component
{
    private:
        Mix_Music* backgroundMusic;
    public:
        AudioComponent( const char* path)
        {
            if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
            {
                std::cout << " SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
            }
            loadMusic(path);
        }

        ~AudioComponent()
        {
            Mix_FreeMusic(backgroundMusic);
        }

        void loadMusic(const char* path)
        {
            backgroundMusic = Mix_LoadMUS(path);
            if (!backgroundMusic)
            {
                std::cout << "Failed to load sound: " << Mix_GetError() << std::endl;
                exit(0);
            }
        }

        void playMusic()
        {
            if (backgroundMusic)
            {
                Mix_PlayMusic(backgroundMusic, -1);
            }
        }

        void isPlaying()
        {
            Mix_PlayingMusic();
        }
};

