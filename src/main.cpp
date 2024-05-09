#include <sdl/SDL.h>
#include <sdl/SDL_image.h>
#include <iostream>
#include <time.h>
#include <math.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Vector.hpp"

int main(int argc, char* argv[]) {
    
    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        std::cout << "SDL FAILED: " << SDL_GetError() << std::endl;
    }
    if (!(IMG_Init(IMG_INIT_PNG))) {
        std::cout << "IMG_Init FAILED: " << SDL_GetError() << std::endl;
    }
    int gameWidth = 1280;
    int gameHeight = 720;
    RenderWindow window("Game v1.0", gameWidth, gameHeight);

    SDL_Texture *platformTex = window.loadTexture("res/gfx/BasePlateRMBG.png");
    SDL_Texture *ballTex = window.loadTexture("res/gfx/smallball.png");
    SDL_Texture *playButtonTex = window.loadTexture("res/gfx/playButton.png");
    
    int playWidth = 200;
    int playHeight = 50;

    srand(time(NULL));
    int windowWidth = 0;
    int windowHeight = 0;
    SDL_GetWindowSize(window.window, &windowWidth, &windowHeight);
    //printf("Width: %d\nHeight: %d\n", windowWidth, windowHeight);

    int platformWidth = 192;
    int platformHeight = 40;
    Entity platform(10, windowHeight - (windowHeight / 5), platformWidth, platformHeight, platformTex);

    int ballWidth = 50;
    int ballHeight = ballWidth;
    Entity ball((rand() % (windowWidth)), 10, ballWidth, ballHeight, ballTex);
    int ballSpeedX = rand() % 100;
    int ballSpeedY = rand() % 100;
    long double totalSpeed = sqrt(((ballSpeedX ^ 2) + (ballSpeedY ^ 2)));
    Vector ballSpeed((0.08 * (ballSpeedX / totalSpeed)),(0.08 * (ballSpeedY / totalSpeed)));

    bool running = true;
    SDL_Event menuEvent;
    int mouseX = 0;
    int mouseY = 0;
    while (running)
    {
        SDL_GetWindowSize(window.window, &windowWidth, &windowHeight);
        int playX = (windowWidth / 2) - (playWidth / 2);
        int playY = (windowHeight / 2) - (playHeight / 2);
        Entity playButton(playX, playY, playWidth, playHeight, playButtonTex);
        while (SDL_PollEvent(&menuEvent))
        {
            switch (menuEvent.type)
            {
            case SDL_QUIT:
                running = false;
                window.cleanup();
                SDL_Quit();
                return 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&mouseX, &mouseY);
                //printf("MouseX: %d, MouseY: %d\nPlayX: %d, PlayY: %d\nWidth: %d, Height: %d\n----\n", mouseX, mouseY, playX, playY, playWidth, playHeight);
                if ((mouseX > playX) && (mouseX < (playX + playWidth)) && (mouseY > playY) && (mouseY < (playY + playHeight))) {
                    //printf("Pressed\n");
                    goto playing;
                }
                break;
            default:
                break;
            }
        }
        window.clear();
        window.render(playButton);
        window.display();
        
    }
    
    playing:
    bool playing = true;
    SDL_Event event;
    float platformSpeed = 50;
    int lenience = 5;
    while (playing)
    {
        SDL_GetWindowSize(window.window, &windowWidth, &windowHeight);
        if (ball.getX() <= 0)
        {
            ballSpeed.changeX(-1);
        }
        if (ball.getY() <= 0)
        {
            ballSpeed.changeY(-1);
        }
        if (ball.getX() >= windowWidth - ballWidth) {
            ballSpeed.changeX(-1);
        }
        if (ball.getY() >= windowHeight - ballHeight) {
            ballSpeed.changeY(-1);
        }
        if ((ball.getX() >= platform.getX()) && (ball.getX() <= (platform.getX() + platformWidth)) && (ball.getY() >= platform.getY()) /*&& (ball.getY() <= (platform.getY() + lenience))*/) {
            ballSpeed.changeY(-1);
        }
        ball.changeX(ballSpeed.getX());
        ball.changeY(ballSpeed.getY());
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                playing = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    playing = false;
                }
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    if (platform.getX() > 0) 
                        platform.changeX(-platformSpeed);
                }
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    if (platform.getX() < windowWidth - platformWidth) {
                        platform.changeX(platformSpeed);
                    }
                }
                break;
            default:
                break;
            }
        }

        window.clear();
        window.render(ball);
        window.render(platform);
        window.display();
        
    }
    
    leaving: 
    window.cleanup();
    SDL_Quit();
    return 0;
}