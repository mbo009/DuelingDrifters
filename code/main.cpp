#include "game.hpp"
#include <iostream>

// TODO
// * hp system for cars, hp meter in bottom corners of screen

int main()
{
    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1024, 1024), "CARBRAWL");
    Game game = Game(window);

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            game.handleEvent(event);
        }
        game.loadObjectsRound();
    }

    return 0;
}
