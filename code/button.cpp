#include "button.hpp"
#include <map>

Button::Button(float x, float y, std::string name) : x(x), y(y), name(name)
{
    baseTexture.loadFromFile(texturePaths[name].first);
    highlightedTexture.loadFromFile(texturePaths[name].second);
    setTexture(baseTexture);
    setPosition(x, y);
    setScale(2, 2);
}

void Button::highlight(bool state)
{
    highlighted = state;
    if (highlighted)
        setTexture(highlightedTexture);
    else
        setTexture(baseTexture);
}

std::string Button::getName()
{
    return name;
}