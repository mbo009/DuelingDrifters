#ifndef BUTTON_H
#define BUTTON_H

#include "SFML/Graphics.hpp"

class Button : public sf::Sprite
{
public:
    Button(float x, float y, std::string name);
    void highlight();
    void highlightOff();
    void click();

private:
    std::string name;
    sf::Texture baseTexture;
    sf::Texture highlightedTexture;
    bool higlighted;
    bool clicked;
    float x;
    float y;
};
#endif
