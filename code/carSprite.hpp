#ifndef CARSPRITE_H
#define CARSPRITE_H

#include <SFML/Graphics.hpp>
#include <cmath>

enum TriStateBool
{
    False, // -
    Zero,  // 0
    True   // +
};

class CarSprite : public sf::Sprite
{
public:
    CarSprite(std::string color, float x, float y);
    void updateDirectionTexture();
    bool reloadTextures();
    void setColor(std::string newColor);
    std::string getColor();
    void setNextAction(bool &WPressed, bool &APressed, bool &SPressed, bool &DPressed);
    void move();
    void noMovementKeyPressed();

private:
    void changeVelocity(TriStateBool xAcc, TriStateBool yAcc);
    std::vector<sf::Texture> textures;
    std::string color = "";
    unsigned int keyAction = 0;
    float rotation = 0;
    float xVelocity = 0;
    float yVelocity = 0;
    float maxSpeed = 0.5;
    float acceleration = 0.001;
    float x = 300;
    float y = 300;
};

#endif