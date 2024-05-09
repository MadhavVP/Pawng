#include "headers/Vector.hpp"

Vector::Vector(float speedX, float speedY) {
    this->speedX = speedX;
    this->speedY = speedY;
}

void Vector::changeX(float multiplier) {
    speedX = speedX * multiplier;
}

void Vector::changeY(float multiplier) {
    speedY = speedY * multiplier;        
}

float Vector::getX() {
    return speedX;
}

float Vector::getY() {
    return speedY;
}