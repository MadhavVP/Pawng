#pragma once
#include <sdl/SDL.h>
#include <sdl/SDL_image.h>
#include <headers/Entity.hpp>

class RenderWindow {
    public: 
        RenderWindow(const char *title, int w, int h);
        SDL_Texture *loadTexture(const char *fp);
        void cleanup();
        void clear();
        void render(Entity &entity);
        void display();
        SDL_Renderer *rend;
        SDL_Window *window;
    private:
};