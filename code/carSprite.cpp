#include "carSprite.hpp"

/**
 * @brief Construct a new Car Sprite:: Car Sprite object
 *
 * @param color color to indicate which texture to load
 * @param x position of the sprite on the x-axis
 * @param y position of the sprite on the y-axis
 * @param scale scale original size of the texture
 * @param initTextureCode direction texture of the car
 */
CarSprite::CarSprite(const std::string &color, float x, float y, float scale, unsigned int initTextureCode) : scale(scale), x(x), y(y)
{
    sf::Transformable::setScale(sf::Vector2f(scale, scale));
    this->carObj = CarObj(x, y);
    setColor(color);
    this->initialTextureCode = initTextureCode;
    setTexture(textures[initialTextureCode - 1]);
}

/**
 * @brief Overloaded assignment operator.
 *
 * @param other
 * @return CarSprite&
 */
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

/**
 * @brief Return the key action of the car, which is the direction it is moving in.
 *
 * @return int
 */
int CarSprite::getKeyAction() const
{
    return keyAction;
}

/**
 * @brief Return the scale of the car sprite.
 *
 * @return int
 */

int CarSprite::getScale() const
{
    return scale;
}

/**
 * @brief Return position of the car sprite on the x-axis.
 *
 * @return float
 */
float CarSprite::getX() const
{
    return carObj.getX();
}

/**
 * @brief Return position of the car sprite on the y-axis.
 *
 * @return float
 */
float CarSprite::getY() const
{
    return carObj.getY();
}

/**
 * @brief Return the velocity of the car object containing the car sprite.
 *
 * @return sf::Vector2f
 */
sf::Vector2f CarSprite::getVelocity()
{
    return sf::Vector2f(carObj.getXVelocity(), carObj.getYVelocity());
}

/**
 * @brief Set the color of the car sprite.
 *
 * @param color
 */
void CarSprite::setColor(const std::string &color)
{
    this->color = toLowerCase(color);
    textures.clear();
    loadTextures();
}

/**
 * @brief Return the color of the car sprite.
 *
 * @return std::string
 */
std::string CarSprite::getColor() const
{
    return color;
}

/**
 * @brief Return the car object containing the car sprite.
 *
 * @return CarObj&
 */
CarObj &CarSprite ::getCarObj()
{
    return carObj;
}

unsigned int CarSprite::getPoints()
{
    return carObj.getPoint();
}

/**
 * @brief Load the textures for the car sprite.
 * @return exception if failed to load texture.
 */
void CarSprite::loadTextures()
{
    sf::Texture temp;
    for (size_t i = 0; i < ASSET_PATHS_HPP::CAR_SPRITE_LIST.at(color).size(); i++)
    {
        if (temp.loadFromFile(ASSET_PATHS_HPP::CAR_SPRITE_LIST.at(color)[i]))
            textures.push_back(temp);
        else
            throw failedToLoadTexture();
    }
}

/**
 * @brief
 *
 * @param other
 */
void CarSprite::updateTexture(CarSprite &other)
{
    sf::Sprite test;
    test.setPosition(x, y);
    test.setTexture(textures[keyAction]);
    if (!other.checkCollision(test))
        setTexture(textures[keyAction]);
}

/**
 * @brief
 *
 * @param UpPressed
 * @param LeftPressed
 * @param DownPressed
 * @param RightPressed
 * @param other
 */
void CarSprite::setNextAction(bool &UpPressed, bool &LeftPressed, bool &DownPressed, bool &RightPressed, CarSprite &other)
{
    if (reversed)
    {
        std::swap(UpPressed, DownPressed);
        std::swap(LeftPressed, RightPressed);
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
}

/**
 * @brief Hold direction of the car sprite when no movement key is pressed.
 *
 */
void CarSprite::noMovementKeyPressed()
{
    keyAction = 8;
}

/**
 * @brief Move the car sprite by updating the position of the car object.
 *
 */
void CarSprite::move()
{
    carObj.move(keyAction);
    setPosition(carObj.getX(), carObj.getY());
    this->x = carObj.getX();
    this->y = carObj.getY();
}

/**
 * @brief Check if the car sprite is colliding with another sprite.
 *
 * @param other
 * @return true
 * @return false
 */
void CarSprite::getPushed(float opXV, float opYV)
{
    this->carObj.getPushed(opXV, opYV);
    timeSinceCollision.restart();
}

/**
 * @brief Push the car sprite by updating the velocity of the car object.
 *
 * @param opXV
 * @param opYV
 */
void CarSprite::push(float opXV, float opYV)
{
    this->carObj.push(opXV, opYV);
    timeSinceCollision.restart();
}

/**
 * @brief Reset the car sprite to its original position and texture.
 *
 */
void CarSprite::resetCar()
{
    setPosition(carObj.getStartX(), carObj.getStartY());
    setTexture(textures[initialTextureCode - 1]);
    carObj.reset();
    carObj.resetBaseStats();
    reversed = 0;
}

/**
 * @brief Nomalize the string to lower case.
 *
 * @param str
 * @return std::string
 */
std::string CarSprite::toLowerCase(const std::string &str)
{
    std::string result(str);
    std::transform(str.begin(), str.end(), result.begin(), [](unsigned char c)
                   { return std::tolower(c); });
    return result;
}

/**
 * @brief Add explosion effect to the car sprite.
 *
 */
void CarSprite::explosion()
{
    getPushed(-2 * carObj.getXVelocity(), -2 * carObj.getYVelocity());
}

/**
 * @brief Check if the car sprite is colliding with another sprite. Compare overlapping pixels of the two sprites.
 * If there is two pixel from each sprite that overlap and neither of them are transparent, then there is a collision.
 * @param other
 * @return
 */
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

/**
 * @brief Clear effect of the item after a certain amount of time.
 *
 */
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

/**
 * @brief Apply effect of the item to the car sprite.
 *
 * @param time
 */
void CarSprite::usedItem(sf::Time time)
{
    activeItem = true;
    timeItem = time;
    activeItemClock.restart();
}

/**
 * @brief Add reverse steering effect to the car sprite.
 *
 */
void CarSprite::reverseSteering()
{
    reversed = true;
}

/**
 * @brief Stop the car.
 *
 */
void CarSprite::stop()
{
    carObj.stop();
}

/**
 * @brief Set the position of the car sprite.
 *
 * @param x
 * @param y
 */
void CarSprite::setPos(float x, float y)
{
    this->x = x;
    this->y = y;
    carObj.setX(x);
    carObj.setY(y);
}
