#include "carObj.hpp"

CarObj::CarObj(float x, float y) : x(x), y(y)
{
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