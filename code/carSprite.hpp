#ifndef CARSPRITE_H
#define CARSPRITE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "carObj.hpp"

class CarSprite : public sf::Sprite
{
public:
    CarSprite(const std::string &color = "red", float x = 0, float y = 0);
    void setColor(const std::string &newColor); // Set new color, reload textures
    std::string getColor() const;               // Return the color of the car
    bool reloadTextures();
    void updateDirectionTexture();
    float getX();
    float getY();
    // TODO: Write setter for x, y
    // Convert user input to parameters to pass to carObj
    void setNextAction(bool &WPressed, bool &APressed, bool &SPressed, bool &DPressed);
    void noMovementKeyPressed();
    // Get updated position from carObj
    void move();

private:
    // TODO: Add more colors, change the folder, change the extension
    //=================THIS SHOULD BE CHANGE==============//
    const std::vector<std::string> files = {"up", "upRight", "right", "downRight",
                                            "down", "downLeft", "left", "upLeft"};
    const std::string folder = "img";
    const std::string extension = "png";
    // ==================================================//
    std::vector<sf::Texture> textures;
    CarObj carObj;
    std::string color = "";
    void changeVelocity(TriStateBool xAcc, TriStateBool yAcc);
    unsigned int keyAction = 0;
};

#endif