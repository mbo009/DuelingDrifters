#ifndef CAROBJ_HPP
#define CAROBJ_HPP

#include <cmath>
enum TriStateBool
{
    False, // -
    Zero,  // 0
    True   // +
};

class CarObj
{
public:
    CarObj(float startX = 0, float startY = 0);
    void setX(float x);
    float getX() const;
    void setY(float y);
    float getY() const;
    void setPosition(float x, float y);
    float getStartX() const;
    float getStartY() const;
    float getXVelocity();
    float getYVelocity();
    void setPoint(int inc = 1);
    unsigned int getPoint();
    void setMaxSpeed(float newMax);
    void setAcceleration(float newMax);
    void resetBaseStats();
    void setVelocity(TriStateBool xAcc, TriStateBool yAcc);
    void resetVelocity();
    void resetPosition();
    void reset();
    void move(int code);
    void getPushed(float opXV, float opYV);
    void push(float opXV, float opYV);
    void stop();

private:
    void capVelocity(float multiplier);
    unsigned int points = 0;
    float startX;
    float startY;
    float x;
    float y;
    float rotation = 0;
    float xVelocity = 0;
    float yVelocity = 0;
    float maxSpeed = 6;
    float baseMaxSpeed = 6;
    float acceleration = 0.2;
    float baseAcceleration = 0.2;
};

#endif