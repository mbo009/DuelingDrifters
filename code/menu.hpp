#ifndef MENU_H
#define MENU_H

#include "button.hpp"
#include "game.hpp"
#include <memory>

class Menu
{
public:
    Menu(std::shared_ptr<sf::RenderWindow> &window);
    void makeGame();
    void loadAssets();
    void loadFont();
    void loadMusic();
    void loadMap();
    void mainMenu();
    void pickCarMenu();
    void settingsMenu();
    void handleEvent(sf::Event &event);
    void loadObjectsRound();
    void makeCarMove(CarSprite &car, CarSprite &other, unsigned int range);
    void buttonPressed();

private:
    std::shared_ptr<sf::RenderWindow> window;
    unsigned int currentPosition = 0;

    CarSprite car1 = CarSprite("red", 50, 50);
    CarSprite car2 = CarSprite("blue", 850, 850);

    const float NAME_FONT_SIZE = 90;

    bool gameActive = 0;
    bool upPressed;
    bool downPressed;
    bool acceptPressed;

    sf::Sprite map;
    sf::Font font;
    sf::Text mainMenuName;
    sf::Texture mapTexture;
    sf::Sound music;
    sf::SoundBuffer musicBuffer;
    std::vector<Button> buttons;
    std::shared_ptr<Game> game;
    sf::Clock wait;
};

#endif