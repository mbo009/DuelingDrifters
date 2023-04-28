#include "carSprite.hpp"

// TODO: Implement error as a class
class loadingTexturesError : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Error in loading textures!";
    }
};

CarSprite::CarSprite(const std::string &color, float x, float y)
{
    this->setColor(color);
    carObj = CarObj(x, y);
}

void CarSprite::setColor(const std::string &color)
{
    this->color = color;
    textures.clear(); // Clear the textures vector
    reloadTextures();
}

void CarSprite::restartPosition()
{
    setPosition(getCarObj().getStartX(), getCarObj().getStartY());
    getCarObj().restart();
}

std::string CarSprite::getColor() const
{
    return color;
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
    return true;
}

float CarSprite::getX()
{
    return carObj.getX();
}

float CarSprite::getY()
{
    return carObj.getY();
}

void CarSprite::updateDirectionTexture()
{
    setTexture(textures[keyAction]);
}

void CarSprite::setNextAction(bool &UpPressed, bool &LeftPressed, bool &DownPressed, bool &RightPressed)
{
    if (UpPressed && RightPressed) // Go north-east
        this->keyAction = 1;
    else if (RightPressed && DownPressed) // Go south-east
        this->keyAction = 3;
    else if (DownPressed && LeftPressed) // Go south-west
        this->keyAction = 5;
    else if (LeftPressed && UpPressed) // Go north-west
        this->keyAction = 7;
    else if (UpPressed) // Go north
        this->keyAction = 0;
    else if (RightPressed) // Go east
        this->keyAction = 2;
    else if (DownPressed) // Go south
        this->keyAction = 4;
    else if (LeftPressed) // Go west
        this->keyAction = 6;
}

CarObj &CarSprite ::getCarObj()
{
    return carObj;
}

void CarSprite::noMovementKeyPressed()
{
    keyAction = 8;
}

void CarSprite::move()
{
    carObj.move(keyAction);
    setPosition(getX(), getY());
}

sf::Vector2f CarSprite::getVelocity()
{
    return sf::Vector2f(carObj.getXVelocity(), carObj.getYVelocity());
}

void CarSprite::getPushed(float opXV, float opYV)
{
    this->carObj.getPushed(opXV, opYV);
}

void CarSprite::push(float opXV, float opYV)
{
    this->carObj.push(opXV, opYV);
}