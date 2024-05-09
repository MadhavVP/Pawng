#pragma once

class Vector
{
private:
    float speedX;
    float speedY;
public:
    Vector(float speedX, float speedY);
    void changeX(float multiplier);
    void changeY(float multiplier);
    float getX();
    float getY();
};
