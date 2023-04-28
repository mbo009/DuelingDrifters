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
    CarObj(float x = 0, float y = 0);
    void setX(float x);
    void setY(float y);
    float getX() const;
    float getY() const;
    void move(int code);
    void restartPosition();
    void changeVelocity(TriStateBool xAcc, TriStateBool yAcc);
    float getXVelocity();
    float getYVelocity();
    void scoredPoint();
    float getStartX() const;
    float getStartY() const;
    unsigned int getPoints();
    void getPushed(float opXV, float opYV);
    void push(float opXV, float opYV);
    void restartVelocity();
    void restart();

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
    float acceleration = 0.2;
};

#endif