#pragma once
#include <sdl/SDL.h>

class Clock {
    public:
        Clock();
        float getDT();
        void update();
        void reset();
        void print();
        int getSecOnes();
        int getSecTens();
        int getMinOnes();
        int getMinTens();
        int getHrOnes();
        int getHrTens();
    private:
        Uint64 startMs;
        Uint64 elapsedMs;
        Uint64 curMs;
        int secs;
        int mins;
        int hrs;
        float DT;
};