#include "carSprite.hpp"
std::vector<std::string> files = {"up", "upRight", "right", "downRight",
                                  "down", "downLeft", "left", "upLeft"};
std::string folder = "img";
std::string extension = "png";
std::string color = "Red";

class loadingTexturesError : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Error in loading textures!";
    }
};

CarSprite::CarSprite()
{
    reloadTextures();
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

void CarSprite::updateCarDirection(sf::Event &event, bool &WPressed, bool &APressed, bool &SPressed, bool &DPressed)
{
    if (event.type == sf::Event::KeyPressed && WPressed && DPressed)
        setTexture(textures[1]);
    else if (event.type == sf::Event::KeyPressed && DPressed && SPressed)
        setTexture(textures[3]);
    else if (event.type == sf::Event::KeyPressed && SPressed && APressed)
        setTexture(textures[5]);
    else if (event.type == sf::Event::KeyPressed && APressed && WPressed)
        setTexture(textures[7]);
    else if (event.type == sf::Event::KeyPressed && WPressed)
        setTexture(textures[0]);
    else if (event.type == sf::Event::KeyPressed && DPressed)
        setTexture(textures[2]);
    else if (event.type == sf::Event::KeyPressed && SPressed)
        setTexture(textures[4]);
    else if (event.type == sf::Event::KeyPressed && APressed)
        setTexture(textures[6]);
}