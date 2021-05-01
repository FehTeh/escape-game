#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "soundmanager.h"

void SoundManager::init()
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void SoundManager::playSound(Mix_Chunk* sound)
{
    Mix_PlayChannel(-1, sound, 0);
}

void SoundManager::playMusic(Mix_Music* music)
{
    Mix_PlayMusic(music, -1);
}