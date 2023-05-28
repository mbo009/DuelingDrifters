#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include "assetPaths.hpp"
#include <map>
#include <string>

// item variants to implement:
// 2x speed 3 seconds
// 0.5x speed enemy 3 seconds
// dash
// bomb

class Item : public sf::Sprite
{
public:
    Item(const std::string &name, float x, float y, sf::Time duration, bool useOnself = 1, float acc = -1, float maxSpeed = -1, bool reverse = 0, bool explode = 0, bool stun = 0, bool swap = 0);
    ~Item(){};
    std::string getName() const;
    float getX() const;
    void setX(float x);
    float getY() const;
    void setY(float y);
    void setPos(float x, float y);
    void refreshTexture();
    bool getExplode() const;
    bool getReverseSteering() const;
    float getMaxSpeed() const;
    float getAcceleration() const;
    bool getUseOnSelf() const;
    sf::Time getDuration() const;
    bool getStun() const;
    bool getSwap() const;
    sf::Texture &getTexture();

protected:
    std::map<std::string, std::string> itemTextures;
    sf::Texture texture;
    std::string name;
    float xPos;
    float yPos;
    sf::Time duration;
    bool useOnSelf;
    float changeAcc = -1;
    float changeMaxSpeed = -1;
    bool reverseSteering;
    bool explode;
    bool stun;
    bool swap;

    void createTextureMap();
};

#endif