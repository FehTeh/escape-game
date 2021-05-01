#pragma once

#include "resourcemanager.h"
#include "windowmanager.h"
#include "controllermanager.h"
#include "soundmanager.h"

#include "player.h"

enum class GameEvent
{
    Running = 1,
    Timeout,
    LevelUp
};

class Game {
public:
    GameEvent update(WindowManager& window, ResourceManager& resource, SoundManager& sound, ControllerManager& controller);
	void generate(int p_s);
private:
    void showmaze();
    void move(PlayerMovement movement);
    bool canMove(PlayerMovement movement);
    PlayerMovement mapKeyToMovement(GameKey key);

    Player player;

    int moveX;
    int moveY;

    int interval = 0;

    int size;
    char* map;
};