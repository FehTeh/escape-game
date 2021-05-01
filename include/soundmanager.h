#pragma once

#include <SDL2/SDL_mixer.h>

class SoundManager {
public:
	void init();
    void playSound(Mix_Chunk* sound);
    void playMusic(Mix_Music* music);
};