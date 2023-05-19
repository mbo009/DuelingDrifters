#include "menu.hpp"

Menu::Menu(std::shared_ptr<sf::RenderWindow> &window) : window(window)
{
    // set FPS cap
    window->setFramerateLimit(60);
    loadAssets();
    car1.setScale(2, 2);
    car2.setScale(2, 2);
    car1.getCarObj().setMaxSpeed(9);
    car2.getCarObj().setMaxSpeed(9);
}

void Menu::makeGame()
{
    game = std::make_shared<Game>(window, font);
    gameActive = 1;
}

void Menu::loadAssets()
{
    buttons.push_back(Button(300, 250, "start"));
    buttons.push_back(Button(300, 600, "exit"));
    gameModeButtons.push_back(Button(300, 250, "normal"));
    gameModeButtons.push_back(Button(300, 600, "tag"));
    // gameModeButtons.push_back(Button(300, 600, "custom"));
    loadFont();
    loadMusic();
    loadMap();
    buttons[currentPosition].highlight();
    gameModeButtons[currentPosition].highlight();
    // REMAKE TO REFRESH TEXTURES FOR ALL BUTTONS IN FIRST FRAME
    buttons[currentPosition + 1].highlightOff();
}

void Menu::loadMusic()
{
    musicBuffer.loadFromFile(ASSET_PATHS_HPP::MUSIC_LIST[1]);
    music.setBuffer(musicBuffer);
    music.setVolume(20);
    music.setLoop(true);
    music.play();
}

void Menu::loadMap()
{
    mapTexture.loadFromFile(ASSET_PATHS_HPP::MAP_LIST[1]);
    map.setTexture(mapTexture, true);
}

void Menu::loadFont()
{
    // Load from file
    font.loadFromFile(ASSET_PATHS_HPP::STATS_FONT);
    // Create text
    mainMenuName = sf::Text("DuelingDrifters", font, NAME_FONT_SIZE);
    mainMenuName.setPosition(60, 70);
}

void Menu::makeCarMove(CarSprite &car, CarSprite &other, unsigned int range = 512)
{
    bool up = (car.getX() > range) && (car.getY() > range);
    bool down = (car.getX() < range) && (car.getY() < range);
    bool left = (car.getX() > range) && (car.getY() < range);
    bool right = (car.getX() < range) && (car.getY() > range);

    car.setNextAction(up, left, down, right, other);
    car.move();
}

void Menu::mainMenu()
{
    if (acceptPressed)
    {
        buttonPressed(buttons);
    }

    if ((upPressed || downPressed) && wait.getElapsedTime().asMilliseconds() > 100)
    {
        buttons[currentPosition].highlightOff();
        if (upPressed)
            currentPosition = (currentPosition - 1) % buttons.size();
        if (downPressed)
            currentPosition = (currentPosition + 1) % buttons.size();
        buttons[currentPosition].highlight();
        wait.restart();
    }

    makeCarMove(car1, car2);
    makeCarMove(car2, car1);

    window->clear(sf::Color::Black);
    window->draw(map);
    for (auto &button : buttons)
    {
        window->draw(button);
    }
    window->draw(mainMenuName);
    window->draw(car1);
    window->draw(car2);
    window->display();
}
#include <iostream>
#include <Windows.h>
void Menu::gameModeMenu()
{
    std::cout << "I'm in";
    if (acceptPressed)
    {
        buttonPressed(gameModeButtons);
    }

    if ((upPressed || downPressed) && wait.getElapsedTime().asMilliseconds() > 100)
    {
        gameModeButtons[currentPosition].highlightOff();
        if (upPressed)
            currentPosition = (currentPosition - 1) % gameModeButtons.size();
        if (downPressed)
            currentPosition = (currentPosition + 1) % gameModeButtons.size();
        gameModeButtons[currentPosition].highlight();
        wait.restart();
    }
    for (auto &button : gameModeButtons)
    {
        window->draw(button);
    }
    window->display();
    Sleep(1000);
    std::cout << "I'm out";
}

void Menu::pickCarMenu()
{
}

void Menu::settingsMenu()
{
}

void Menu::handleEvent(sf::Event &event)
{
    if (event.type == sf::Event::Closed)
        window->close();

    if (gameActive)
        game->handleEvent();
    else
    {
        upPressed = (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
                     sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
        downPressed = (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) ||
                      sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
        acceptPressed = (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
                         sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ||
                         sf::Keyboard::isKeyPressed(sf::Keyboard::E) ||
                         sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
                         sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
    }
}

void Menu::loadObjectsRound()
{
    if (!gameActive)
        mainMenu();
    else
        game->loadObjectsRound();
}

void Menu::buttonPressed(std::vector <Button> &buttonsList)
{
    if (buttonsList[currentPosition].getName() == "start")
    {
        gameModeMenu();
    }

    if (buttonsList[currentPosition].getName() == "exit")
    {
        window->close();
    }

    if (buttonsList[currentPosition].getName() == "normal")
    {
        makeGame();
        music.stop();
    }
}