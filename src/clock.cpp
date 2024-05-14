#include <headers/Clock.hpp>
#include <sdl/SDL.h>
#include <iostream>

Clock::Clock() {
    startMs = SDL_GetTicks64();
    DT = 0.0f;
    elapsedMs = 0;
    curMs = 0;
    secs = 0;
    mins = 0;
    hrs = 0;
}

float Clock::getDT() {return DT;}
void Clock::reset() {
    startMs = SDL_GetTicks64();
    elapsedMs = 0;
    DT = 0.0f;
    curMs = 0;
    secs = 0;
    mins = 0;
    hrs = 0;
}
void Clock::update() {
    elapsedMs = SDL_GetTicks64();
    DT = (elapsedMs - startMs) * 0.001f;
    if ((elapsedMs - curMs) * 0.001f >= 1.0f) {
        secs++;
        curMs = elapsedMs;
    }
    if (secs == 60) {
        mins++;
        secs = 0;
    }
    if (mins == 60) {
        hrs++;
        mins = 0;
    }
}

void Clock::print() {
    printf("%d:%d:%d\n", hrs, mins, secs);
}

int Clock::getSecOnes() {
    return secs % 10;
}

int Clock::getSecTens() {
    if (secs < 10) {
        return 0;
    }
    return (secs - getSecOnes()) / 10;
}

int Clock::getMinOnes() {
    return mins % 10;
}

int Clock::getMinTens() {
    if (mins < 10) {
        return 0;
    }
    return (mins - getMinOnes()) / 10;
}

int Clock::getHrOnes() {
    return hrs % 10;
}

int Clock::getHrTens() {
    if (hrs < 10) {
        return 0;
    }
    return (hrs - getHrOnes()) / 10;
}