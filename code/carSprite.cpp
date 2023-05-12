#include "carSprite.hpp"

CarSprite::CarSprite(const std::string &color, float x, float y, float scale, unsigned int initTextureCode) : scale(scale), x(x), y(y)
{
    sf::Transformable::setScale(sf::Vector2f(scale, scale));
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

void CarSprite::updateTexture(CarSprite &other)
{
    sf::Sprite test;
    test.setPosition(x, y);
    test.setTexture(textures[keyAction]);
    if (!other.checkCollision(test))
        setTexture(textures[keyAction]);
}

void CarSprite::setNextAction(bool &UpPressed, bool &LeftPressed, bool &DownPressed, bool &RightPressed, CarSprite &other)
{
    if (reversed)
    {
        bool temp = UpPressed;
        UpPressed = DownPressed;
        DownPressed = temp;
        temp = LeftPressed;
        LeftPressed = RightPressed;
        RightPressed = temp;
    }

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
    updateTexture(other);
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

void CarSprite::getPushed(float opXV, float opYV)
{
    // if (timeSinceCollision.getElapsedTime().asMilliseconds() > 10)
    this->carObj.getPushed(opXV, opYV);
    timeSinceCollision.restart();
}

void CarSprite::push(float opXV, float opYV)
{
    // if (timeSinceCollision.getElapsedTime().asMilliseconds() > 10)
    this->carObj.push(opXV, opYV);
    timeSinceCollision.restart();
}

void CarSprite::resetCar()
{
    setPosition(carObj.getStartX(), carObj.getStartY());
    setTexture(textures[initialTextureCode - 1]);
    carObj.reset();
    carObj.resetBaseStats();
    reversed = 0;
}

std::string CarSprite::toLowerCase(const std::string &str)
{
    std::string result(str);
    std::transform(str.begin(), str.end(), result.begin(), [](unsigned char c)
                   { return std::tolower(c); });
    return result;
}

void CarSprite::explosion()
{
    getPushed(-2 * carObj.getXVelocity(), -2 * carObj.getYVelocity());
}

bool CarSprite::checkCollision(const sf::Sprite &other)
{
    // Get the current texture for each sprite
    const std::shared_ptr<sf::Texture> texture1 = std::make_shared<sf::Texture>(*this->getTexture());
    const std::shared_ptr<sf::Texture> texture2 = std::make_shared<sf::Texture>(*other.getTexture());
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

void CarSprite::checkItemReset()
{
    if (activeItem)
    {
        if (activeItemClock.getElapsedTime().asMilliseconds() > timeItem.asMilliseconds())
        {
            carObj.resetBaseStats();
            reversed = false;
            activeItem = 0;
        }
    }
}

void CarSprite::usedItem(sf::Time time)
{
    activeItem = true;
    timeItem = time;
    activeItemClock.restart();
}

void CarSprite::reverseSteering()
{
    reversed = true;
}

void CarSprite::stop()
{
    carObj.stop();
}

void CarSprite::setPos(float x, float y)
{
    this->x = x;
    this->y = y;
    carObj.setX(x);
    carObj.setY(y);
}
