#include "game.hpp"
#include <iostream>

std::vector<std::string> musicPath = {"battleTheme.ogg"};
std::vector<std::string> mapPath = {"spaceMap.png"};
std::string fontPath = "PixeloidMono.ttf";

Game::Game(std::shared_ptr<sf::RenderWindow> window) : window(window)
{
    songIndex = 0;
    mapIndex = 0;
    window->setFramerateLimit(60);
    loadMap();
    loadMusic();
    loadFont();
    view.setSize(1024, 1024);
    timerText = sf::Text("", font, 50);
    timerText.setPosition(428.5, 50.f);
    clock.restart();
    makeCar("Red");
    makeCar("Red");
}

void Game::makeCar(std::string color)
{
    if (cars.size() == 0)
    {
        CarSprite car = CarSprite(color, 80, 50, 2.5);
        cars.push_back(car);
    }

    else
    {
        CarSprite car = CarSprite(color, 850, 850, 2.5);
        cars.push_back(car);
    }
}

// TODO: To change
void Game::handleEvent(sf::Event &event)
{
    if (event.type == sf::Event::Closed)
        window->close();

    bool UpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool LeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool DownPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    bool RightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    if ((UpPressed || LeftPressed || DownPressed || RightPressed))
    {
        cars[0].setNextAction(UpPressed, LeftPressed, DownPressed, RightPressed);
        cars[0].updateDirectionTexture();
    }
    else
        cars[0].noMovementKeyPressed();

    UpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    LeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    DownPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    RightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    if ((UpPressed || LeftPressed || DownPressed || RightPressed))
    {
        cars[1].setNextAction(UpPressed, LeftPressed, DownPressed, RightPressed);
        cars[1].updateDirectionTexture();
    }
    else
        cars[1].noMovementKeyPressed();
}

void Game::nextSong()
{
    songIndex++;
    songIndex = songIndex % musicPath.size();
}

void Game::nextMap()
{
    mapIndex++;
    mapIndex = mapIndex % mapPath.size();
}

void Game::loadMusic()
{
    startSoundBuffer.loadFromFile("music/gameStart.ogg");
    startSound.setBuffer(startSoundBuffer);
    startSound.setVolume(60);
    startSound.play();

    musicBuffer.loadFromFile("music/" + musicPath[songIndex]); // to be changed
    music.setBuffer(musicBuffer);
    music.setLoop(true);
    music.setVolume(20);

    crashSoundBuffer.loadFromFile("music/crash.ogg");
    crashSound.setBuffer(crashSoundBuffer);
    crashSound.setVolume(60);

    music.play();
}

void Game::loadFont()
{
    font.loadFromFile("font/" + fontPath);
}

void Game::loadMap()
{
    mapTexture.loadFromFile("img/" + mapPath[mapIndex]);
    map.setTexture(mapTexture, true);
    map.setScale(sf::Vector2f(1.5, 1.5));
    map.setOrigin(190, 230);
}

void Game::handleCarCollision()
{
    sf::Vector2f relPosition = cars[1].getPosition() - cars[0].getPosition();
    sf::Vector2f relVelocity = cars[0].getVelocity() - cars[1].getVelocity();

    // Compute the dot product of the relative velocity and the relative position vectors
    float dotProduct = relVelocity.x * relPosition.x + relVelocity.y * relPosition.y;
    float dotProduct2 = cars[0].getVelocity().x * cars[1].getVelocity().x + cars[0].getVelocity().y * cars[1].getVelocity().y;

    if (dotProduct2 < 0)
    {
        // Cars are going in opposite directions
        sf::Vector2f temp = cars[0].getVelocity();
        cars[0].getPushed(cars[1].getVelocity().x, cars[1].getVelocity().y);
        cars[1].getPushed(temp.x, temp.y);
    }
    else // if (dotProduct2 > 0)
    {
        // not a head-on collision
        if (dotProduct >= 0)
        {
            // Cars[0] is driving towards cars[1]
            sf::Vector2f temp = cars[0].getVelocity();
            cars[0].push(cars[1].getVelocity().x, cars[1].getVelocity().y);
            cars[1].getPushed(temp.x, temp.y);
        }
        else if (dotProduct < 0)
        {
            // Cars[1] is driving towards cars[0]
            sf::Vector2f temp = cars[0].getVelocity();
            cars[0].getPushed(cars[1].getVelocity().x, cars[1].getVelocity().y);
            cars[1].push(temp.x, temp.y);
        }
    }
}

void Game::loadObjectsRound()
{
    sf::Time elapsed = clock.getElapsedTime();
    int min = static_cast<int>(elapsed.asSeconds()) / 60;
    int sec = static_cast<int>(elapsed.asSeconds()) % 60;
    timerText.setString((min < 10 ? "0" + std::to_string(min) : std::to_string(min)) + ":" + (sec < 10 ? "0" + std::to_string(sec) : std::to_string(sec)));
    for (auto &car : cars)
        car.move();
    if (cars[0].checkCollision(cars[1]))
    {
        crashSound.play();
        handleCarCollision();
    }
    view.setCenter((cars[0].getX() + cars[1].getX() + 3090) / 8, (cars[0].getY() + cars[1].getY() + 3000) / 8);
    window->setView(view);
    window->clear(sf::Color::Black);
    window->draw(map);
    window->draw(timerText);
    window->draw(cars[0]);
    window->draw(cars[1]);
    window->display();
}