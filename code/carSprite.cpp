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

CarSprite::CarSprite(std::string color)
{
    setColor(color);
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

bool CarSprite::setNextAction(bool &WPressed, bool &APressed, bool &SPressed, bool &DPressed)
{
    if (WPressed && DPressed)
        keyAction = 1;
    else if (DPressed && SPressed)
        keyAction = 3;
    else if (SPressed && APressed)
        keyAction = 5;
    else if (APressed && WPressed)
        keyAction = 7;
    else if (WPressed)
        keyAction = 0;
    else if (DPressed)
        keyAction = 2;
    else if (SPressed)
        keyAction = 4;
    else if (APressed)
        keyAction = 6;
}
void CarSprite::updateDirectionTexture()
{
    setTexture(textures[keyAction]);
}