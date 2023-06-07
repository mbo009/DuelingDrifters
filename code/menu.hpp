/**
 * @file menu.hpp
 * @author Binh Vuong Le Duc, Filip Ryniewicz, Cieśla Miłosz
 * @brief Class that represents the menu, contains all type of menus settings and functions before the game starts
 * @date 2023-06-07
 */
#ifndef MENU_H
#define MENU_H

#include <memory>
#include <utility>
#include "button.hpp"
#include "game.hpp"

/**
 * @brief Class that represents the menu, contains all type of menus settings and functions before the game starts
 *
 */
class Menu
{
public:
    Menu(std::shared_ptr<sf::RenderWindow> &window);
    void loadAssets();
    void loadFont();
    void loadMusic();
    void loadBackground();
    void preloadTextures();
    void updateButtonHighlights(std::vector<Button> &buttons);
    void updateTimeText();

    void drawButtons(std::vector<Button> buttons);
    void drawBackground(sf::Text textToDraw);
    void restartCameraPosition();
    void makeCarMove(CarSprite &car, CarSprite &other, unsigned int range);
    void moveCars();
    void mainMenu();
    void gameModeMenu();
    void gameSettings();

    void handleEvent(sf::Event &event);
    void loadObjectsRound();
    void buttonPressed(std::vector<Button> &buttonsList);
    bool areKeysPressed(std::vector<sf::Keyboard::Key> keys);

    void resetAfterRound();

private:
    std::shared_ptr<sf::RenderWindow> window;
    unsigned int currentPosition = 0;

    CarSprite car1 = CarSprite("red", 50, 50);
    CarSprite car2 = CarSprite("blue", 850, 850);

    const float NAME_FONT_SIZE = 90;
    const std::vector<sf::Keyboard::Key> UP_BUTTONS = {sf::Keyboard::W, sf::Keyboard::Up};
    const std::vector<sf::Keyboard::Key> DOWN_BUTTONS = {sf::Keyboard::S, sf::Keyboard::Down};
    const std::vector<sf::Keyboard::Key> LEFT_BUTTONS = {sf::Keyboard::A, sf::Keyboard::Left};
    const std::vector<sf::Keyboard::Key> RIGHT_BUTTONS = {sf::Keyboard::D, sf::Keyboard::Right};
    const std::vector<sf::Keyboard::Key> ACCEPT_BUTTONS = {sf::Keyboard::E, sf::Keyboard::Space, sf::Keyboard::Enter};

    const int TIME_BETWEEN_ACTIONS = 300;
    const int TIME_BETWEEN_ESC = 500;

    bool isGameActive = 0;
    bool isChoosingGameMode = 0;
    bool isSettingsMenu = 0;

    bool isUpPressed;
    bool isDownPressed;
    bool isLeftPressed;
    bool isRightPressed;
    bool isAcceptPressed;

    sf::Sprite background;

    sf::Font font;
    sf::Text mainMenuName;
    sf::Text gameModeMenuName;
    sf::Text settingsMenuName;
    sf::Text timeText;
    sf::Text pointsText;

    sf::Texture backgroundTexture;
    sf::Sound music;
    sf::SoundBuffer musicBuffer;
    std::vector<Button> buttons;
    std::vector<Button> gameModeButtons;
    std::shared_ptr<Game> game;
    sf::Clock wait;
    std::vector<Button> arrows;
    std::vector<Button> settingsButtons;

    sf::Time chosenTimeLimit = sf::seconds(300);
    unsigned int chosenPointsLimit = 10;
    unsigned int chosenGameMode;

    void preloadButtonTexture(std::vector<Button> &buttons);
};

#endif