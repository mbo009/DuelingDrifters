#ifndef CARSPRITE_H
#define CARSPRITE_H

// #include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <cctype>
// #include <string>
#include <memory>
#include "carObj.hpp"
// #include "assetPaths.hpp"
#include "exception.hpp"
#include "item.hpp"

class CarSprite : public sf::Sprite
{
public:
    CarSprite(const std::string &color = "red", float x = 0, float y = 0, float scale = 1, unsigned int initTextureCode = 1);
    CarSprite &operator=(const CarSprite &other);
    int getKeyAction() const;
    int getScale() const;
    float getX() const;
    float getY() const;
    sf::Vector2f getVelocity();
    void setColor(const std::string &color);
    std::string getColor() const;
    CarObj &getCarObj();

    void loadTextures();
    void updateTexture();
    void setNextAction(bool &WPressed, bool &APressed, bool &SPressed, bool &DPressed);
    void noMovementKeyPressed();
    void move();
    bool checkCollision(const CarSprite &other);
    void getPushed(float opXV, float opYV);
    void push(float opXV, float opYV);
    void resetCar();

private:
    std::string toLowerCase(const std::string &str);
    unsigned int keyAction = 8;
    float scale = 1.0;
    float x = 300;
    float y = 300;
    CarObj carObj;
    std::string color = "";
    std::vector<sf::Texture> textures;
    sf::Texture initialTexture;
    sf::Clock timeSinceCollision;
    unsigned int initialTextureCode = 1;
};

#endif