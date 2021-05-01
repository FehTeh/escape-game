#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#include "math.h"

#include "menu.h"

MenuEvent Menu::update(WindowManager& window, ResourceManager& resource, SoundManager& sound, ControllerManager& controller)
{
    window.clear();

	window.renderTextCenter(0, sin(window.getTicks()/100) * 2 - 4, "Escape!!", resource.getFont(FontKey::Font24), resource.getColor(ColorKey::White));

    window.display();

    if(controller.getKeyPressed() == GameKey::A)
    {
        return MenuEvent::AType;
    }

    return MenuEvent::Running;
}