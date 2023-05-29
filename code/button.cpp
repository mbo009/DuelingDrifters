#include "button.hpp"
#include <map>

std::map<std::string, std::string> baseTextures;
std::map<std::string, std::string> highlightedTextures;

void createBaseMap()
{
    baseTextures["start"] = ASSET_PATHS_HPP::START_BTN;
    baseTextures["exit"] = ASSET_PATHS_HPP::EXIT_BTN;
    // TODO: Change this when we have a new button
    baseTextures["normal"] = ASSET_PATHS_HPP::START_BTN; // ::NORMAL;
    baseTextures["tag"] = ASSET_PATHS_HPP::EXIT_BTN;   // ::TAG;
    // baseTextures["custom"] = ASSET_PATHS_HPP::START_BTN; // ::CUSTOM;
}

void createHighlightedMap()
{
    highlightedTextures["start"] = ASSET_PATHS_HPP::HLT_START_BTN;
    highlightedTextures["exit"] = ASSET_PATHS_HPP::HLT_EXIT_BTN;
    // TODO: Change this when we have a new button
    highlightedTextures["normal"] = ASSET_PATHS_HPP::HLT_START_BTN; // ::NORMAL;
    highlightedTextures["tag"] = ASSET_PATHS_HPP::HLT_EXIT_BTN;   // ::TAG;
    // highlightedTextures["custom"] = ASSET_PATHS_HPP::HLT_START_BTN; // ::CUSTOM;
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