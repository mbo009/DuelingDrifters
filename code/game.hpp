#ifndef GAME_H
#define GAME_H
#include "carSprite.hpp"
#include <memory>

class Game
{
public:
    Game(std::shared_ptr<sf::RenderWindow> window);
    void makeCar(std::string color);
    void handleEvent(sf::Event &event);
    void loadMusic();
    void loadMap();
    void loadObjectsRound();
    void loadFont();
    void nextSong();
    void nextMap();
    sf::Sound music;
    std::vector<CarSprite> cars;

private:
    sf::Texture carTexture;
    sf::Texture mapTexture;
    sf::SoundBuffer musicBuffer;
    sf::Clock clock;
    sf::Time roundTime;
    sf::Font font;
    sf::Sprite map;
    sf::Text timerText;

    unsigned int songIndex;
    unsigned int mapIndex;
    std::shared_ptr<sf::RenderWindow> window;
    // std::shared_ptr<sf::Event> event;
};

#endif
