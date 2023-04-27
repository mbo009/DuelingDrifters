#include "carSprite.hpp"
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "CARBRAWL");
    window.setFramerateLimit(60);
    bool UpPressed, LeftPressed, DownPressed, RightPressed;
    CarSprite car = CarSprite("Red", 300, 300);
    CarSprite car2 = CarSprite("Red", 200, 200);
    sf::Texture mapTexture;
    sf::SoundBuffer musicBuffer;
    sf::Sound music;
    musicBuffer.loadFromFile("music/battleTheme.ogg");
    music.setBuffer(musicBuffer);
    music.setLoop(true);
    mapTexture.loadFromFile("img/spaceMap.png");
    sf::Sprite map(mapTexture);
    map.setScale(sf::Vector2f(1.5, 1.5));
    map.setOrigin(190, 230);
    car.setScale(sf::Vector2f(2.5, 2.5));
    car2.setScale(sf::Vector2f(2.5, 2.5));
    music.play();
    music.setVolume(20);
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
        }
        car.move();
        car2.move();
        window.clear(sf::Color::Black);
        window.draw(map);
        window.draw(car);
        window.draw(car2);
        window.display();
    }

    return 0;
}
