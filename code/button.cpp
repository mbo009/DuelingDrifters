#include "button.hpp"
#include <map>

std::map<std::string, std::string> baseTextures;
std::map<std::string, std::string> highlightedTextures;

void createBaseMap()
{
    baseTextures["start"] = ASSET_PATHS_HPP::START_BTN;
    baseTextures["exit"] = ASSET_PATHS_HPP::EXIT_BTN;
    baseTextures["duel"] = ASSET_PATHS_HPP::DUEL_BTN;
    baseTextures["flag"] = ASSET_PATHS_HPP::FLAG_BTN;
}

void createHighlightedMap()
{
    highlightedTextures["start"] = ASSET_PATHS_HPP::HLT_START_BTN;
    highlightedTextures["exit"] = ASSET_PATHS_HPP::HLT_EXIT_BTN;
    highlightedTextures["duel"] = ASSET_PATHS_HPP::HLT_DUEL_BTN; // ::NORMAL;
    highlightedTextures["flag"] = ASSET_PATHS_HPP::HLT_FLAG_BTN;   // ::TAG;
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