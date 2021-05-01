#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "resourcemanager.h"

void ResourceManager::init(WindowManager window)
{
    //Textures
    textures[(int)TextureKey::Char_Front] = window.loadTexture("res/textures/char_front.png");
    textures[(int)TextureKey::Char_Front_2] = window.loadTexture("res/textures/char_front_2.png");
    textures[(int)TextureKey::Char_Back] = window.loadTexture("res/textures/char_back.png");
    textures[(int)TextureKey::Char_Back_2] = window.loadTexture("res/textures/char_back_2.png");
    textures[(int)TextureKey::Char_Right] = window.loadTexture("res/textures/char_right.png");
    textures[(int)TextureKey::Char_Right_2] = window.loadTexture("res/textures/char_right_2.png");
    textures[(int)TextureKey::Char_Left] = window.loadTexture("res/textures/char_left.png");
    textures[(int)TextureKey::Char_Left_2] = window.loadTexture("res/textures/char_left_2.png");

    textures[(int)TextureKey::Floor] = window.loadTexture("res/textures/floor.png");
    textures[(int)TextureKey::Wall] = window.loadTexture("res/textures/wall.png");

    //Sounds
    //sounds[(int)SoundKey::Buzz] = Mix_LoadWAV("res/sounds/buzz.wav");
    //sounds[(int)SoundKey::Correct] = Mix_LoadWAV("res/sounds/correct.wav");
    //sounds[(int)SoundKey::Buzz] = Mix_LoadWAV("res/sounds/buzz.wav");

    //Musics
    musics[(int)MusicKey::StartWindow] = Mix_LoadMUS("res/sounds/startwindow.mp3");

    //Fonts
    fonts[(int)FontKey::Font16] = TTF_OpenFont("res/fonts/cocogoose.ttf", 16);
    fonts[(int)FontKey::Font24] = TTF_OpenFont("res/fonts/cocogoose.ttf", 24);

    //Colors
    colors[(int)ColorKey::White] = { 255, 255, 255, 255 };
    colors[(int)ColorKey::Red] = { 255, 0, 0, 255 };
    colors[(int)ColorKey::Black] = { 0, 0, 0, 255 };
}

SDL_Texture* ResourceManager::getTexture(TextureKey textureKey)
{
    return textures[(int)textureKey];
}

Mix_Chunk* ResourceManager::getSound(SoundKey soundKey)
{
    return sounds[(int)soundKey];
}

Mix_Music* ResourceManager::getMusic(MusicKey musicKey)
{
    return musics[(int)musicKey];
}

TTF_Font* ResourceManager::getFont(FontKey fontKey)
{
    return fonts[(int)fontKey];
}

SDL_Color ResourceManager::getColor(ColorKey colorKey)
{
    return colors[(int)colorKey];
}

void ResourceManager::cleanUp()
{
    TTF_CloseFont(fonts[(int)FontKey::Font16]);
    TTF_CloseFont(fonts[(int)FontKey::Font24]);
}