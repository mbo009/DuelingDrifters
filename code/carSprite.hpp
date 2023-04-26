#include <SFML/Graphics.hpp>

class CarSprite : public sf::Sprite
{
public:
    CarSprite();
    void updateCarDirection(sf::Event &event, bool &W, bool &A, bool &S, bool &D);
    bool reloadTextures();
    void setColor(std::string newColor);

private:
    std::vector<sf::Texture> textures;
    // std::string color = "";
};
