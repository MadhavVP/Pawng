#include "headers/Entity.hpp"

Entity::Entity(float x, float y, float w, float h, SDL_Texture *tex)
:x(x), y(y), tex(tex), w(w), h(h)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = w;
    currentFrame.h = h;
}

float Entity::getX() {return x;}
float Entity::getY() {return y;}
void Entity::changeX(float inc) {x += inc;}
void Entity::changeY(float inc) {y += inc;}
float Entity::getWidth() {return w;}
SDL_Texture* Entity::getTex() {return tex;}
SDL_Rect Entity::getCurrentFrame() {return currentFrame;}