#ifndef CARSPRITE_H
#define CARSPRITE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <vector>

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
    std::vector<sf::Texture> textures;
    void changeVelocity(TriStateBool xAcc, TriStateBool yAcc);
    std::string color = "";
    unsigned int keyAction = 0;
    float rotation = 0;
    float xVelocity = 0;
    float yVelocity = 0;
    float maxSpeed = 6;
    float acceleration = 0.2;
    float x = 300;
    float y = 300;
};

#endif