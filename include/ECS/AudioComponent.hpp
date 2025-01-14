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
                std::cerr << " SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
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
                std::cerr << "Failed to load sound: " << Mix_GetError() << std::endl;
            }
        }

        void playMusic(int loops = -1) {
            if (backgroundMusic) {
                if (Mix_PlayMusic(backgroundMusic, loops) == -1) {
                    std::cerr << "Error playing music: " << Mix_GetError() << std::endl;
                }
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

        void cleanAudio() {
        if (backgroundMusic) {
            Mix_FreeMusic(backgroundMusic);
            backgroundMusic = nullptr;
        }
        Mix_CloseAudio(); // Đóng hệ thống âm thanh nếu không cần nữa
    }
};

