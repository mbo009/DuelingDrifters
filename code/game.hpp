#ifndef GAME_H
#define GAME_H

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
    unsigned int songIndex;
    unsigned int mapIndex;
    std::shared_ptr<sf::RenderWindow> window;
    CarSprite car1, car2;
};

#endif
