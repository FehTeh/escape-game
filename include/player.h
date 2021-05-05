#pragma once

#include "resourcemanager.h"

enum class PlayerMovement
{
    StandBy = 1,
    Up,
    Down,
    Left,
    Right
};

class Player {
public:
    PlayerMovement getMovement();
    void setMovement(PlayerMovement direction);
    TextureKey getTexture(int interval);
private:
    PlayerMovement movement = PlayerMovement::StandBy;
    PlayerMovement prevMovement = PlayerMovement::StandBy;
};