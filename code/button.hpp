#ifndef BUTTON_H
#define BUTTON_H

#include "SFML/Graphics.hpp"
#include "assetPaths.hpp"

class Button : public sf::Sprite
{
public:
    Button(float x, float y, std::string name);
    void highlight(bool state);
    void click();
    std::string getName();

private:
    sf::Texture baseTexture;
    sf::Texture highlightedTexture;
    bool highlighted = 0;
    bool clicked;
    float x;
    float y;
    std::string name;
};
#endif
