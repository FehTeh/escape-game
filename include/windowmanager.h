#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class WindowManager {
public:
	void create(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	
	void renderTexture(float p_x, float p_y, SDL_Texture* p_tex);
	void renderTextureFull(SDL_Texture* p_tex);
	
	void renderText(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);
	
	void renderTextCenter(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);
	void renderTextCenter(float p_x, float p_y, float p_w, float p_h, const char* p_text, TTF_Font* font, SDL_Color textColor);
	
	void renderRectangle(float p_x, float p_y, float p_w, float p_h, SDL_Color color);

	void fade(int percentage);

	int getWidth();
	int getHeight();
	int getTicks();

	void clear();
	void display();
	void cleanUp();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width;
	int height;
};