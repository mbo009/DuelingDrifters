#include "carSprite.hpp"
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Racing game!");
    window.setFramerateLimit(60);

    CarSprite car = CarSprite("Red", 300, 300);
    CarSprite car2 = CarSprite("Red", 200, 200);
    car.setScale(sf::Vector2f(3.0, 3.0));
    car2.setScale(sf::Vector2f(3.0, 3.0));

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
            if ((UpPressed || LeftPressed || DownPressed || RightPressed))
            {
                car.setNextAction(UpPressed, LeftPressed, DownPressed, RightPressed);
                car.updateDirectionTexture();
            }
            else
                car.noMovementKeyPressed();
            car.move();

            UpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
            LeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
            DownPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
            RightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
            if ((UpPressed || LeftPressed || DownPressed || RightPressed))
            {
                car2.setNextAction(UpPressed, LeftPressed, DownPressed, RightPressed);
                car2.updateDirectionTexture();
            }
            else
                car2.noMovementKeyPressed();
            car2.move();
        }

        window.clear(sf::Color::Black);
        window.draw(car);
        window.draw(car2);
        window.display();
    }

    return 0;
}
