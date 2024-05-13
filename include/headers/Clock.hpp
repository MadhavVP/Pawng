#pragma once
#include <sdl/SDL.h>

class Clock {
    public:
        Clock();
        float getDT();
        void update();
        void reset();
    private:
        Uint64 startMs;
        Uint64 elapsedMs;
        float DT;
};