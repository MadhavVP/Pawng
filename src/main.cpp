#include <sdl/SDL.h>
#include <sdl/SDL_image.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <Windows.h>
 
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Vector.hpp"
#include "Clock.hpp"

int main(int argc, char* argv[]) {
    
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) > 0) {
        std::cout << "SDL FAILED: " << SDL_GetError() << std::endl;
    }
    if (!(IMG_Init(IMG_INIT_PNG))) {
        std::cout << "IMG_Init FAILED: " << SDL_GetError() << std::endl;
    }
    int gameWidth = 1280;
    int gameHeight = 720;
    RenderWindow window("Pawng", gameWidth, gameHeight);

    SDL_Texture *platformTex = window.loadTexture("res/gfx/BasePlateRMBG.png");
    SDL_Texture *ballTex = window.loadTexture("res/gfx/smallball.png");
    SDL_Texture *playButtonTex = window.loadTexture("res/gfx/playButton.png");
    SDL_Texture *quitButtonTex = window.loadTexture("res/gfx/quitButton.png");
    SDL_Texture *titleTex = window.loadTexture("res/gfx/titleImage.png");
    SDL_Texture *timerTex[] = {window.loadTexture("res/gfx/200x300pixel0.png"),
                               window.loadTexture("res/gfx/200x300pixel1.png"),
                               window.loadTexture("res/gfx/200x300pixel2.png"),
                               window.loadTexture("res/gfx/200x300pixel3.png"),
                               window.loadTexture("res/gfx/200x300pixel4.png"),
                               window.loadTexture("res/gfx/200x300pixel5.png")};
    
    int buttonWidth = 200;
    int buttonHeight = 50;
    int hoverButtonWidth = 220;
    int hoverButtonHeight = 55;

    int titleWidth = 600;
    int titleHeight = 153;

    int timerWidth = 200;
    int timerHeight = 300;

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
    Vector ballSpeed((0.05 * (ballSpeedX / totalSpeed)),(0.05 * (ballSpeedY / totalSpeed)));

    int titleX = (windowWidth / 2) - (titleWidth / 2);
    int titleY = (windowHeight / 4) - (titleHeight / 2);
    if (titleY < 0) {
        titleY = 0;
    }
    Entity title(titleX, titleY, titleWidth, titleHeight, titleTex);

    int titleSpeedX = 30 + (rand() % 70);
    int titleSpeedY = 30 + (rand() % 70);
    long double totalTitleSpeed = sqrt(((titleSpeedX ^ 2) + (titleSpeedY ^ 2)));
    Vector titleSpeed((0.007 * (titleSpeedX / totalTitleSpeed)),(0.007 * (titleSpeedY / totalTitleSpeed)));

    int timerX = (windowWidth / 2) - (timerWidth / 2);
    int timerY = (windowHeight / 4) - (timerHeight / 2);
    for (int i = 0; i < 6; i++)
    {
        SDL_SetTextureAlphaMod(timerTex[i], 200);
    }
    Entity timerNums[] = {Entity(timerX, timerY, timerWidth, timerHeight, timerTex[0]),
                          Entity(timerX, timerY, timerWidth, timerHeight, timerTex[1]),
                          Entity(timerX, timerY, timerWidth, timerHeight, timerTex[2]),
                          Entity(timerX, timerY, timerWidth, timerHeight, timerTex[3]),
                          Entity(timerX, timerY, timerWidth, timerHeight, timerTex[4]),
                          Entity(timerX, timerY, timerWidth, timerHeight, timerTex[5])};

    bool running = true;
    SDL_Event menuEvent;
    int mouseX = 0;
    int mouseY = 0;
    startscreen:
    Clock frameManager = Clock();
    while (running)
    {
        frameManager.update();
        if (frameManager.getDT() > (1 / 120.0f)) {
            //printf("%.5f\n", frameManager.getDT());
            frameManager.reset();
            SDL_GetWindowSize(window.window, &windowWidth, &windowHeight);

            int playX = (windowWidth / 2) - (buttonWidth / 2);
            int playY = (windowHeight / 2) - (buttonHeight / 2);
            Entity playButton(playX, playY, buttonWidth, buttonHeight, playButtonTex);

            int quitY = playY + 5 + buttonHeight;
            Entity quitButton(playX, quitY, buttonWidth, buttonHeight, quitButtonTex);

            int hoverPlayX = (windowWidth / 2) - (hoverButtonWidth / 2);
            int hoverPlayY = (windowHeight / 2) - (hoverButtonHeight / 2);
            int hoverQuitY = playY + hoverButtonHeight;

            if (title.getX() <= 0)
            {
                titleSpeed.changeX(-1);
                title.setX(0);
            }
            if (title.getY() <= 0)
            {
                titleSpeed.changeY(-1);
                title.setY(0);
            }
            if (title.getX() >= windowWidth - titleWidth) {
                titleSpeed.changeX(-1);
                title.setX(windowWidth - titleWidth);
            }
            if (title.getY() >= playY - titleHeight) {
                titleSpeed.changeY(-1);
                title.setY(playY- titleHeight);
            }
            title.changeX(titleSpeed.getX());
            //printf("TitleX: %.2f TitleY: %.2f SpeedX: %.2f SpeedY: %.2f\n", title.getX(), title.getY(), titleSpeed.getX(), titleSpeed.getY());
            title.changeY(titleSpeed.getY());
            SDL_GetMouseState(&mouseX, &mouseY);
                    //printf("MouseX: %d, MouseY: %d\nPlayX: %d, PlayY: %d\nWidth: %d, Height: %d\n----\n", mouseX, mouseY, playX, playY, buttonWidth, buttonHeight);
                    if ((mouseX > playX) && (mouseX < (playX + buttonWidth)) && (mouseY > playY) && (mouseY < (playY + buttonHeight))) {
                        playButton.setX(hoverPlayX);
                        playButton.setY(hoverPlayY);
                        playButton.setWidth(hoverButtonWidth);
                        playButton.setHeight(hoverButtonHeight);
                    }
                    else if ((mouseX > playX) && (mouseX < (playX + buttonWidth)) && (mouseY > quitY) && (mouseY < (quitY + buttonHeight))) {
                        quitButton.setX(hoverPlayX);
                        quitButton.setY(hoverQuitY);
                        quitButton.setWidth(hoverButtonWidth);
                        quitButton.setHeight(hoverButtonHeight);
                    }
                    else {
                        playButton = {(float) playX,(float) playY,(float) buttonWidth,(float) buttonHeight, playButtonTex};
                        quitButton = {(float) playX,(float) quitY,(float) buttonWidth,(float) buttonHeight, quitButtonTex};
                    }
            while (SDL_PollEvent(&menuEvent))
            {
                switch (menuEvent.type)
                {
                case SDL_KEYDOWN:
                    if (menuEvent.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                        window.cleanup();
                        SDL_Quit();
                        return 0;
                        break;
                    }
                case SDL_QUIT:
                    running = false;
                    window.cleanup();
                    SDL_Quit();
                    return 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mouseX, &mouseY);
                    //printf("MouseX: %d, MouseY: %d\nPlayX: %d, PlayY: %d\nWidth: %d, Height: %d\n----\n", mouseX, mouseY, playX, playY, buttonWidth, buttonHeight);
                    if ((mouseX > playX) && (mouseX < (playX + buttonWidth)) && (mouseY > playY) && (mouseY < (playY + buttonHeight))) {
                        //printf("Pressed\n");
                        goto playing;
                    }
                    if ((mouseX > playX) && (mouseX < (playX + buttonWidth)) && (mouseY > quitY) && (mouseY < (quitY + buttonHeight))) {
                        running = false;
                        window.cleanup();
                        SDL_Quit();
                        return 0;
                    }
                    break;
                default:
                    break;
                }
            }
            window.clear();
            window.render(title);
            window.render(playButton);
            window.render(quitButton);
            window.display();
        }
    }
    
    playing:
    bool playing = true;
    SDL_Event event;
    float platformSpeed = 50;
    int lenience = 3;
    SDL_GetWindowSize(window.window, &windowWidth, &windowHeight);
    /*while (timer5S.getSecs() < 6)
    {
        timer5S.update(SDL_GetTicks64());
        window.clear();
        if (timer5S.getSecs() >= 5) {
            window.render(timerNums[0]);
        }
        else if (timer5S.getSecs() >= 4) {
            window.render(timerNums[1]);
        }
        else if (timer5S.getSecs() >= 3) {
            window.render(timerNums[2]);
        }
        else if (timer5S.getSecs() >= 2) {
            window.render(timerNums[3]);
        }
        else if (timer5S.getSecs() >= 1) {
            window.render(timerNums[4]);
        }
        else if (timer5S.getSecs() >= 0) {
            window.render(timerNums[5]);
        }
        window.render(ball);
        window.render(platform);
        window.display();
    }*/

    frameManager.reset();
    Clock timer5s = Clock();
    int timerIterator = 0;
    while (playing)
    {   
        timer5s.reset();
        while (timerIterator < 6) {
            if (timer5s.getDT() > 8.5f) {
                timer5s.reset();
                timerIterator++;
            }
            window.clear();
            window.render(timerNums[5 - timerIterator]);
            window.render(ball);
            window.render(platform);
            window.display();
            timer5s.update();
        }
        
        frameManager.update();
        if (frameManager.getDT() > (1 / 240.0f)) {
            frameManager.reset();
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
                ball.setX(windowWidth - ballWidth);
            }
            if (ball.getY() >= windowHeight - ballHeight) {
                ballSpeed.changeY(-1);
                ball.setY(windowHeight - ballHeight);
            }
            if ((ball.getX() >= platform.getX()) && (ball.getX() <= (platform.getX() + platformWidth)) && (ball.getY() >= platform.getY()) && (ball.getY() <= (platform.getY() + lenience))) {
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
                        goto startscreen;
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
        
    }
    
    leaving: 
    window.cleanup();
    SDL_Quit();
    return 0;
}