#include "button.hpp"

/**
 * @brief Construct a new Button
 *
 * @param x Postion of button on x-axis
 * @param y Postion of button on y-axis
 * @param name Name of button for loading textures
 */
Button::Button(float x, float y, std::string name, sf::Vector2f scale) : x(x), y(y), name(name)
{
    baseTexture.loadFromFile(texturePaths[name].first);
    highlightedTexture.loadFromFile(texturePaths[name].second);
    setTexture(baseTexture);
    setPosition(x, y);
    setScale(scale);
}

/**
 * @brief Set the highlight state of the button.
 * By changing the texture of the button from base to highlighted.
 * @param state State of highlight
 */
void Button::highlight(bool state)
{
    highlighted = state;
    if (highlighted)
        setTexture(highlightedTexture);
    else
        setTexture(baseTexture);
}

/**
 * @brief Get the name of the button
 *
 */
std::string Button::getName()
{
    return name;
}