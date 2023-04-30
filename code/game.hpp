#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Audio.hpp>
#include <memory>
#include "carSprite.hpp"

class Game
{
public:
    Game(std::shared_ptr<sf::RenderWindow> window);
    void handleEvent(sf::Event &event);
    void handleCarCollision();
    void loadMusic();
    void loadMap();
    void resetCarPosition();
    void checkPointCondition();
    bool carCrossedLine(const CarSprite &car);
    void loadObjectsRound();
    void loadFont();
    void nextSong();
    void countDown();
    void nextRound();
    void drawObjects();
    void nextMap();

private:
    const int VIEW_WIDTH = 1024;
    const int VIEW_HEIGHT = 1024;
    const float TIMER_X = 428.5;
    const float TIMER_Y = 50;
    const float CAR1_POINTS_X = 208;
    const float CAR1_POINTS_Y = 50;
    const float CAR2_POINTS_X = 778;
    const float CAR2_POINTS_Y = 50;
    const float STATS_FONT_SIZE = 50;

    //PLAYGROUND BORDER
    const float BORDER_LEFT = 40;
    const float BORDER_RIGHT = 900;
    const float BORDER_TOP = 10;
    const float BORDER_BOTTOM = 900;

    unsigned int songIndex;
    unsigned int mapIndex;
    
    sf::Sound startSound;
    sf::Sound crashSound;
    sf::Sound music;
    sf::Texture mapTexture;
    sf::SoundBuffer musicBuffer;
    sf::SoundBuffer startSoundBuffer;
    sf::SoundBuffer crashSoundBuffer;
    sf::Clock clock;
    sf::Time roundTime;
    sf::Font font;
    sf::Sprite map;
    sf::Text timerText;
    sf::Text car1PointsText;
    sf::Text car2PointsText;
    sf::View view;
    std::shared_ptr<sf::RenderWindow> window;
    CarSprite car1, car2;
};

#endif
