#ifndef CARSPRITE_H
#define CARSPRITE_H

#include <vector>
#include <algorithm>
#include <cctype>
#include <memory>
#include "carObj.hpp"
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
    sf::Sprite &getDummy();
    void resetDummyPosition();

    void loadTextures();
    void updateTexture(CarSprite &other, unsigned int lastAction);
    void setNextAction(bool &WPressed, bool &APressed, bool &SPressed, bool &DPressed, CarSprite &other);
    void noMovementKeyPressed();
    void move();
    void preMove();
    bool checkCollision(const sf::Sprite &other);
    void getPushed(float opXV, float opYV);
    void push(float opXV, float opYV);
    void resetCar();
    void explosion();
    void checkItemReset();
    void usedItem(sf::Time timeItem);
    void reverseSteering();
    void stop();
    void setPos(float x, float y);

private:
    std::string toLowerCase(const std::string &str);
    unsigned int keyAction = 8;
    float scale;
    float x;
    float y;
    CarObj carObj;
    std::string color;
    std::vector<sf::Texture> textures;
    sf::Texture initialTexture;
    sf::Clock activeItemClock;
    bool activeItem;
    bool reversed = false;
    sf::Time timeItem;
    unsigned int initialTextureCode = 1;
    CarObj dummyCar;
    sf::Sprite dummyCarSprite;
};

#endif