#include <headers/Clock.hpp>
#include <sdl/SDL.h>

Clock::Clock() {
    startMs = SDL_GetTicks64();
    DT = 0.0f;
    elapsedMs = 0;
}

float Clock::getDT() {return DT;}
void Clock::reset() {
    startMs = SDL_GetTicks64();
    elapsedMs = 0;
    DT = 0.0f;
}
void Clock::update() {
    elapsedMs = SDL_GetTicks64();
    DT = (elapsedMs - startMs) * 0.01f;
}