#include "carSprite.hpp"
std::vector<std::string> files = {"up", "upRight", "right", "downRight",
                                  "down", "downLeft", "left", "upLeft"};
std::string folder = "img";
std::string extension = "png";

class loadingTexturesError : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Error in loading textures!";
    }
};

CarSprite::CarSprite(std::string color, float x, float y) : x(x), y(y)
{
    setColor(color);
    setPosition(x, y);
}

std::string CarSprite::getColor()
{
    return color;
}

void CarSprite::setColor(std::string new_color)
{
    color = new_color;
    if (textures.size() == 0)
        textures.clear();
    reloadTextures();
}

bool CarSprite::reloadTextures()
{
    sf::Texture temp;
    for (const auto &t : files)
    {
        if (temp.loadFromFile(folder + "/" + t + color + "." + extension))
            textures.push_back(temp);
        else
            throw loadingTexturesError();
    }
    setTexture(textures[0]);
}

void CarSprite::setNextAction(bool &UpPressed, bool &LeftPressed, bool &DownPressed, bool &RightPressed)
{
    if (UpPressed && RightPressed)
        keyAction = 1;
    else if (RightPressed && DownPressed)
        keyAction = 3;
    else if (DownPressed && LeftPressed)
        keyAction = 5;
    else if (LeftPressed && UpPressed)
        keyAction = 7;
    else if (UpPressed)
        keyAction = 0;
    else if (RightPressed)
        keyAction = 2;
    else if (DownPressed)
        keyAction = 4;
    else if (LeftPressed)
        keyAction = 6;
}

void CarSprite::updateDirectionTexture()
{
    setTexture(textures[keyAction]);
}

void CarSprite::changeVelocity(TriStateBool xAcc, TriStateBool yAcc)
{
    if (xVelocity + acceleration < maxSpeed && xAcc == 2) // Right
        xVelocity += acceleration;
    else if (xVelocity - acceleration > -maxSpeed && xAcc == 0) // Left
        xVelocity -= acceleration;
    else if (xAcc == 1 && xVelocity > 0)
        xVelocity -= acceleration / 2;
    else if (xAcc == 1 && xVelocity < 0)
        xVelocity += acceleration / 2;

    if (yVelocity + acceleration < maxSpeed && yAcc == 2) // Up
        yVelocity += acceleration;
    else if (yVelocity - acceleration > -maxSpeed && yAcc == 0) // Down
        yVelocity -= acceleration;
    else if (yAcc == 1 && yVelocity > 0)
        yVelocity -= acceleration / 2;
    else if (yAcc == 1 && yVelocity < 0)
        yVelocity += acceleration / 2;
}

void CarSprite::move()
{
    if (keyAction == 0)
        changeVelocity(Zero, False);
    else if (keyAction == 1)
        changeVelocity(True, False);
    else if (keyAction == 2)
        changeVelocity(True, Zero);
    else if (keyAction == 3)
        changeVelocity(True, True);
    else if (keyAction == 4)
        changeVelocity(Zero, True);
    else if (keyAction == 5)
        changeVelocity(False, True);
    else if (keyAction == 6)
        changeVelocity(False, Zero);
    else if (keyAction == 7)
        changeVelocity(False, False);
    else if (keyAction == 8)
        changeVelocity(Zero, Zero);

    x += xVelocity;
    y += yVelocity;
    setPosition(x, y);
}

void CarSprite::noMovementKeyPressed()
{
    keyAction = 8;
}
