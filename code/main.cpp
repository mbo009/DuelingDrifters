#include "carSprite.hpp"
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Racing game!");
    std::vector<std::string> files = {"img/upRed.png", "img/upRightRed.png", "img/rightRed.png", "img/downRed.png",
                                      "img/downLeftRed.png", "img/leftRed.png", "img/upLeftRed.png"};
    std::vector<sf::Texture> tCar;
    sf::Texture test;
    for (const auto &t : files)
    {
        test.loadFromFile(t);
        tCar.push_back(test);
    }
    int i = 0;
    sf::Sprite car(tCar[i]);
    car.setScale(sf::Vector2f(5.0, 5.0));
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
            {
                i++;
                car.setTexture(tCar[i % 7]);
            }
        }
        window.clear(sf::Color::Black);
        window.draw(car);
        window.display();
    }

    return 0;
}
