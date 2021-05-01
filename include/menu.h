#pragma once

#include "resourcemanager.h"
#include "windowmanager.h"
#include "controllermanager.h"
#include "soundmanager.h"

enum class MenuEvent
{
    Running = 1,
    AType,
    BType,
    Exit
};

class Menu {
public:
    MenuEvent update(WindowManager& window, ResourceManager& resource, SoundManager& sound, ControllerManager& controller);
private:
    MenuEvent selected = MenuEvent::AType;
};