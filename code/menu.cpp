#include "menu.hpp"
#include <iostream>

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

void Menu::loadAssets()
{
    buttons.push_back(Button(300, 250, "start"));
    buttons.push_back(Button(300, 600, "exit"));

    gameModeButtons.push_back(Button(100, 300, "duel"));
    gameModeButtons.push_back(Button(500, 300, "flag"));

    arrows.push_back(Button(95, 340, "arrowLeft", sf::Vector2f(4, 4)));
    arrows.push_back(Button(795, 340, "arrowRight", sf::Vector2f(4, 4)));
    arrows.push_back(Button(95, 590, "arrowLeft", sf::Vector2f(4, 4)));
    arrows.push_back(Button(795, 590, "arrowRight", sf::Vector2f(4, 4)));

    settingsButtons.push_back(Button(107, 100, "longTime", sf::Vector2f(4, 3)));
    settingsButtons.push_back(Button(107, 350, "longPoints", sf::Vector2f(4, 3)));
    settingsButtons.push_back(Button(300, 680, "start"));

    loadFont();
    loadMusic();
    loadMap();

    preloadTextures();
}

void Menu::preloadButtonTexture(std::vector<Button> &buttons)
{
    for (auto &button : buttons)
    {
        button.highlight(0);
    }
    buttons[currentPosition].highlight(1);
}

