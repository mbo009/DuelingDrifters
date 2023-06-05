#include "item.hpp"

/**
 * @brief Construct a new Item:: Item object
 * 
 * @param x 
 * @param y 
 * @param duration effect duration
 * @param useOnSelf is the item used on self or on opponent
 * @param acc acceleration change
 * @param maxSpeed max speed change
 * @param reverse reverse steering
 * @param explode get exploded
 * @param stun get stunned
 * @param swap swap position with opponent
 */
Item::Item(float x, float y,
           sf::Time duration, bool useOnSelf, float acc,
           float maxSpeed, bool reverse, bool explode,
           bool stun, bool swap) : xPos(x), yPos(y), duration(duration),
                                   useOnSelf(useOnSelf), changeAcc(acc),
                                   changeMaxSpeed(maxSpeed), reverseSteering(reverse),
                                   explode(explode), stun(stun), swap(swap)
{
    setPosition(x, y);
}

/**
 * @brief return position of item in x-axis
 * 
 * @return float 
 */
float Item::getX() const
{
    return xPos;
}

/**
 * @brief set position of item in x-axis
 * 
 * @param x 
 */
void Item::setX(float x)
{
    xPos = x;
}

/**
 * @brief return position of item in y-axis
 * 
 * @return float 
 */
float Item::getY() const
{
    return yPos;
}

/**
 * @brief set position of item in y-axis
 * 
 * @param y 
 */
void Item::setY(float y)
{
    yPos = y;
}

/**
 * @brief set position of item
 * 
 * @param x 
 * @param y 
 */
void Item::setPos(float x, float y)
{
    setX(x);
    setY(y);
    setPosition(x, y);
}

/**
 * @brief check if item carry explosion effect
 * 
 * @return boolean
 */
bool Item::getExplode() const
{
    return explode;
}

/**
 * @brief check if item carry reverse steering effect
 * 
 * @return true 
 * @return false 
 */
bool Item::getReverseSteering() const
{
    return reverseSteering;
}

/**
 * @brief get max speed change effect that item carry
 * 
 * @return float 
 */
float Item::getMaxSpeed() const
{
    return changeMaxSpeed;
}

/**
 * @brief get acceleration change effect that item carry
 * 
 * @return float 
 */
float Item::getAcceleration() const
{
    return changeAcc;
}

/**
 * @brief check if item is used on self or on opponent
 * 
 * @return true 
 * @return false 
 */
bool Item::getUseOnSelf() const
{
    return useOnSelf;
}

/**
 * @brief get duration of item effect
 * 
 * @return sf::Time 
 */
sf::Time Item::getDuration() const
{
    return duration;
}

/**
 * @brief check if item carry stun effect
 * 
 * @return true 
 * @return false 
 */
bool Item::getStun() const
{
    return stun;
}

/**
 * @brief check if item carry swap effect
 * 
 * @return true 
 * @return false 
 */
bool Item::getSwap() const
{
    return swap;
}

/**
 * @brief get texture of item
 * 
 * @return sf::Texture& 
 */
sf::Texture &Item::getTexture()
{
    return texture;
}

/**
 * @brief Construct a new Speed Up object. Inherit from Item.
 * Increase acceleration and max speed.
 * @param x 
 * @param y 
 * @param duration 
 */
SpeedUp::SpeedUp(float x, float y, sf::Time duration) : Item(x, y, duration)
{
    changeAcc = 1.5;
    changeMaxSpeed = 9;
    texture.loadFromFile(ASSET_PATHS_HPP::SPEED_ITM);
    setTexture(texture);
}

/**
 * @brief Construct a new Opponent Slow object. Inherit from Item.
 * Decrease acceleration and max speed of opponent.
 * @param x 
 * @param y 
 * @param duration 
 */
OpponentSlow::OpponentSlow(float x, float y, sf::Time duration) : Item(x, y, duration)
{
    useOnSelf = 0;
    changeAcc = 0.1;
    changeMaxSpeed = 3;
    texture.loadFromFile(ASSET_PATHS_HPP::OPP_SLOW_ITM);
    setTexture(texture);
}

/**
 * @brief Construct a new Bomb object. Inherit from Item.
 * Make car that hit this item bounce back.
 * @param x 
 * @param y 
 * @param duration 
 */
Bomb::Bomb(float x, float y, sf::Time duration) : Item(x, y, duration)
{
    explode = 1;
    texture.loadFromFile(ASSET_PATHS_HPP::BOMB_ITM);
    setTexture(texture);
}

/**
 * @brief Construct a new Dash object. Inherit from Item.
 * Increase acceleration and max speed at very high rate in short time.
 * @param x 
 * @param y 
 * @param duration 
 */
Dash::Dash(float x, float y, sf::Time duration) : Item(x, y, duration)
{
    changeAcc = 2;
    changeMaxSpeed = 20;
    texture.loadFromFile(ASSET_PATHS_HPP::DASH_ITM);
    setTexture(texture);
}

/**
 * @brief Construct a new Reverse object. Inherit from Item.
 * Reverse steering of opponent. Left turn become right turn and vice versa.
 * @param x 
 * @param y 
 * @param duration 
 */
Reverse::Reverse(float x, float y, sf::Time duration) : Item(x, y, duration)
{
    useOnSelf = 0;
    reverseSteering = 1;
    texture.loadFromFile(ASSET_PATHS_HPP::REVERSE_ITM);
    setTexture(texture);
}

/**
 * @brief Construct a new Stun object. Inherit from Item.
 * Make opponent car unable to move for a short time.
 * @param x 
 * @param y 
 * @param duration 
 */
Stun::Stun(float x, float y, sf::Time duration) : Item(x, y, duration)
{
    useOnSelf = 0;
    stun = 1;
    texture.loadFromFile(ASSET_PATHS_HPP::STUN_ITM);
    setTexture(texture);
}

/**
 * @brief Construct a new Swap object. Inherit from Item.
 * Swap position with opponent on the map.
 * @param x 
 * @param y 
 * @param duration 
 */
Swap::Swap(float x, float y, sf::Time duration) : Item(x, y, duration)
{
    useOnSelf = 0;
    swap = 1;
    texture.loadFromFile(ASSET_PATHS_HPP::SWAP_ITM);
    setTexture(texture);
}

/**
 * @brief Construct a new Flag object. Inherit from Item.
 * Just a flag. Whoever hold this flag when time is up will win.
 * @param x 
 * @param y 
 * @param duration 
 */
Flag::Flag(float x, float y, sf::Time duration) : Item(x, y, duration)
{
    useOnSelf = 0;
    texture.loadFromFile(ASSET_PATHS_HPP::FLAG_ITM);
    setTexture(texture);
}