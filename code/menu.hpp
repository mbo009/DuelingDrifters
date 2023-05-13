#ifndef MENU_H
#define MENU_H

#include "button.hpp"
#include <memory>

class Menu
{
public:
    Menu(std::shared_ptr<sf::RenderWindow> &window);

private:
    std::shared_ptr<sf::RenderWindow> window;
    std::vector<Button> buttons;
};

#endif