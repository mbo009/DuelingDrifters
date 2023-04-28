#include "game.hpp"
#include <iostream>

// TODO
// * collisions
// * sound when collision
// * countdown before starting game
// * player point system
// * game stopping when car out of ring, point going to the other player
// * hp system for cars, hp meter in bottom corners of screen

int main()
{
    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1024, 1024), "CARBRAWL");
    // std::shared_ptr<CarSprite> car = std::make_shared<CarSprite>("Red", 100, 100, 1);
    Game game = Game(window);
    // TODO: Change this or f*ck up (Load default texture)
    // // the best option we found for now to preload car texture
    sf::Texture t;
    sf::Texture t1;
    t.loadFromFile("img/downRightRed.png");
    game.cars[0].setTexture(t);
    t1.loadFromFile("img/upLeftRed.png");
    game.cars[1].setTexture(t1);

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
