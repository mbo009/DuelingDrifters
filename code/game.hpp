#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include <string>
#include "carSprite.hpp"
#include "assetPaths.hpp"

class Game
{
public:
    Game(std::shared_ptr<sf::RenderWindow> window);
    void loadAssets();
    void loadFont();
    void loadMap();
    void nextMap();
    void loadMusic();
    void nextMusic();
    void drawObjects();
    void loadObjectsRound();
    void handleEvent(sf::Event &event);
    void handleCarCollision();
    void countDown();
    bool carCrossedLine(const CarSprite &car);
    void checkPointCondition();
    void resetCarsPosition();
    void nextRound();

private:
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

    //PLAYGROUND BORDER
    const float BORDER_LEFT = 40;
    const float BORDER_RIGHT = 900;
    const float BORDER_TOP = 10;
    const float BORDER_BOTTOM = 900;

    sf::Font font;
 
    sf::View view;

    sf::Text timerText;
    sf::Text car1PointsText;
    sf::Text car2PointsText;

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

    sf::Clock clock;
    sf::Time roundTime;
    std::shared_ptr<sf::RenderWindow> window;
    CarSprite car1, car2;
};

#endif
