#include <SFML/Graphics.hpp>

class CarSprite : public sf::Sprite
{
public:
    CarSprite(std::string color);
    void updateDirectionTexture();
    bool reloadTextures();
    void setColor(std::string newColor);
    std::string getColor();
    bool setNextAction(bool &WPressed, bool &APressed, bool &SPressed, bool &DPressed);

private:
    std::vector<sf::Texture> textures;
    std::string color = "";
    unsigned int keyAction = 0;
    float rotation = 0;
    float x_velocity = 0;
    float y_velocity = 0;
    float maxSpeed = 10;
    float acceleration = 0.1;
    float x = 300;
    float y = 300;
};
