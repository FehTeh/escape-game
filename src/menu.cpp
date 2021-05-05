#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#include "math.h"

#include "menu.h"

MenuEvent Menu::update(WindowManager& window, ResourceManager& resource, SoundManager& sound, ControllerManager& controller)
{
    window.clear();
    
    int offsetX = window.getWidth() / 2;

    window.renderTextCenter(offsetX - 50, 100, 100, 30, "ESCAPE!! working title", resource.getFont(FontKey::Font24), resource.getColor(ColorKey::Red));

    renderButton(window, resource, 155, "A-Type", selected == MenuEvent::AType);
    renderButton(window, resource, 115, "B-Type", selected == MenuEvent::BType);
    renderButton(window, resource, 75, "Exit", selected == MenuEvent::Exit);

    window.display();

    switch(controller.getKeyPressed())
    {
        case GameKey::Up:
        case GameKey::Down:
            if(!keyPressed)
            {
                keyPressed = true;
                sound.playSound(resource.getSound(SoundKey::MenuSelection));
                selected = moveSelected(controller.getKeyPressed());
            }
            break;
        case GameKey::A:
            sound.playSound(resource.getSound(SoundKey::MenuSelected));
            return selected;
        case GameKey::None:
            keyPressed = false;
        default:
            break;
    }

    return MenuEvent::None;
}

void Menu::renderButton(WindowManager& window, ResourceManager& resource, int positionY, const char* text, bool active)
{
    int offsetX = window.getWidth() / 2;
    int offsetY = window.getHeight();

    ColorKey textColor = active ? ColorKey::Black : ColorKey::White;
    ColorKey buttonColor = active ? ColorKey::White : ColorKey::Black;

    window.renderRectangle(offsetX - 52, offsetY - positionY - 2, 104, 34, resource.getColor(ColorKey::White));
    window.renderRectangle(offsetX - 50, offsetY - positionY, 100, 30, resource.getColor(buttonColor));
    window.renderTextCenter(offsetX - 50, offsetY - positionY, 100, 30, text, resource.getFont(FontKey::Font16), resource.getColor(textColor));
}

MenuEvent Menu::moveSelected(GameKey key)
{
    if(key == GameKey::Up)
    {
        if(selected == MenuEvent::Exit)
            return MenuEvent::BType;
        else
            return MenuEvent::AType;
    }

    if(key == GameKey::Down)
    {
        if(selected == MenuEvent::AType)
            return MenuEvent::BType;
        else
            return MenuEvent::Exit;
    }

    return MenuEvent::None;
}