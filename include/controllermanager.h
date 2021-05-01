#pragma once

#include <SDL2/SDL.h>
#include <cstdio>
#include <cstring>

enum class GameKey
{
    None,
    Up,
    Down,
    Left,
    Right,
    A,
    B
};

class ControllerManager {
public:
    bool checkKey();
    GameKey getKeyPressed();
private:
    GameKey mapKeyboardToGameKey(int keyCode);
    GameKey keyPressed = GameKey::None;
};