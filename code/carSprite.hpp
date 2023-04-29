#ifndef CARSPRITE_H
#define CARSPRITE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "carObj.hpp"

class CarSprite : public sf::Sprite
{
public:
    CarSprite(const std::string &color = "red", float x = 0, float y = 0, float scale = 1);
    CarSprite &operator=(const CarSprite &other);
    void setColor(const std::string &color);
    std::string getColor() const;
    int getKeyAction() const;
    int getScale() const;
    float getX() const;
    float getY() const;

    bool reloadTextures();
    void updateDirectionTexture();
    void setNextAction(bool &WPressed, bool &APressed, bool &SPressed, bool &DPressed);
    void noMovementKeyPressed();
    void move();
    void restartPosition();
    bool checkCollision(const CarSprite &other);
    sf::Vector2f getVelocity();
    void getPushed(float opXV, float opYV);
    void push(float opXV, float opYV);
    CarObj &getCarObj();
    void loadStartingPosition(unsigned int carId);

private:
    // TODO: Add more colors, change the folder, change the extension
    //=================THIS SHOULD BE CHANGE==============//
    const std::vector<std::string> files = {"up", "upRight", "right", "downRight",
                                            "down", "downLeft", "left", "upLeft"};
    const std::string folder = "img";
    const std::string extension = "png";
    // ==================================================//
    unsigned int keyAction = 8;
    float scale = 1.0;
    float x = 300;
    float y = 300;
    std::vector<sf::Texture> textures;
    CarObj carObj;
    std::string color = "";
    sf::Texture initialTexture;
};

#endif