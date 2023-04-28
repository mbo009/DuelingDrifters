#include "carObj.hpp"

CarObj::CarObj(float x, float y) : startX(x), startY(y)
{
    x = startX;
    y = startY;
}

void CarObj::setX(float x)
{
    this->x = x;
}

void CarObj::setY(float y)
{
    this->y = y;
}

float CarObj::getX() const
{
    return x;
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

void CarObj::restartVelocity()
{
    xVelocity = 0;
    yVelocity = 0;
}

void CarObj::restartPosition()
{
    setX(startX);
    setY(startY);
}

void CarObj::restart()
{
    restartVelocity();
    restartPosition();
}

void CarObj::move(int opsCode)
{
    if (opsCode == 0)
        changeVelocity(Zero, False);
    else if (opsCode == 1)
        changeVelocity(True, False);
    else if (opsCode == 2)
        changeVelocity(True, Zero);
    else if (opsCode == 3)
        changeVelocity(True, True);
    else if (opsCode == 4)
        changeVelocity(Zero, True);
    else if (opsCode == 5)
        changeVelocity(False, True);
    else if (opsCode == 6)
        changeVelocity(False, Zero);
    else if (opsCode == 7)
        changeVelocity(False, False);
    else if (opsCode == 8)
        changeVelocity(Zero, Zero);

    setX(x + xVelocity);
    setY(y + yVelocity);
}

void CarObj::scoredPoint()
{
    points++;
}

void CarObj::changeVelocity(TriStateBool xAcc, TriStateBool yAcc)
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
}

float CarObj::getXVelocity()
{
    return xVelocity;
}

float CarObj::getYVelocity()
{
    return yVelocity;
}

unsigned int CarObj::getPoints()
{
    return points;
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

void CarObj::getPushed(float opXV, float opYV)
{
    this->xVelocity += 2 * opXV;
    this->yVelocity += 2 * opYV;
    this->capVelocity(2);
}

void CarObj::push(float opXV, float opYV)
{
    this->xVelocity -= opXV / 2;
    this->yVelocity -= opYV / 2;
    this->capVelocity(2);
}