#include "button.hpp"
#include <map>

std::map<std::string, std::string> baseTextures;
std::map<std::string, std::string> highlightedTextures;

void createBaseMap()
{
    baseTextures["start"] = ASSET_PATHS_HPP::START;
    baseTextures["exit"] = ASSET_PATHS_HPP::EXIT;
    // TODO: Change this when we have a new button
    baseTextures["normal"] = ASSET_PATHS_HPP::START; // ::NORMAL;
    baseTextures["tag"] = ASSET_PATHS_HPP::EXIT;   // ::TAG;
    // baseTextures["custom"] = ASSET_PATHS_HPP::START; // ::CUSTOM;
}

void createHighlightedMap()
{
    highlightedTextures["start"] = ASSET_PATHS_HPP::HIGHLIGHTED_START;
    highlightedTextures["exit"] = ASSET_PATHS_HPP::HIGHLIGHTED_EXIT;
    // TODO: Change this when we have a new button
    highlightedTextures["normal"] = ASSET_PATHS_HPP::HIGHLIGHTED_START; // ::NORMAL;
    highlightedTextures["tag"] = ASSET_PATHS_HPP::HIGHLIGHTED_EXIT;   // ::TAG;
    // highlightedTextures["custom"] = ASSET_PATHS_HPP::HIGHLIGHTED_START; // ::CUSTOM;
}

Button::Button(float x, float y, std::string name) : x(x), y(y), name(name)
{
    createBaseMap();
    createHighlightedMap();
    baseTexture.loadFromFile(baseTextures[name]);
    highlightedTexture.loadFromFile(highlightedTextures[name]);
    setTexture(baseTexture);
    setPosition(x, y);
    setScale(2, 2);
}

void Button::highlight()
{
    setTexture(highlightedTexture);
    highlighted = 1;
}

void Button::highlightOff()
{
    setTexture(baseTexture);
    highlighted = 0;
}

std::string Button::getName()
{
    return name;
}