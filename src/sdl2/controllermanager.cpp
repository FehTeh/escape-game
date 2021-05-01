#include "controllermanager.h"

bool ControllerManager::checkKey()
{
	SDL_Event event;
 	while (SDL_PollEvent(&event)) 
 	{
    	switch (event.type) {
			case SDL_QUIT: 
			{
				return false;
			}
			case SDL_KEYUP:
			{
				keyPressed = GameKey::None;
				break;
			}
			case SDL_KEYDOWN:
			{
				if(keyPressed == GameKey::None)
				{
					keyPressed = mapKeyboardToGameKey(event.button.button);
				}
				break;
			}
    	}
	}
	return true;
}

GameKey ControllerManager::getKeyPressed()
{
	return keyPressed;
}

/* Private */
GameKey ControllerManager::mapKeyboardToGameKey(int keyCode)
{
	switch(keyCode)
	{
		case 82:
			return GameKey::Up;
		case 81:
			return GameKey::Down;
		case 80:
			return GameKey::Left;
		case 79:
			return GameKey::Right;
		case 4:
			return GameKey::A;
		case 22:
			return GameKey::B;
		default:
			return GameKey::None;
	}
}