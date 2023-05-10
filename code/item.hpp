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
    Item(const std::string &name, float x, float y);
    std::string getName() const;
    float getX() const;
    void setX(float x);
    float getY() const;
    void setY(float y);
    void refreshTexture();

private:
    sf::Texture texture;
    std::string name;
    float xPos;
    float yPos;
};

#endif