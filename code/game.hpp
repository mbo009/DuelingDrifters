/**
 * @file game.hpp
 * @author Binh Vuong Le Duc, Filip Ryniewicz, Cieśla Miłosz
 * @brief Class that represents the game, control properties and handle events while in game.
 * @date 2023-06-07
 * 
 */
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include <string>
#include <ctime>
#include <utility>
#include "carSprite.hpp"
#include "assetPaths.hpp"

/**
 * @brief Class that represents the game, control properties and handle events while in game.
 * 
 */
class Game
{
public:
    Game(std::shared_ptr<sf::RenderWindow> &window, sf::Font &font, unsigned int gameMode, unsigned int pointLimit = 1, sf::Time timeLimit = sf::seconds(5));
    // Load all assets
    void loadAssets();
    void loadFont();
    void loadMap();
    void loadSound();

    // Update game properties
    void resetCarsPosition();
    void nextRound(unsigned int winner);
    void spawnItem();
    void drawObjects(bool drawCar = 1, bool drawTimer = 1, bool drawPoints = 1, bool drawFlag = 1, bool drawItems = 1);

    // Game Properties Modifiers
    bool checkCarCollisions();
    void handleCarCollision();
    void handleItemAction();
    void useItem(CarSprite &car, Item &item);
    bool carCrossedLine(const CarSprite &car);
    void countDown(unsigned int winner);
    void printMsg(const std::string &msg, float x, float y);
    void endGame();
    void rotateCars(sf::Text textToDisplay);

    void duelEndCondition();
    void loadDuelRound();

    void checkBounceCondition();
    void checkFlag();
    void tagEndCondition();
    void loadTagRound();

    // Game Communication with Menu
    int handleEvent();
    void loadObjectsRound();

    bool isEnded();

private:
    std::shared_ptr<sf::RenderWindow> window;

    // Constants
    const int VIEW_WIDTH = 1024;
    const int VIEW_HEIGHT = 1024;
    const float TIMER_X = 428.5;
    const float TIMER_Y = 50;
    const float CAR1_POINTS_X = 208;
    const float CAR1_POINTS_Y = 50;
    const float CAR2_POINTS_X = 778;
    const float CAR2_POINTS_Y = 50;
    const float STATS_FONT_SIZE = 50;
    const float MAP_SCALE = 1.5;
    const float CAR_SCALE = 2.5;
    const float FLAG_SCALE = 1.75;
    const std::pair <int, int> CAR1_START_POS = {80, 50};
    const std::pair <int, int> CAR2_START_POS = {850, 850};
    const std::pair <int, int> FLAG_START_POS = {480, 470};


    // PLAYGROUND BORDERS
    const float BORDER_LEFT = 40;
    const float BORDER_RIGHT = 900;
    const float BORDER_TOP = 5;
    const float BORDER_BOTTOM = 900;

    sf::Font font;

    sf::View view;

    sf::Text timerText;
    sf::Text car1PointsText;
    sf::Text car2PointsText;
    sf::Text message;

    sf::Sprite map;
    sf::Texture mapTexture;

    sf::Sound startSound;
    sf::SoundBuffer startSoundBuffer;
    sf::Sound crashSound;
    sf::SoundBuffer crashSoundBuffer;
    sf::Sound music;
    sf::SoundBuffer musicBuffer;
    sf::Sound victorySound;
    sf::SoundBuffer victorySoundBuffer;

    unsigned int gameMode = 0; // 0 - duel, 1 - tag
    unsigned int pointLimit = 0;

    bool gameEnded = 0;

    sf::Clock clock;
    sf::Time roundTimeToSubtract;
    CarSprite car1, car2;

    int flagHolder = 0;
    Flag flag;
    sf::Time totalPlayTime;
    sf::Time timeLimit;
    sf::Time roundTimeLimit = sf::seconds(30);
    std::vector<Item> itemTypes;
    std::vector<std::pair<Item, sf::Clock>> itemsOnMap; // first is item, second is clock for item expiration
    sf::Clock sinceLastItemSpawn;

    unsigned int itemCap = 5;
};

#endif
