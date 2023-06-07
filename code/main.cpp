#include "menu.hpp"
#include <iostream>

int main()
{
    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1024, 1024), "Dueling Drifters");
    Menu menu = Menu(window);

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            menu.handleEvent(event);
        }

        menu.loadObjectsRound();
    }

    return 0;
}
