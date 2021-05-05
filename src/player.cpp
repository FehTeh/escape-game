#include <string>
#include <iostream>

#include "player.h"

PlayerMovement Player::getMovement()
{
    return movement;
}

void Player::setMovement(PlayerMovement direction)
{
    if(movement != PlayerMovement::StandBy)
    {
        prevMovement = movement;
    }
    
    movement = direction;
}

TextureKey Player::getTexture(int interval)
{
    PlayerMovement toRender = movement;

    if(movement == PlayerMovement::StandBy)
    {
        toRender = prevMovement;
        interval = 0;
    }

    switch(toRender)
    {
        case PlayerMovement::Right:
            return interval % 2 == 0 ? TextureKey::Char_Right_2 : TextureKey::Char_Right;
        case PlayerMovement::Left:
            return interval % 2 == 0 ? TextureKey::Char_Left_2 : TextureKey::Char_Left;
        case PlayerMovement::Up:
            return interval % 2 == 0 ? TextureKey::Char_Back_2 : TextureKey::Char_Back;
        default:
            return interval % 2 == 0 ? TextureKey::Char_Front : 
                   interval % 3 == 0 ? TextureKey::Char_Front_3 : 
                                       TextureKey::Char_Front_2;
    }
}