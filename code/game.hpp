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

class Game
{
public:
    Game(std::shared_ptr<sf::RenderWindow> &window, sf::Font &font, unsigned int gameMode);
    // Load all assets
    void loadAssets();
    void loadFont();
    void loadMap();
    void loadSound();
    // Update game properties
    void nextMap();
    void nextMusic();
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

    void duelEndCondition();
    void loadDuelRound();

    void checkBounceCondition();
    void checkFlag();
    void tagEndCondition();
    void loadTagRound();

    // Game Communication with Menu
    int handleEvent();
    void loadObjectsRound();

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

    unsigned int musicIndex = 0;
    unsigned int mapIndex = 0;
    unsigned int gameMode = 0; // 0 - duel, 1 - tag

    sf::Clock clock;
    sf::Time roundTimeToSubtract;
    CarSprite car1, car2;

    int flagHolder = 0;
    Flag flag;
    sf::Time totalPlayTime;
    sf::Time timeLimit;
    std::vector<Item> itemTypes;
    std::vector<std::pair<Item, sf::Clock>> itemsOnMap; // first is item, second is clock for item expiration
    sf::Clock sinceLastItemSpawn;

    unsigned int itemCap = 5;
};

#endif
