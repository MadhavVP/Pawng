#pragma once
#include <sdl/SDL.h>
#include <sdl/SDL_image.h>

class Entity {
    public:
        Entity(float x, float y, float w, float h, SDL_Texture *tex);
        float getX();
        float getY();
        float getWidth();
        void changeX(float inc);
        void changeY(float inc);
        void setX(float set);
        void setY(float set);
        void setWidth(float set);
        void setHeight(float set);
        SDL_Texture *getTex();
        SDL_Rect getCurrentFrame();
    private:
        float x, y, w, h;
        SDL_Rect currentFrame;
        SDL_Texture *tex;
};