#include "carSprite.hpp"

CarSprite::CarSprite(const std::string &color, float x, float y, float scale, unsigned int initTextureCode)
{
    this->scale = scale;
    sf::Transformable::setScale(sf::Vector2f(scale, scale));
    this->x = x;
    this->y = y;
    this->carObj = CarObj(x, y);
    setColor(color);
    this->initialTextureCode = initTextureCode;
    setTexture(textures[initialTextureCode - 1]);
}

CarSprite &CarSprite::operator=(const CarSprite &other)
{
    if (this != &other)
    {
        this->keyAction = other.keyAction;
        this->scale = other.scale;
        this->sf::Transformable::setScale(sf::Vector2f(scale, scale));
        this->x = other.x;
        this->y = other.y;
        this->textures = other.textures;
        this->carObj = other.carObj;
        this->color = other.color;
        this->initialTextureCode = other.initialTextureCode;
        this->setTexture(textures[initialTextureCode - 1]);
    }
    return *this;
}

int CarSprite::getKeyAction() const
{
    return keyAction;
}

int CarSprite::getScale() const
{
    return scale;
}

float CarSprite::getX() const
{
    return carObj.getX();
}

float CarSprite::getY() const
{
    return carObj.getY();
}

sf::Vector2f CarSprite::getVelocity()
{
    return sf::Vector2f(carObj.getXVelocity(), carObj.getYVelocity());
}

void CarSprite::setColor(const std::string &color)
{
    this->color = toLowerCase(color);
    textures.clear();
    loadTextures();
}

std::string CarSprite::getColor() const
{
    return color;
}

CarObj &CarSprite ::getCarObj()
{
    return carObj;
}

void CarSprite::loadTextures()
{
    sf::Texture temp;
    for (size_t i = 0; i < ASSET_PATHS_HPP::CAR_SPRITE_LIST.at(color).size(); i++)
    {
        if (temp.loadFromFile(ASSET_PATHS_HPP::CAR_SPRITE_LIST.at(color)[i]))
            textures.push_back(temp);
        else
            throw loadingTexturesError();
    }
}

void CarSprite::updateTexture()
{
    return setTexture(textures[keyAction]);
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
    updateTexture();
    return;
}

void CarSprite::noMovementKeyPressed()
{
    keyAction = 8;
}

void CarSprite::move()
{
    carObj.move(keyAction);
    setPosition(carObj.getX(), carObj.getY());
    this->x = carObj.getX();
    this->y = carObj.getY();
}

bool CarSprite::checkCollision(const CarSprite &other)
{
    // Get the current texture for each sprite
    const sf::Texture *texture1 = this->getTexture();
    const sf::Texture *texture2 = other.getTexture();
    if (!texture1 || !texture2) // Make sure both sprites have textures
    {
        return false;
    }

    // Get the global bounds of each sprite
    sf::FloatRect bounds1 = this->getGlobalBounds();
    sf::FloatRect bounds2 = other.getGlobalBounds();

    // Calculate the intersection rectangle
    sf::FloatRect intersection;
    if (!bounds1.intersects(bounds2, intersection)) // No intersection, no collision
    {
        return false;
    }

    // Get the texture data for each sprite
    sf::Image image1 = texture1->copyToImage();
    sf::Image image2 = texture2->copyToImage();
    // Check each pixel in the intersection area for opacity overlap
    for (int x = intersection.left; x < intersection.left + intersection.width; x++)
    {
        for (int y = intersection.top; y < intersection.top + intersection.height; y++)
        {
            sf::Color color1 = image1.getPixel((x - bounds1.left) / this->scale, (y - bounds1.top) / this->scale);
            sf::Color color2 = image2.getPixel((x - bounds2.left) / this->scale, (y - bounds2.top) / this->scale);
            if (color1.a != 0 && color2.a != 0)
            {
                return true; // Collision detected
            }
        }
    }
    return false; // No collision detected
}

void CarSprite::getPushed(float opXV, float opYV)
{
    if (timeSinceCollision.getElapsedTime().asMilliseconds() > 10)
        this->carObj.getPushed(opXV, opYV);
    timeSinceCollision.restart();
}

void CarSprite::push(float opXV, float opYV)
{
    if (timeSinceCollision.getElapsedTime().asMilliseconds() > 10)
        this->carObj.push(opXV, opYV);
    timeSinceCollision.restart();
}

void CarSprite::resetCar()
{
    setPosition(carObj.getStartX(), carObj.getStartY());
    setTexture(textures[initialTextureCode - 1]);
    carObj.restart();
}

std::string CarSprite::toLowerCase(const std::string &str)
{
    std::string result(str);
    std::transform(str.begin(), str.end(), result.begin(), [](unsigned char c)
                   { return std::tolower(c); });
    return result;
}