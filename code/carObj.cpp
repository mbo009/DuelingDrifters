#include "carObj.hpp"

#include <iostream>

CarObj::CarObj(float startX, float startY) : startX(startX), startY(startY)
{
    this->x = this->startX;
    this->y = this->startY;
}

void CarObj::setX(float x)
{
    this->x = x;
}

float CarObj::getX() const
{
    return x;
}

void CarObj::setY(float y)
{
    this->y = y;
}

float CarObj::getY() const
{
    return y;
}

float CarObj::getStartX() const
{
    return startX;
}

float CarObj::getStartY() const
{
    return startY;
}

float CarObj::getXVelocity()
{
    return xVelocity;
}

float CarObj::getYVelocity()
{
    return yVelocity;
}

void CarObj::setPoint(int inc)
{
    points += inc;
}

unsigned int CarObj::getPoint()
{
    return points;
}

void CarObj::setMaxSpeed(float newMax)
{
    maxSpeed = newMax;
}

void CarObj::setAcceleration(float newAcc)
{
    acceleration = newAcc;
}

void CarObj::resetBaseStats()
{
    acceleration = baseAcceleration;
    maxSpeed = baseMaxSpeed;
}

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

void CarObj::resetVelocity()
{
    xVelocity = 0;
    yVelocity = 0;
}

void CarObj::resetPosition()
{
    setX(startX);
    setY(startY);
}

void CarObj::reset()
{
    resetVelocity();
    resetPosition();
}

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

void CarObj::getPushed(float opXV, float opYV)
{
    this->xVelocity += 2 * opXV;
    this->yVelocity += 2 * opYV;
    this->capVelocity(3);
    acceleration = 0; // Prevent gainning speed from getting pushed
}

void CarObj::push(float opXV, float opYV)
{
    this->xVelocity -= opXV / 2;
    this->yVelocity -= opYV / 2;
    this->capVelocity(3);
    acceleration = 0; // Prevent gainning speed from pushing
}

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

void CarObj::stop()
{
    xVelocity = 0;
    yVelocity = 0;
}