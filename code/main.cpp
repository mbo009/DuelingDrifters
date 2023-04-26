#include "carSprite.hpp"
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Racing game!");
    CarSprite car = CarSprite();
    car.setScale(sf::Vector2f(5.0, 5.0));
    // car.setPosition(sf::Vector2f(400, 400));
    car.setPosition(400, 400);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            bool WPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
            bool APressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
            bool SPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
            bool DPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

            car.updateCarDirection(event, WPressed, APressed, SPressed, DPressed);
        }
        window.clear(sf::Color::Black);
        window.draw(car);
        window.display();
    }

    return 0;
}
