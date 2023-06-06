/**
 * @file button.hpp
 * @author Binh Vuong Le Duc, Filip Ryniewicz, Cieśla Miłosz
 * @brief Class for the buttons
 * @date 2023-06-04
 *
 */
#ifndef BUTTON_H
#define BUTTON_H
#pragma once

#include <utility>
#include <map>
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
    std::map<std::string, std::pair<std::string, std::string>> texturePaths = {
        {"start", {ASSET_PATHS_HPP::START_BTN, ASSET_PATHS_HPP::HLT_START_BTN}},
        {"exit", {ASSET_PATHS_HPP::EXIT_BTN, ASSET_PATHS_HPP::HLT_EXIT_BTN}},
        {"duel", {ASSET_PATHS_HPP::DUEL_BTN, ASSET_PATHS_HPP::HLT_DUEL_BTN}},
        {"flag", {ASSET_PATHS_HPP::FLAG_BTN, ASSET_PATHS_HPP::HLT_FLAG_BTN}},
        {"arrowLeft", {ASSET_PATHS_HPP::LEFT_ARROW, ASSET_PATHS_HPP::LEFT_ARROW}},
        {"arrowRight", {ASSET_PATHS_HPP::RIGHT_ARROW, ASSET_PATHS_HPP::RIGHT_ARROW}},
        {"long", {ASSET_PATHS_HPP::LONG_BUTTON, ASSET_PATHS_HPP::HLT_LONG_BUTTON}}};
    sf::Texture baseTexture;
    sf::Texture highlightedTexture;
    bool highlighted = 0;
    bool clicked;
    float x;
    float y;
    std::string name;
};
#endif
