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

CarSprite::CarSprite(const std::string &color, float x, float y, float scale) : x(x), y(y)
{
    this->x = x;
    this->y = y;
    this->carObj = CarObj(x, y);
    this->scale = scale;
    this->setScale(sf::Vector2f(scale, scale));
    this->setColor(color);
}

CarSprite &CarSprite::operator=(const CarSprite &other)
{
    if (this != &other)
    {
        this->keyAction = other.keyAction;
        this->scale = other.scale;
        this->setScale(sf::Vector2f(scale, scale));
        this->x = other.x;
        this->y = other.y;
        this->textures = other.textures;
        this->carObj = other.carObj;
        this->color = other.color;
    }
    return *this;
}

void CarSprite::setColor(const std::string &color)
{
    this->color = color;
    textures.clear();
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

int CarSprite::getKeyAction() const
{
    return keyAction;
}

int CarSprite::getScale() const
{
    return scale;
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

float CarSprite::getX() const
{
    return carObj.getX();
}

float CarSprite::getY() const
{
    return carObj.getY();
}

void CarSprite::updateDirectionTexture()
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
    // const sf::Uint8 *pixels1 = image1.getPixelsPtr();
    // const sf::Uint8 *pixels2 = image2.getPixelsPtr();
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

void CarSprite::loadStartingPosition(unsigned int carId)
{
    if (carId == 1)
        initialTexture.loadFromFile("assets/images/Car/downRight.png");
    else
        initialTexture.loadFromFile("assets/images/Car/upLeft.png");

    setTexture(initialTexture);
}