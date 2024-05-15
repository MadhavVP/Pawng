#include <sdl/SDL.h>
#include <sdl/SDL_image.h>
#include <iostream>
#include <time.h>
#include <math.h>
 
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
                               window.loadTexture("res/gfx/200x300pixel3.png")};
    for (int i = 0; i < 4; i++)
    {
        SDL_SetTextureAlphaMod(timerTex[i], 150);
    }                           
    SDL_Texture *clockTex[] = {window.loadTexture("res/gfx/40x60pixel0.png"),
                               window.loadTexture("res/gfx/40x60pixel1.png"),
                               window.loadTexture("res/gfx/40x60pixel2.png"),
                               window.loadTexture("res/gfx/40x60pixel3.png"),
                               window.loadTexture("res/gfx/40x60pixel4.png"),
                               window.loadTexture("res/gfx/40x60pixel5.png"),
                               window.loadTexture("res/gfx/40x60pixel6.png"),
                               window.loadTexture("res/gfx/40x60pixel7.png"),
                               window.loadTexture("res/gfx/40x60pixel8.png"),
                               window.loadTexture("res/gfx/40x60pixel9.png"),
                               window.loadTexture("res/gfx/colon3dMed.png")};
    for (int i = 0; i <= 10; i++)
    {
        SDL_SetTextureAlphaMod(clockTex[i], 150);
    }  
    SDL_Texture *dotTex = window.loadTexture("res/gfx/pixelDot.png");
    SDL_Texture *obstacleTex = window.loadTexture("res/gfx/100x100square3.png");
    int buttonWidth = 200;
    int buttonHeight = 50;
    int hoverButtonWidth = 220;
    int hoverButtonHeight = 55;

    int titleWidth = 600;
    int titleHeight = 153;

    int timerWidth = 200;
    int timerHeight = 300;

    int clockWidth = 40;
    int clockHeight = 60;

    int obstacleWidth = 100;
    int obstacleHeight = obstacleWidth;

    srand(time(NULL));
    int windowWidth = 0;
    int windowHeight = 0;
    SDL_GetWindowSize(window.window, &windowWidth, &windowHeight);
    //printf("Width: %d\nHeight: %d\n", windowWidth, windowHeight);

    int platformWidth = 192;
    int platformHeight = 40;

    int ballWidth = 50;
    int ballHeight = ballWidth;

    int titleX = (windowWidth / 2) - (titleWidth / 2);
    int titleY = (windowHeight / 4) - (titleHeight / 2);
    if (titleY < 0) {
        titleY = 0;
    }
    Entity title(titleX, titleY, titleWidth, titleHeight, titleTex);

    int titleSpeedX = 30 + (rand() % 70);
    int titleSpeedY = 30 + (rand() % 70);
    long double totalTitleSpeed = sqrt(((titleSpeedX ^ 2) + (titleSpeedY ^ 2)));
    Vector titleSpeed((0.1 * (titleSpeedX / totalTitleSpeed)),(0.1 * (titleSpeedY / totalTitleSpeed)));

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
                    }
                    break;
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
    Entity platform(10, windowHeight - (windowHeight / 5), platformWidth, platformHeight, platformTex);

    Entity ball((rand() % (windowWidth)), 10, ballWidth, ballHeight, ballTex);
    int ballSpeedX = 50 + rand() % 50;
    int ballSpeedY = 50 + rand() % 50;
    long double totalSpeed = sqrt(((ballSpeedX ^ 2) + (ballSpeedY ^ 2)));
    Vector ballSpeed((0.3 * (ballSpeedX / totalSpeed)),(0.3 * (ballSpeedY / totalSpeed)));

    bool playing = true;
    bool first = true;
    SDL_Event event;
    float platformSpeed = 50;
    int lenience = 3;
    frameManager.reset();
    Clock timer5s = Clock();
    Clock gameClock = Clock();
    int timerIterator = 0;
    int secOnes = 0;
    int secTens = 0;
    int minOnes = 0;
    int minTens = 0;
    int hrOnes = 00;
    int hrTens = 0;
    int clockMidX = 0;
    int clockY = 5;
    int firstLevel = 10;
    const int numObstacles = 7;
    int obstacleNum = 0;
    bool obstacles[numObstacles] = {false};
    Entity *obstacleList[numObstacles] = {NULL};

    int speedLevels = 4;
    while (playing)
    {   
        timer5s.reset();
        while (timerIterator < 4) {
            SDL_GetWindowSize(window.window, &windowWidth, &windowHeight);
            int timerX = (windowWidth / 2) - (timerWidth / 2);
            int timerY = (windowHeight / 3) - (timerHeight / 2);
            Entity timerNum(timerX, timerY, timerWidth, timerHeight, timerTex[3 - timerIterator]);
            if (timer5s.getDT() > 1.0f) {
                timer5s.reset();
                timerIterator++;
            }
            window.clear();
            window.render(timerNum);
            window.render(ball);
            window.render(platform);
            window.display();
            timer5s.update();
        }
        
        if (first) {
            gameClock.reset();
            first = false;
        }
        frameManager.update();
        gameClock.update();
        //printf("Line 250\n");
        if (frameManager.getDT() > (1 / 240.0f)) {
            window.clear();
            frameManager.reset();
            //printf("Line 254\n");
            
            secOnes = gameClock.getSecOnes();
            secTens = gameClock.getSecTens();
            minOnes = gameClock.getMinOnes();
            minTens = gameClock.getMinTens();
            hrOnes = gameClock.getHrOnes();
            hrTens = gameClock.getHrTens();
            clockMidX = (windowWidth / 2) - (clockWidth / 2);
            //printf("Line 261\n");
            Entity timings[] = {Entity(clockMidX + (3 * clockWidth) + 3, clockY, clockWidth, clockHeight, clockTex[secOnes]),
                                Entity(clockMidX + (2 * clockWidth) + 3, clockY, clockWidth, clockHeight, clockTex[secTens]),
                                Entity(clockMidX + (1.5f * clockWidth) - 8.5f, clockY, clockWidth, clockHeight, clockTex[10]),
                                Entity(clockMidX + (0.5f * clockWidth), clockY, clockWidth, clockHeight, clockTex[minOnes]),
                                Entity(clockMidX - (0.5f  * clockWidth), clockY, clockWidth, clockHeight, clockTex[minTens]),
                                Entity(clockMidX - (1.5f * clockWidth) + 9, clockY, clockWidth, clockHeight, clockTex[10]),
                                Entity(clockMidX - (2 * clockWidth) - 3, clockY, clockWidth, clockHeight, clockTex[hrOnes]),
                                Entity(clockMidX - (3 * clockWidth) - 3, clockY, clockWidth, clockHeight, clockTex[hrTens])};
            
            SDL_GetWindowSize(window.window, &windowWidth, &windowHeight);
            //printf("Line 269\n");
            if ((gameClock.getDT() > firstLevel) && (firstLevel <= (10 * 2^speedLevels))) {
                ballSpeed.changeX(1.15);
                ballSpeed.changeY(1.15);
                platform.changeX(1.15);
                firstLevel *= 2;
            }
            if ((gameClock.getDT() > (15 + (15 * obstacleNum))) && (!obstacles[obstacleNum]) && (obstacleNum < 7)) {
                obstacles[obstacleNum] = true;
                int obsX = ball.getX();
                while ((obsX <= ball.getX() + ballWidth) && (obsX + obstacleWidth >= ball.getX())) {
                    //for (int i = 0; i < obstacleNum; i++) {
                        //while ((obsX <= (*obstacleList[i]).getX() + obstacleWidth) && (obsX + obstacleWidth >= (*obstacleList[i]).getX())) {
                            obsX = ((rand() % (windowWidth - obstacleWidth)) + (obstacleWidth / 2));
                        //}
                    //}
                }
                
                obstacleList[obstacleNum] = new Entity(obsX, (rand() % (windowHeight - (2 * windowHeight / 5))), obstacleWidth, obstacleHeight, obstacleTex);
                obstacleNum++;                
            }
            
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
                //ballSpeed.changeY(-1);
                //ball.setY(windowHeight - ballHeight);
                bool endScreen = true;
                SDL_Texture *playAgainButtonTex = window.loadTexture("res/gfx/playAgainButton.png");
                SDL_Texture *gameOverTex = window.loadTexture("res/gfx/gameOverImage.png");
                int gOWidth = 405;
                int gOHeight = 250;
                while (endScreen)
                {
                    frameManager.update();
                    if (frameManager.getDT() > (1 / 120.0f)) {
                        //printf("%.5f\n", frameManager.getDT());
                        frameManager.reset();
                        SDL_GetWindowSize(window.window, &windowWidth, &windowHeight);
                        int gameOX = (windowWidth / 2) - (gOWidth / 2);
                        int gameOY = (windowHeight / 4) - (gOHeight / 2) + 15;
                        Entity gameOIMG(gameOX, gameOY, gOWidth, gOHeight, gameOverTex);
                        
                        int playX = (windowWidth / 2) - (buttonWidth / 2);
                        int playY = (windowHeight / 2) - (buttonHeight / 2);
                        Entity playButton(playX, playY, buttonWidth, buttonHeight, playAgainButtonTex);

                        int quitY = playY + 5 + buttonHeight;
                        Entity quitButton(playX, quitY, buttonWidth, buttonHeight, quitButtonTex);

                        int hoverPlayX = (windowWidth / 2) - (hoverButtonWidth / 2);
                        int hoverPlayY = (windowHeight / 2) - (hoverButtonHeight / 2);
                        int hoverQuitY = playY + hoverButtonHeight;
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
                                    playButton = {(float) playX,(float) playY,(float) buttonWidth,(float) buttonHeight, playAgainButtonTex};
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
                                }
                                break;
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
                                    endScreen = false;
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
                        for (int i = 0; i < 8; i++) {
                            window.render(timings[i]);
                        }
                        window.render(platform);
                        window.render(gameOIMG);
                        window.render(ball);
                        window.render(playButton);
                        window.render(quitButton);
                        window.display();
                    }
                }
            }
            if ((ball.getX() + ballWidth - lenience >= platform.getX()) && (ball.getX() + lenience <= (platform.getX() + platformWidth)) && (ball.getY() + ballHeight >= platform.getY()) && (ball.getY() <= (platform.getY() + lenience))) {
                ball.setY(platform.getY() - ballHeight);
                ballSpeed.changeY(-1);
            }
            for (int i = 0; i < obstacleNum; i++) {
                if ((ball.getX() - lenience <= (*obstacleList[i]).getX() + obstacleWidth) && (ball.getX() >= (*obstacleList[i]).getX() + obstacleWidth - lenience) && (ball.getY() + ballHeight >= (*obstacleList[i]).getY()) && (ball.getY() <= (*obstacleList[i]).getY() + obstacleHeight))
                {
                    //printf("Ball hits right wall\n");
                    ball.setX((*obstacleList[i]).getX() + obstacleWidth + lenience);
                    ballSpeed.changeX(-1);
                }
                if ((ball.getX() + ballWidth + lenience >= (*obstacleList[i]).getX()) && (ball.getX() + ballWidth <= (*obstacleList[i]).getX() + lenience) && (ball.getY() + ballHeight >= (*obstacleList[i]).getY()) && (ball.getY() <= (*obstacleList[i]).getY() + obstacleHeight))
                {
                    //printf("Ball hits left wall\n");
                    ball.setX((*obstacleList[i]).getX() - ballWidth - lenience);
                    ballSpeed.changeX(-1);
                }
                if ((ball.getY() - lenience <= (*obstacleList[i]).getY() + obstacleHeight) && (ball.getY() >= (*obstacleList[i]).getY() + obstacleHeight - lenience) && (ball.getX() + ballWidth >= (*obstacleList[i]).getX()) && (ball.getX() <= (*obstacleList[i]).getX() + obstacleWidth))
                {
                    //printf("Ball hits bottom wall\n");
                    ball.setY((*obstacleList[i]).getY() + obstacleHeight + lenience);
                    ballSpeed.changeY(-1);
                }
                if ((ball.getY() + ballHeight + lenience >= (*obstacleList[i]).getY()) && (ball.getY() + ballHeight <= (*obstacleList[i]).getY() + lenience) && (ball.getX() + ballWidth >= (*obstacleList[i]).getX()) && (ball.getX() <= (*obstacleList[i]).getX() + obstacleWidth))
                {
                    //printf("Ball hits top wall\n");
                    ball.setY((*obstacleList[i]).getY() - ballHeight - lenience);
                    ballSpeed.changeY(-1);
                }
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
                        //playing = false;
                        //goto startscreen;
                        bool paused = true;
                        SDL_Texture *resumeButtonTex = window.loadTexture("res/gfx/resumeButton.png");
                        SDL_Texture *pausedImageTex = window.loadTexture("res/gfx/pausedImage.png");
                        while (paused)
                        {
                            frameManager.update();
                            if (frameManager.getDT() > (1 / 120.0f)) {
                                //printf("%.5f\n", frameManager.getDT());
                                frameManager.reset();
                                SDL_GetWindowSize(window.window, &windowWidth, &windowHeight);
                                int pausedWidth = 600;
                                int pausedHeight = 140;
                                int pausedX = (windowWidth / 2) - (titleWidth / 2);
                                int pausedY = (windowHeight / 4) - (titleHeight / 2);
                                Entity pausedIMG(pausedX, pausedY, pausedWidth, pausedHeight, pausedImageTex);
                                
                                int playX = (windowWidth / 2) - (buttonWidth / 2);
                                int playY = (windowHeight / 2) - (buttonHeight / 2);
                                Entity playButton(playX, playY, buttonWidth, buttonHeight, resumeButtonTex);

                                int quitY = playY + 5 + buttonHeight;
                                Entity quitButton(playX, quitY, buttonWidth, buttonHeight, quitButtonTex);

                                int hoverPlayX = (windowWidth / 2) - (hoverButtonWidth / 2);
                                int hoverPlayY = (windowHeight / 2) - (hoverButtonHeight / 2);
                                int hoverQuitY = playY + hoverButtonHeight;
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
                                            playButton = {(float) playX,(float) playY,(float) buttonWidth,(float) buttonHeight, resumeButtonTex};
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
                                        }
                                        break;
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
                                            paused = false;
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
                                for (int i = 0; i < numObstacles; i++) {
                                    if (obstacles[i]) {
                                        window.render(*(obstacleList[i]));
                                    }
                                    
                                }
                                for (int i = 0; i < 8; i++) {
                                    window.render(timings[i]);
                                }
                                window.render(platform);
                                window.render(pausedIMG);
                                window.render(ball);
                                window.render(playButton);
                                window.render(quitButton);
                                window.display();
                            }
                        }
                    }
                    if ((event.key.keysym.sym == SDLK_LEFT) || (event.key.keysym.sym == SDLK_a))
                    {
                        if (platform.getX() > 0) 
                            platform.changeX(-platformSpeed);
                    }
                    if ((event.key.keysym.sym == SDLK_RIGHT) || (event.key.keysym.sym == SDLK_d))
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

            for (int i = 0; i < numObstacles; i++)
            {
                if (obstacles[i]) {
                    window.render(*(obstacleList[i]));
                }
                
            }

            for (int i = 0; i < 8; i++) {
                window.render(timings[i]);
            }
            
            window.render(ball);
            window.render(platform);
            window.display();
        }
        
    }
    
    leaving: 
    gameClock.print();
    printf("Num Obstacles = %d, Obstacle Num = %d\n", numObstacles, obstacleNum);
    window.cleanup();
    SDL_Quit();
    return 0;
}