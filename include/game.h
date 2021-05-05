#pragma once

#include "resourcemanager.h"
#include "windowmanager.h"
#include "controllermanager.h"
#include "soundmanager.h"

#include "player.h"

enum class GameEvent
{
    Running = 1,
    Stopped
};

class Game {
public:
    GameEvent update(WindowManager& window, ResourceManager& resource, SoundManager& sound, ControllerManager& controller);
	void start();
private:
    void renderLevel(WindowManager& window, ResourceManager& resource);
    void renderStatusBar(WindowManager& window, ResourceManager& resource);
    void showmaze();
    void generate(int p_s);
    void move(PlayerMovement movement);
    bool canMove(PlayerMovement movement);
    PlayerMovement mapKeyToMovement(GameKey key);

    Player player;

    int moveX;
    int moveY;

    int interval = 600;

    int size;
    char* map;

    bool loading;

    ColorKey background = ColorKey::Green;
    bool backgroundPressed;
};