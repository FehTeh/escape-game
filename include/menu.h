#pragma once

#include "resourcemanager.h"
#include "windowmanager.h"
#include "controllermanager.h"
#include "soundmanager.h"

enum class MenuEvent
{
    None,
    AType,
    BType,
    Exit
};

class Menu {
public:
    MenuEvent update(WindowManager& window, ResourceManager& resource, SoundManager& sound, ControllerManager& controller);
private:
    void renderButton(WindowManager& window, ResourceManager& resource, int positionY, const char* text, bool active);
    MenuEvent moveSelected(GameKey key);

    MenuEvent selected = MenuEvent::AType;
    bool keyPressed = false;
};