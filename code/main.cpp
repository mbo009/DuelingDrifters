#include "carSprite.hpp"
#include <vector>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "CARBRAWL");
    window.setFramerateLimit(60);

    sf::Texture mapTexture;
    mapTexture.loadFromFile("img/spaceMap.png");
    sf::Sprite map(mapTexture);
    map.setScale(sf::Vector2f(1.5, 1.5));
    map.setOrigin(190, 230);

    sf::SoundBuffer musicBuffer;
    musicBuffer.loadFromFile("music/battleTheme.ogg");
    sf::Sound music;
    music.setBuffer(musicBuffer);
    music.setLoop(true);
    music.play();
    music.setVolume(20);

    sf::Font font;
    font.loadFromFile("font/PixeloidMono.ttf");
    sf::Text timerText("", font, 50);
    timerText.setPosition(450.f, 50.f);
    sf::Clock clock;
    clock.restart();

    CarSprite car = CarSprite("Red", 300, 300);
    car.setScale(sf::Vector2f(2.5, 2.5));
    CarSprite car2 = CarSprite("Red", 200, 200);
    car2.setScale(sf::Vector2f(2.5, 2.5));

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
        sf::Time elapsed = clock.getElapsedTime();
        int min = static_cast<int>(elapsed.asSeconds()) / 60;
        int sec = static_cast<int>(elapsed.asSeconds()) % 60;
        timerText.setString((min < 10 ? "0" + std::to_string(min) : std::to_string(min)) + ":" + (sec < 10 ? "0" + std::to_string(sec) : std::to_string(sec)));

        car.move();
        car2.move();
        window.clear(sf::Color::Black);
        window.draw(map);
        window.draw(car);
        window.draw(car2);
        window.draw(timerText);
        window.display();
    }

    return 0;
}
