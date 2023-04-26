#include "carSprite.hpp"
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Racing game!");
    CarSprite car = CarSprite();
    CarSprite car2 = CarSprite();
    car.setScale(sf::Vector2f(3.0, 3.0));
    car.setPosition(400, 400);
    car2.setScale(sf::Vector2f(3.0, 3.0));
    car2.setPosition(200, 200);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            bool UpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
            bool LeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
            bool DownPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
            bool RightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

            car.updateCarDirection(event, UpPressed, LeftPressed, DownPressed, RightPressed);

            UpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
            LeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
            DownPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
            RightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

            car2.updateCarDirection(event, UpPressed, LeftPressed, DownPressed, RightPressed);
        }
        window.clear(sf::Color::Black);
        window.draw(car);
        window.draw(car2);
        window.display();
    }

    return 0;
}
