#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include "assetPaths.hpp"

// item variants to implement:
// 2x speed 3 seconds
// 0.5x speed enemy 3 seconds
// dash
// bomb

class Item : public sf::Sprite
{
public:
    Item(const std::string &name, float x, float y, sf::Time duration, bool useOnself = 1, float acc = -1, float maxSpeed = -1, bool reverse = 0, bool explode = 0);
    std::string getName() const;
    float getX() const;
    void setX(float x);
    float getY() const;
    void setY(float y);
    void setPos(float x, float y);
    void refreshTexture();
    bool getExplode();
    bool getReverseSteering();
    float getMaxSpeed();
    float getAcceleration();
    bool getUseOnSelf();

private:
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
};

#endif