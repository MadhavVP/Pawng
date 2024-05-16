#include <sdl/SDL.h>
#include <sdl/SDL_image.h>
#include <iostream>

#include <headers/RenderWindow.hpp>

RenderWindow::RenderWindow(const char * title, int w, int h) {
    window = NULL;
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
            std::cout << "Window Failed: " << SDL_GetError() << std::endl;
    }
    rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

}

RenderWindow::RenderWindow(const char * title, int w, int h, Uint32 flags) {
    window = NULL;
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | flags);
    if (window == NULL) {
            std::cout << "Window Failed: " << SDL_GetError() << std::endl;
    }
    rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

}

SDL_Texture *RenderWindow::loadTexture(const char *fp) {
    SDL_Texture *tex = NULL;
    tex = IMG_LoadTexture(rend, fp);
    if (tex == NULL) {
        std::cout << "Texture load Failed: " << SDL_GetError() << std::endl;
    }
    return tex;
}

// Call this function before ending the program, it makes sure SDL properly closes
void RenderWindow::cleanup() {
    SDL_DestroyWindow(window);
}

// This function cleans up any previous renders before displaying any new renders (call it every frame)
void RenderWindow::clear() {
    SDL_RenderClear(rend);
}

// This function should be called whenever rendering something to the screen
void RenderWindow::render(Entity &entity) {
    SDL_Rect src;
    src.x = entity.getCurrentFrame().x;
    src.y = entity.getCurrentFrame().y;
    src.w = entity.getCurrentFrame().w;
    src.h = entity.getCurrentFrame().h;
    SDL_Rect dst;
    dst.x = entity.getX();
    dst.y = entity.getY();
    dst.w = entity.getCurrentFrame().w;
    dst.h = entity.getCurrentFrame().h;
    SDL_RenderCopy(rend, entity.getTex(), &src, &dst);
}

// This function actually presents whatever has been rendered
void RenderWindow::display() {
    SDL_RenderPresent(rend);
}