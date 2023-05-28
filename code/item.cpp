#include "item.hpp"

void Item::createTextureMap()
{
    itemTextures["SpeedUp"] = ASSET_PATHS_HPP::SPEED_ITM;
    itemTextures["OpponentSlow"] = ASSET_PATHS_HPP::OPP_SLOW_ITM;
    itemTextures["Bomb"] = ASSET_PATHS_HPP::BOMB_ITM;
    itemTextures["Dash"] = ASSET_PATHS_HPP::DASH_ITM;
    itemTextures["Reverse"] = ASSET_PATHS_HPP::REVERSE_ITM;
    itemTextures["Stun"] = ASSET_PATHS_HPP::STUN_ITM;
    itemTextures["Swap"] = ASSET_PATHS_HPP::SWAP_ITM;
}

Item::Item(const std::string &name, float x, float y,
           sf::Time duration, bool useOnSelf, float acc,
           float maxSpeed, bool reverse, bool explode,
           bool stun, bool swap) : name(name), xPos(x), yPos(y), duration(duration),
                                   useOnSelf(useOnSelf), changeAcc(acc),
                                   changeMaxSpeed(maxSpeed), reverseSteering(reverse),
                                   explode(explode), stun(stun), swap(swap)
{
    createTextureMap();
    texture.loadFromFile(itemTextures[name]);
    setTexture(texture);
    setPosition(x, y);
}

std::string Item::getName() const
{
    return name;
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

void Item::refreshTexture()
{
    setTexture(texture);
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