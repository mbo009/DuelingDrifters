#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Racing game!");
    sf::CircleShape shape(100.f);
    sf::Texture tCar;
    tCar.loadFromFile("img/downLeftRed.png");
    sf::Sprite car(tCar);
    car.setScale(sf::Vector2f(5.0, 5.0));
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        window.draw(car);
        window.display();
    }

    return 0;
}
