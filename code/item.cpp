#include "item.hpp"
#include <map>
#include <string>
std::map<std::string, std::string> itemTextures;

void createTextureMap()
{
    itemTextures["SpeedUp"] = ASSET_PATHS_HPP::SPEED_ORB;
    itemTextures["OpponentSlow"] = ASSET_PATHS_HPP::OPPONENT_SLOW_ORB;
    itemTextures["Bomb"] = ASSET_PATHS_HPP::BOMB_ORB;
}

Item::Item(const std::string &name, float x, float y) : name(name), xPos(x), yPos(y)
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

void Item::refreshTexture()
{
    setTexture(texture);
}