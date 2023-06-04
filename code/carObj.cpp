/**
 * @file carObj.cpp
 * @author Binh Vuong Le Duc, Filip Ryniewicz, Cieśla Miłosz
 * @brief Class that represents the car object, stores the position, velocity, acceleration, and the points of the car
 * @date 2023-06-03
 */
#include "carObj.hpp"

/**
 * @brief Construct a new CarObj:: Car object
 * 
 * @param startX Starting position of the car on the x-axis
 * @param startY Starting position of the car on the y-axis
 */
CarObj::CarObj(float startX, float startY) : startX(startX), startY(startY)
{
    this->x = this->startX;
    this->y = this->startY;
}

/**
 * @brief Set the position of the car on the x-axis
 * 
 * @param x New position of the car on the x-axis
 */
void CarObj::setX(float x)
{
    this->x = x;
}

/**
 * @brief Get the position of the car on the x-axis
 * 
 * @return float Current position of the car on the x-axis
 */
float CarObj::getX() const
{
    return x;
}

/**
 * @brief Set the position of the car on the y-axis
 * 
 * @param y New position of the car on the y-axis
 */
void CarObj::setY(float y)
{
    this->y = y;
}

/**
 * @brief Get the position of the car on the y-axis
 * 
 * @return float Current position of the car on the y-axis
 */
float CarObj::getY() const
{
    return y;
}

/**
 * @brief Get the starting position of the car on the x-axis (Initial position). For reseting the car
 * 
 * @return float Starting position of the car on the x-axis
 */
float CarObj::getStartX() const
{
    return startX;
}

/**
 * @brief Get the starting position of the car on the y-axis (Initial position). For reseting the car
 * 
 * @return float Starting position of the car on the y-axis
 */
float CarObj::getStartY() const
{
    return startY;
}

/**
 * @brief Set the velocity of the car on the x-axis
 * 
 * @param xVelocity New velocity of the car on the x-axis
 */
float CarObj::getXVelocity()
{
    return xVelocity;
}

/**
 * @brief Set the velocity of the car on the y-axis
 * 
 * @param yVelocity New velocity of the car on the y-axis
 */
float CarObj::getYVelocity()
{
    return yVelocity;
}

/**
 * @brief Set points for the car
 * 
 * @param inc 
 */
void CarObj::setPoint(int inc)
{
    points += inc;
}

/**
 * @brief Get the points of the car
 * 
 * @return unsigned int Points of the car
 */
unsigned int CarObj::getPoint()
{
    return points;
}

/**
 * @brief Set the max speed of the car
 * 
 * @param newMax New max speed of the car
 */
void CarObj::setMaxSpeed(float newMax)
{
    maxSpeed = newMax;
}

/**
 * @brief Set the acceleration of the car
 * 
 * @param newAcc New acceleration of the car
 */
void CarObj::setAcceleration(float newAcc)
{
    acceleration = newAcc;
}

/**
 * @brief Reset the base stats of the car including acceleration and max speed
 */
void CarObj::resetBaseStats()
{
    acceleration = baseAcceleration;
    maxSpeed = baseMaxSpeed;
}

/**
 * @brief Set the Velocity for the car
 * Update the velocity of the car based on the acceleration and the direction
 * @param xAcc Acceleration on the x-axis
 * @param yAcc Acceleration on the y-axis
 */
void CarObj::setVelocity(TriStateBool xAcc, TriStateBool yAcc)
{
    if (xVelocity + acceleration < maxSpeed && xAcc == 2) // Right
        xVelocity += acceleration;
    else if (xVelocity - acceleration > -maxSpeed && xAcc == 0) // Left
        xVelocity -= acceleration;
    else if (xAcc == 1 && xVelocity > 0)
        xVelocity -= acceleration / 2;
    else if (xAcc == 1 && xVelocity < 0)
        xVelocity += acceleration / 2;

    if (yVelocity + acceleration < maxSpeed && yAcc == 2) // Up
        yVelocity += acceleration;
    else if (yVelocity - acceleration > -maxSpeed && yAcc == 0) // Down
        yVelocity -= acceleration;
    else if (yAcc == 1 && yVelocity > 0)
        yVelocity -= acceleration / 2;
    else if (yAcc == 1 && yVelocity < 0)
        yVelocity += acceleration / 2;
    if (std::abs(xVelocity) < 0.1)
        xVelocity = 0;
    if (std::abs(yVelocity) < 0.1)
        yVelocity = 0;
    if (acceleration == 0) // Reset acceleration after preventing gainning speed from pushing or getting pushed
        acceleration = baseAcceleration;
}

/**
 * @brief Reset the velocity of the car 
 */
void CarObj::resetVelocity()
{
    xVelocity = 0;
    yVelocity = 0;
}

/**
 * @brief Reset the position of the car
 */

void CarObj::resetPosition()
{
    setX(startX);
    setY(startY);
}

/**
 * @brief Reset the car
 * Reset the velocity and the position of the car
 */
void CarObj::reset()
{
    resetVelocity();
    resetPosition();
}

/**
 * @brief Move the car. Update the position of the car based on the velocity
 * @param opsCode Code of the direction
 */
void CarObj::move(int opsCode)
{
    if (opsCode == 0)
        setVelocity(Zero, False);
    else if (opsCode == 1)
        setVelocity(True, False);
    else if (opsCode == 2)
        setVelocity(True, Zero);
    else if (opsCode == 3)
        setVelocity(True, True);
    else if (opsCode == 4)
        setVelocity(Zero, True);
    else if (opsCode == 5)
        setVelocity(False, True);
    else if (opsCode == 6)
        setVelocity(False, Zero);
    else if (opsCode == 7)
        setVelocity(False, False);
    else if (opsCode == 8)
        setVelocity(Zero, Zero);

    setX(x + xVelocity);
    setY(y + yVelocity);
}

/**
 * @brief Change this car properties when it gets pushed by other object
 * 
 * @param opXV Velocity of other object that pushes this car on the x-axis
 * @param opYV Velocity of other object that pushes this car on the y-axis
 */
void CarObj::getPushed(float opXV, float opYV)
{
    this->xVelocity += 2 * opXV;
    this->yVelocity += 2 * opYV;
    this->capVelocity(3);
    acceleration = 0; // Prevent gainning speed from getting pushed
}

/**
 * @brief Change this car properties when it pushes other object
 * 
 * @param opXV Velocity of other object that gets pushed by this car on the x-axis
 * @param opYV Velocity of other object that gets pushed by this car on the y-axis
 */
void CarObj::push(float opXV, float opYV)
{
    this->xVelocity -= opXV / 2;
    this->yVelocity -= opYV / 2;
    this->capVelocity(3);
    acceleration = 0; // Prevent gainning speed from pushing
}

/**
 * @brief Ensure that the velocity of the car does not exceed the limit 
 * 
 * @param multiplier Expansion of the limit
 */

void CarObj::capVelocity(float multiplier)
{
    if (std::abs(this->xVelocity) > std::abs(multiplier * maxSpeed))
    {
        if (this->xVelocity > 0)
            this->xVelocity = multiplier * maxSpeed;
        else
            this->xVelocity = multiplier * (-maxSpeed);
    }

    if (std::abs(this->yVelocity) > std::abs(multiplier * maxSpeed))
    {
        if (this->yVelocity > 0)
            this->yVelocity = multiplier * maxSpeed;
        else
            this->yVelocity = multiplier * (-maxSpeed);
    }
}

/**
 * @brief Stop the car by setting the velocity to 0
 * 
 */
void CarObj::stop()
{
    xVelocity = 0;
    yVelocity = 0;
}