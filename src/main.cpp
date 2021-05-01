#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <stdlib.h>
#include <string.h>

#include "windowmanager.h"
#include "soundmanager.h"
#include "resourcemanager.h"
#include "controllermanager.h"

#include "menu.h"
#include "game.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

WindowManager window;
SoundManager sound;
ResourceManager resources;
ControllerManager controller;

Menu menu;
Game game;

bool running = true;
bool inMenu = true;

void gameLoop()
{
	if(!controller.checkKey())
	{
		running = false;
	}
	else
	{
		if (inMenu)
		{
			MenuEvent event = menu.update(window, resources, sound, controller);

			if(event == MenuEvent::AType)
			{
				inMenu = false;
				game.generate(50);
			}
		}
		else 
		{
			GameEvent event = game.update(window, resources, sound, controller);

			if(event == GameEvent::LevelUp)
			{
				game.generate(50);
			}
		}
	}
}

int main(int argc, char* args[])
{
	window.create("Escape", SCREEN_WIDTH, SCREEN_HEIGHT);
	srand((unsigned)time(0));

	sound.init();
	resources.init(window);

	while (running) 
	{
    	gameLoop();
    	SDL_Delay(16);
	}

	resources.cleanUp();
	window.cleanUp();
	
	return 0;
}