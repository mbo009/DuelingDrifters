#include "item.hpp"
#include <map>
#include <string>
std::map<std::string, std::string> itemTextures;

void createTextureMap()
{
    itemTextures["SpeedUp"] = ASSET_PATHS_HPP::SPEED_ORB;
    itemTextures["OpponentSlow"] = ASSET_PATHS_HPP::OPPONENT_SLOW_ORB;
    itemTextures["Bomb"] = ASSET_PATHS_HPP::BOMB_ORB;
    itemTextures["Dash"] = ASSET_PATHS_HPP::DASH_ORB;
}

Item::Item(const std::string &name, float x, float y, sf::Time duration, bool useOnSelf, float acc, float maxSpeed, bool reverse, bool explode) : name(name), xPos(x), yPos(y), duration(duration),
                                                                                                                                                  useOnSelf(useOnSelf), changeAcc(acc),
                                                                                                                                                  changeMaxSpeed(maxSpeed), reverseSteering(reverse),
                                                                                                                                                  explode(explode)
{
    createTextureMap();
    texture.loadFromFile(itemTextures[name]);
    // texture.loadFromFile("assets/images/items/bomb.png");
    setTexture(texture);
    setPosition(x, y);
    // sf::Transformable::setScale(sf::Vector2f(10, 10));
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