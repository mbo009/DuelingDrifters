#include "item.hpp"

Item::Item(float x, float y,
           sf::Time duration, bool useOnSelf, float acc,
           float maxSpeed, bool reverse, bool explode,
           bool stun, bool swap) : xPos(x), yPos(y), duration(duration),
                                   useOnSelf(useOnSelf), changeAcc(acc),
                                   changeMaxSpeed(maxSpeed), reverseSteering(reverse),
                                   explode(explode), stun(stun), swap(swap)
{
    setPosition(x, y);
}

float Item::getX() const
{
    return xPos;
}

void Item::setX(float x)
{
    xPos = x;
}

float Item::getY() const
{
    return yPos;
}

void Item::setY(float y)
{
    yPos = y;
}

void Item::setPos(float x, float y)
{
    setX(x);
    setY(y);
    setPosition(x, y);
}

bool Item::getExplode() const
{
    return explode;
}

bool Item::getReverseSteering() const
{
    return reverseSteering;
}

float Item::getMaxSpeed() const
{
    return changeMaxSpeed;
}

float Item::getAcceleration() const
{
    return changeAcc;
}

bool Item::getUseOnSelf() const
{
    return useOnSelf;
}

sf::Time Item::getDuration() const
{
    return duration;
}

bool Item::getStun() const
{
    return stun;
}

bool Item::getSwap() const
{
    return swap;
}

sf::Texture &Item::getTexture()
{
    return texture;
}

SpeedUp::SpeedUp(float x, float y, sf::Time duration) : Item(x, y, duration)
{
    changeAcc = 1.5;
    changeMaxSpeed = 9;
    texture.loadFromFile(ASSET_PATHS_HPP::SPEED_ITM);
    setTexture(texture);
}

OpponentSlow::OpponentSlow(float x, float y, sf::Time duration) : Item(x, y, duration)
{
    useOnSelf = 0;
    changeAcc = 0.1;
    changeMaxSpeed = 3;
    texture.loadFromFile(ASSET_PATHS_HPP::OPP_SLOW_ITM);
    setTexture(texture);
}

Bomb::Bomb(float x, float y, sf::Time duration) : Item(x, y, duration)
{
    explode = 1;
    texture.loadFromFile(ASSET_PATHS_HPP::BOMB_ITM);
    setTexture(texture);
}

Dash::Dash(float x, float y, sf::Time duration) : Item(x, y, duration)
{
    changeAcc = 2;
    changeMaxSpeed = 20;
    texture.loadFromFile(ASSET_PATHS_HPP::DASH_ITM);
    setTexture(texture);
}

Reverse::Reverse(float x, float y, sf::Time duration) : Item(x, y, duration)
{
    useOnSelf = 0;
    reverseSteering = 1;
    texture.loadFromFile(ASSET_PATHS_HPP::REVERSE_ITM);
    setTexture(texture);
}

Stun::Stun(float x, float y, sf::Time duration) : Item(x, y, duration)
{
    useOnSelf = 0;
    stun = 1;
    texture.loadFromFile(ASSET_PATHS_HPP::STUN_ITM);
    setTexture(texture);
}

Swap::Swap(float x, float y, sf::Time duration) : Item(x, y, duration)
{
    useOnSelf = 0;
    swap = 1;
    texture.loadFromFile(ASSET_PATHS_HPP::SWAP_ITM);
    setTexture(texture);
}