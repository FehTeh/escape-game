#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "windowmanager.h"

enum class TextureKey
{
    Wall,
    WallTop,
    Char_Front,
    Char_Front_2,
    Char_Front_3,
    Char_Back,
    Char_Back_2,
    Char_Right,
    Char_Right_2,
    Char_Left,
    Char_Left_2
};

enum class SoundKey
{
    MenuSelection,
    MenuSelected,
    FootStep
};

enum class MusicKey
{
    StartWindow
};

enum class FontKey
{
    Font16,
    Font24
};

enum class ColorKey
{
    White,
    Red,
    Green,
    Blue,
    Black
};

class ResourceManager {
public:
	void init(WindowManager window);
    SDL_Texture* getTexture(TextureKey textureKey);
    Mix_Chunk* getSound(SoundKey soundKey);
    Mix_Music* getMusic(MusicKey musicKey);
    TTF_Font* getFont(FontKey fontKey);
    SDL_Color getColor(ColorKey colorKey);
    void cleanUp();
private:
    SDL_Texture* textures[11];
    Mix_Chunk* sounds[3];
    Mix_Music* musics[1];
    TTF_Font* fonts[2];
    SDL_Color colors[5];
};