#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "windowmanager.h"

int WindowManager::getWidth()
{
	return width;
}

int WindowManager::getHeight()
{
	return height;
}

void WindowManager::create(const char* p_title, int p_w, int p_h)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;

	width = p_w;
	height = p_h;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}


SDL_Texture* WindowManager::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL; 
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}

void WindowManager::clear()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void WindowManager::renderTexture(float p_x, float p_y, SDL_Texture* p_tex)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h); 

	SDL_Rect dst;
	dst.x = p_x;
	dst.y = p_y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

void WindowManager::renderTextureFull(SDL_Texture* p_tex)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h); 

	SDL_Rect dst;
	dst.x = 0;
	dst.y = 0;
	dst.w = width;
	dst.h = height;

	SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

void WindowManager::renderText(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended( font, p_text, textColor);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = surfaceMessage->w;
	src.h = surfaceMessage->h; 

	SDL_Rect dst;
	dst.x = p_x;
	dst.y = p_y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, message, &src, &dst);
	SDL_FreeSurface(surfaceMessage);
}

void WindowManager::renderTextCenter(float p_x, float p_y, float p_w, float p_h, const char* p_text, TTF_Font* font, SDL_Color textColor)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended( font, p_text, textColor);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = surfaceMessage->w;
	src.h = surfaceMessage->h; 

	SDL_Rect dst;
	dst.x = p_w/2 - src.w/2 + p_x;
	dst.y = p_h/2 - src.h/2 + p_y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, message, &src, &dst);
	SDL_FreeSurface(surfaceMessage);
}

void WindowManager::renderTextCenter(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
{
	renderTextCenter(p_x, p_y, width, height, p_text, font, textColor);
}

void WindowManager::renderRectangle(float p_x, float p_y, float p_w, float p_h, SDL_Color color)
{
    SDL_Rect r;
    r.x = p_x;
    r.y = p_y;
    r.w = p_w;
    r.h = p_h;

    SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a);

	SDL_RenderFillRect( renderer, &r );
}

void WindowManager::fade(int percentage)
{
    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.w = width;
    r.h = height;

	int opacity = 255 * percentage / 100;

    SDL_SetRenderDrawColor( renderer, 0, 0, 0, opacity);

	SDL_RenderFillRect( renderer, &r );
}

int WindowManager::getTicks()
{
	return SDL_GetTicks();
}

void WindowManager::display()
{
	SDL_RenderPresent(renderer);
}

void WindowManager::cleanUp()
{
	SDL_DestroyWindow(window);

	TTF_Quit();
	SDL_Quit();
}