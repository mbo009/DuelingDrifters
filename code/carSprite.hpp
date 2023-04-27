#include <SFML/Graphics.hpp>

class CarSprite : public sf::Sprite
{
public:
    CarSprite(std::string color);
    void updateCarDirection(sf::Event &event, bool &W, bool &A, bool &S, bool &D);
    bool reloadTextures();
    void setColor(std::string newColor);
    std::string getColor();

private:
    std::vector<sf::Texture> textures;
    std::string color = "";
    float rotation = 0;
    float velocity = 0;
    float maxSpeed = 10;
    float acceleration = 0.1;
    float x = 300;
    float y = 300;
};
