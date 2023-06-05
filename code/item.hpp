/**
 * @file item.hpp
 * @author Binh Vuong Le Duc, Filip Ryniewicz, Cieśla Miłosz
 * @brief Class for the items and its inherited classes
 * @date 2023-06-04
 * 
 */
#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include "assetPaths.hpp"
#include <map>
#include <string>

class Item : public sf::Sprite
{
public:
    Item(float x, float y, sf::Time duration, bool useOnself = 1, float acc = -1, float maxSpeed = -1, bool reverse = 0, bool explode = 0, bool stun = 0, bool swap = 0);
    ~Item(){};
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
    sf::Texture texture;
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
};

class SpeedUp : public Item
{
public:
    SpeedUp(float x = 1000, float y = 1000, sf::Time duration = sf::seconds(3));
    ~SpeedUp(){};
};

class OpponentSlow : public Item
{
public:
    OpponentSlow(float x = 1000, float y = 1000, sf::Time duration = sf::seconds(2));
    ~OpponentSlow(){};
};

class Bomb : public Item
{
public:
    Bomb(float x = 1000, float y = 1000, sf::Time duration = sf::seconds(0));
    ~Bomb(){};
};

class Dash : public Item
{
public:
    Dash(float x = 1000, float y = 1000, sf::Time duration = sf::milliseconds(100));
    ~Dash(){};
};

class Reverse : public Item
{
public:
    Reverse(float x = 1000, float y = 1000, sf::Time duration = sf::seconds(1));
    ~Reverse(){};
};

class Stun : public Item
{
public:
    Stun(float x = 1000, float y = 1000, sf::Time duration = sf::seconds(0));
    ~Stun(){};
};

class Swap : public Item
{
public:
    Swap(float x = 1000, float y = 1000, sf::Time duration = sf::seconds(0));
    ~Swap(){};
};

class Flag : public Item
{
public:
    Flag(float x = 1000, float y = 1000, sf::Time duration = sf::seconds(0));
    ~Flag(){};
};

#endif