void Menu::preloadTextures()
{
    preloadButtonTexture(buttons);
    preloadButtonTexture(gameModeButtons);
    preloadButtonTexture(settingsButtons);
    preloadButtonTexture(arrows);
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

void Menu::updateTimeText()
{
    int min = static_cast<int>(chosenTimeLimit.asSeconds()) / 60;
    int sec = static_cast<int>(chosenTimeLimit.asSeconds()) % 60;
    timeText.setString((min < 10 ? "0" + std::to_string(min) : std::to_string(min)) + ":" + (sec < 10 ? "0" + std::to_string(sec) : std::to_string(sec)));
}

void Menu::loadFont()
{
    // Load from file
    font.loadFromFile(ASSET_PATHS_HPP::POM_FONT);

    // Create text
    mainMenuName = sf::Text("Dueling Drifters", font, NAME_FONT_SIZE);
    mainMenuName.setPosition(60, 70);
    gameModeMenuName = sf::Text("Choose Game Mode", font, NAME_FONT_SIZE);
    gameModeMenuName.setPosition(60, 70);
    settingsMenuName = sf::Text("Choose Game Settings", font, NAME_FONT_SIZE - 20);
    settingsMenuName.setPosition(60, 70);

    timeText = sf::Text("", font, NAME_FONT_SIZE);
    updateTimeText();
    timeText.setPosition(365, 345);
    pointsText = sf::Text(std::to_string(chosenPointsLimit), font, NAME_FONT_SIZE);
    pointsText.setPosition(445, 593);
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

void Menu::updateButtonHighlights(std::vector<Button> &buttons)
{
    if ((isUpPressed || isDownPressed) && wait.getElapsedTime().asMilliseconds() > TIME_BETWEEN_ACTIONS)
    {
        buttons[currentPosition].highlight(0);
        if (isUpPressed)
            currentPosition = (currentPosition - 1) % buttons.size();
        if (isDownPressed)
            currentPosition = (currentPosition + 1) % buttons.size();
        buttons[currentPosition].highlight(1);
        wait.restart();
    }
}

void Menu::mainMenu()
{
    if (isAcceptPressed)
        buttonPressed(buttons);
    updateButtonHighlights(buttons);
    moveCars();

    drawBackground(mainMenuName);
    drawButtons(buttons);

    window->display();
}

void Menu::gameModeMenu()
{
    if (isAcceptPressed)
        buttonPressed(gameModeButtons);

    isUpPressed = isLeftPressed || isUpPressed;
    isDownPressed = isRightPressed || isDownPressed;

    updateButtonHighlights(gameModeButtons);

    moveCars();

    drawBackground(gameModeMenuName);
    drawButtons(gameModeButtons);

    window->display();
}

void Menu::drawBackground(sf::Text textToDraw)
{
    window->clear(sf::Color::Black);
    window->draw(map);
    window->draw(textToDraw);
    window->draw(car1);
    window->draw(car2);
}

void Menu::gameSettings()
{
    if (isLeftPressed || isRightPressed || isAcceptPressed)
        buttonPressed(settingsButtons);

    updateButtonHighlights(settingsButtons);

    moveCars();
    drawBackground(settingsMenuName);
    drawButtons(settingsButtons);
    drawButtons(arrows);
    window->draw(timeText);
    window->draw(pointsText);
    window->display();
}

void Menu::moveCars()
{
    makeCarMove(car1, car2);
    makeCarMove(car2, car1);
}

void Menu::drawButtons(std::vector<Button> buttons)
{
    for (auto &button : buttons)
    {
        window->draw(button);
    }
}

void Menu::handleEvent(sf::Event &event)
{
    if (event.type == sf::Event::Closed)
        window->close();

    if (!isGameActive)
    {
        if (event.key.code == sf::Keyboard::Escape && wait.getElapsedTime().asMilliseconds() > TIME_BETWEEN_ESC)
        {
            currentPosition = 0;

            if (isSettingsMenu)
            {
                isChoosingGameMode = 1;
                isSettingsMenu = 0;
            }

            if (isChoosingGameMode)
                isChoosingGameMode = 0;

            else
                window->close();
        }

        isUpPressed = areKeysPressed(UP_BUTTONS);
        isDownPressed = areKeysPressed(DOWN_BUTTONS);
        isAcceptPressed = areKeysPressed(ACCEPT_BUTTONS);
        isLeftPressed = areKeysPressed(LEFT_BUTTONS);
        isRightPressed = areKeysPressed(RIGHT_BUTTONS);
    }

    else
    {
        isGameActive = !game->isEnded();
        if (!isGameActive)
        {
            resetAfterRound();
        }
        else
            game->handleEvent();
    }
}

bool Menu::areKeysPressed(std::vector<sf::Keyboard::Key> keys)
{
    bool output = False;
    for (auto &key : keys)
        output = output || sf::Keyboard::isKeyPressed(key);
    return output;
}

void Menu::restartCameraPosition()
{
    sf::View view;
    view.setCenter(512, 512);
    window->setView(view);
}

void Menu::resetAfterRound()
{
    wait.restart();
    restartCameraPosition();
    buttons[currentPosition].highlight(0);
    gameModeButtons[currentPosition].highlight(0);
    currentPosition = 0;
    preloadTextures();
    music.play();
}

void Menu::loadObjectsRound()
{
    if (!isGameActive)
    {
        if (isChoosingGameMode)
            gameModeMenu();

        else if (isSettingsMenu)
            gameSettings();

        else
            mainMenu();
    }

    else
    {
        isGameActive = !game->isEnded();
        if (isGameActive)
            game->loadObjectsRound();
        else
            resetAfterRound();
    }
}

void Menu::buttonPressed(std::vector<Button> &buttonsList)
{
    if (buttonsList[currentPosition].getName() == "start")
    {
        if (isSettingsMenu)
        {
            game = std::make_shared<Game>(window, font, chosenGameMode, chosenPointsLimit, chosenTimeLimit);
            isSettingsMenu = 0;
            isGameActive = 1;
            music.stop();
        }

        else
        {
            isAcceptPressed = 0;
            isChoosingGameMode = 1;
            gameModeMenu();
        }
    }

    else if (buttonsList[currentPosition].getName() == "exit")
    {
        window->close();
    }

    else if (buttonsList[currentPosition].getName() == "duel")
    {
        chosenGameMode = 0;
        isChoosingGameMode = 0;
        isSettingsMenu = 1;
    }

    else if (buttonsList[currentPosition].getName() == "flag")
    {
        chosenGameMode = 1;
        isChoosingGameMode = 0;
        isSettingsMenu = 1;
    }

    else if (buttonsList[currentPosition].getName() == "longTime")
    {
        if (wait.getElapsedTime().asMilliseconds() > 300)
        {
            if (isLeftPressed && chosenTimeLimit.asSeconds() > 30)
                chosenTimeLimit -= sf::seconds(30);

            else if (isRightPressed && chosenTimeLimit.asSeconds() < 3600)
                chosenTimeLimit += sf::seconds(30);

            updateTimeText();
            wait.restart();
        }
    }

    else if (buttonsList[currentPosition].getName() == "longPoints")
    {
        if (wait.getElapsedTime().asMilliseconds() > 100)
        {
            if (isLeftPressed && chosenPointsLimit > 1)
                chosenPointsLimit--;

            else if (isRightPressed && chosenPointsLimit < 999)
                chosenPointsLimit++;
            pointsText.setString(std::to_string(chosenPointsLimit));

            wait.restart();
        }
    }

    isAcceptPressed = 0;
}