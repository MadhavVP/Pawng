#pragma once

class Vector {
    public:
        Vector(float speedX, float speedY);
        void changeX(float multiplier);
        void changeY(float multiplier);
        float getX();
        float getY();
    private:
        float speedX;
        float speedY;
};
