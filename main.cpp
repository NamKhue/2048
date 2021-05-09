#include "score.h"
#include "draw.h"
#include "win_lose.h"
#include "create_block.h"
#include "add_block.h"
#include "move.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <string>

#include <SDL.h>
#include <SDL_main.h>
#include <SDL_mixer.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define BOARD_SIZE 4

#define BOARD_WIDTH 300
#define BOARD_X 50
#define BOARD_Y 10

SDL_Event event;
SDL_Surface *screen, *char_pic;
SDL_Texture *scrtex;
SDL_Window *window;
SDL_Renderer *renderer;

//The music that will be played
Mix_Music *gMusic = Mix_LoadMUS("musicBg.wav");

char text[128];

bool init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    int rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
    if (rc != 0)
    {
        SDL_Quit();
        printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
        return 1;
    }

    //Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return 1;
    }

    return 0;
}

void initBg()
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_SetWindowTitle(window, "2048 GAME");

    screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                               SDL_TEXTUREACCESS_STREAMING,
                               SCREEN_WIDTH, SCREEN_HEIGHT);

    //disable cursor visibility
    SDL_ShowCursor(SDL_DISABLE);
}

bool loadImg()
{
    char_pic = SDL_LoadBMP("img//char_pic.bmp");
    if (char_pic == NULL)
    {
        printf("Can't load image: %s\n", SDL_GetError());
        SDL_FreeSurface(screen);
        SDL_DestroyTexture(scrtex);
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return 1;
    };

    return 0;
}

bool loadMedia()
{
    //Load music
    gMusic = Mix_LoadMUS("musicBg.wav");
    if (gMusic == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        return 0;
    }

    return 1;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    init();
    initBg();
    loadImg();
    loadMedia();
    SDL_SetColorKey(char_pic, true, 0x000000);

    //declare
    int size = 4;
    bool getStart = 0, contiPlaying;

    unsigned int score = 0, backScore = score;
    int **tab, **backtab;

    int fileSize = 0;
    PLAYERSCORE *winnerList;

    int t1, t2, quit, frames;
    double delta, worldTime, preWorldTime, fpsTimer, fps, preFps;

    int white = SDL_MapRGB(screen->format, 255, 255, 255);
    int lavender = SDL_MapRGB(screen->format, 230, 230, 250);
    int cornFlowerBlue = SDL_MapRGB(screen->format, 100, 149, 237);
    int pink = SDL_MapRGB(screen->format, 242, 82, 135);
    int green = SDL_MapRGB(screen->format, 40, 181, 181);
    int orange = SDL_MapRGB(screen->format, 247, 164, 64);
    int red = SDL_MapRGB(screen->format, 240, 89, 69);

    //assign variables with value
    tab = createTab(size);
    backtab = createTab(size);
    copyTab(tab, backtab, size);
    winnerList = openPointFile(fileSize);

    frames = 0;
    fpsTimer = 0;
    fps = 0;
    quit = 0;
    worldTime = 0;

    while (!quit)
    {
        // START WINDOW
        if (!getStart)
        {
            // play music
            Mix_PlayMusic(gMusic, -1);

            if (size >= 10)
                size = 10;
            if (size <= 3)
                size = 3;

            SDL_FillRect(screen, NULL, lavender);

            drawRectangle(screen, 2, 18, 165, 236, white, orange);
            drawRectangle(screen, 166, 18, 162, 236, white, pink);
            drawRectangle(screen, 327, 18, 153, 236, white, green);
            drawRectangle(screen, 479, 18, 159, 236, white, red);

            sprintf(text, "   2222222222222          000000000             444444444        888888888     ");
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 20, text, char_pic);
            sprintf(text, " 22             22      00         00          4        4      88         88   ");
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 35, text, char_pic);
            sprintf(text, "22     22222      2   00             00       4         4    88             88 ");
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 50, text, char_pic);
            sprintf(text, "2222222     2     2  0       000       0     4    44    4   8       888       8");
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 65, text, char_pic);
            sprintf(text, "            2     2  0      0   0      0    4    4 4    4   8     8     8     8");
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 80, text, char_pic);
            sprintf(text, "            2     2  0     0     0     0   4    4  4    4   8     8     8     8");
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 95, text, char_pic);
            sprintf(text, "         222     2   0     0     0     0  4    4   4    4    8      888      8 ");
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 110, text, char_pic);
            sprintf(text, "    22222      22    0     0     0     0 4    444444    444   8             8  ");
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 125, text, char_pic);
            sprintf(text, "  22        222      0     0     0     0 4                4  8      888      8 ");
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 140, text, char_pic);
            sprintf(text, " 2     22222         0     0     0     0 4444444444     444 8     8     8     8");
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 155, text, char_pic);
            sprintf(text, "2     2              0     0     0     0           4    4   8     8     8     8");
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 170, text, char_pic);
            sprintf(text, "2     2              0      0   0      0           4    4   8     8     8     8");
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 185, text, char_pic);
            sprintf(text, "2     2       222222 0       000       0           4    4   8       888       8");
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 200, text, char_pic);
            sprintf(text, "2     222222222    2  00             00          44      44  88             88 ");
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 215, text, char_pic);
            sprintf(text, "2                  2    00         00            4        4    88         88   ");
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 230, text, char_pic);
            sprintf(text, "22222222222222222222      000000000              4444444444      888888888     ");
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 245, text, char_pic);

            drawRectangle(screen, 100, 270, SCREEN_WIDTH - 200, 50, white, cornFlowerBlue);
            sprintf(text, "Choose size of map");
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 283, text, char_pic);
            sprintf(text, "\030 - bigger, \031 - smaller, enter - accept");
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 300, text, char_pic);

            drawRectangle(screen, 278, SCREEN_HEIGHT / 2 + 85, 85, 36, white, cornFlowerBlue);
            sprintf(text, "Size: %d", size);
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2 + 100, text, char_pic);

            drawRectangle(screen, 270, SCREEN_HEIGHT / 2 + 125, 100, 36, white, cornFlowerBlue);
            sprintf(text, "Continue");
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2 + 140, text, char_pic);

            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        quit = 1;
                    else if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
                        size++;
                    else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
                        size--;
                    else if (event.key.keysym.sym == SDLK_c)
                    {
                        contiPlaying = 1;
                        getStart = 1;
                        tab = createTab(size);
                        backtab = createTab(size);
                        openPretabFile(tab, size);
                    }
                    else if (event.key.keysym.sym == SDLK_RETURN)
                    {
                        contiPlaying = 0;
                        getStart = 1;
                        tab = createTab(size);
                        backtab = createTab(size);
                        copyTab(tab, backtab, size);
                        t1 = SDL_GetTicks();
                        backScore = 0;
                        score = 0;
                        worldTime = 0;
                    }
                    break;
                case SDL_QUIT:
                    quit = 1;
                    break;
                };
            };

            SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
            SDL_RenderCopy(renderer, scrtex, NULL, NULL);
            SDL_RenderPresent(renderer);
        }
        // GAME WINDOW
        else if (getStart && !checkLose(tab, size) && !checkWin(tab, size))
        {
            if (contiPlaying)
            {
                contiPlaying = 0;
            }

            //TIME COUNING
            t2 = SDL_GetTicks();
            delta = (t2 - t1) * 0.001;
            t1 = t2;
            worldTime += delta;
            fpsTimer += delta;

            if (fpsTimer > 0.5)
            {
                fps = frames * 2;
                fps /= 10;

                frames = 0;
                fpsTimer -= 0.5;
            };

            if (preWorldTime != 0)
            {
                worldTime = preWorldTime;
                preWorldTime = 0;
            }
            if (preFps != 0)
            {
                fps = preFps;
                preFps = 0;
            }

            SDL_FillRect(screen, NULL, lavender);

            drawBoard(screen, tab, size, white, cornFlowerBlue, char_pic);
            drawScore(screen, score, white, cornFlowerBlue, char_pic);

            // info text
            drawRectangle(screen, 20, 3, SCREEN_WIDTH - 40, 60, white, cornFlowerBlue);

            sprintf(text, "Time: %.1lf s  %.0lf frames/s", worldTime, fps);
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 14, text, char_pic);
            sprintf(text, "arrows (a,w,s,d) - move, u - undo");
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 30, text, char_pic);
            sprintf(text, "esc - menu, r - rankings, o - pause music, p - pause");
            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 46, text, char_pic);

            SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
            // SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, scrtex, NULL, NULL);
            SDL_RenderPresent(renderer);

            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        save_pretab(tab, size);
                        preWorldTime = worldTime;

                        getStart = 0;
                    }
                    else if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN ||
                             event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT ||
                             event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s ||
                             event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_d)
                    {
                        move(event, tab, size, backtab, score, backScore);
                    }
                    else if (event.key.keysym.sym == SDLK_u)
                    {
                        copyTab(tab, backtab, size);
                        score = backScore;
                    }
                    else if (event.key.keysym.sym == SDLK_p)
                    {
                        bool pause_game = 0;

                        preWorldTime = worldTime;
                        preFps = fps;

                        while (!pause_game)
                        {
                            SDL_FillRect(screen, NULL, lavender);

                            // info text
                            drawRectangle(screen, 20, 3, SCREEN_WIDTH - 40, 48, white, cornFlowerBlue);

                            sprintf(text, "Time: %.1lf s  %.0lf frames/s", preWorldTime, preFps);
                            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 14, text, char_pic);

                            sprintf(text, "esc - back to game, r - rankings");
                            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 30, text, char_pic);

                            while (SDL_PollEvent(&event))
                            {
                                switch (event.type)
                                {
                                case SDL_KEYDOWN:
                                    if (event.key.keysym.sym == SDLK_ESCAPE)
                                        pause_game = 1;
                                    else if (event.key.keysym.sym == SDLK_r)
                                    {
                                        // SHOW RANKING WINDOW
                                        bool show_ranking = 0;
                                        int amountBoard = 0;
                                        int startShow = 0;
                                        int limit = 10;

                                        for (int i = 0; i < fileSize; i++)
                                            if (size == winnerList[i].endSize)
                                                amountBoard++;

                                        PLAYERSCORE *sizeRanking = createRanking(winnerList, amountBoard, size, fileSize);

                                        while (!show_ranking)
                                        {
                                            SDL_FillRect(screen, NULL, lavender);

                                            drawRectangle(screen, 20, 3, SCREEN_WIDTH - 40, 48, white, cornFlowerBlue);

                                            sprintf(text, "Winner list for %dx%d", size, size);
                                            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 14, text, char_pic);

                                            sprintf(text, "esc - back to game, t - sort by time, p - sort by points");
                                            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 30, text, char_pic);

                                            // set start of ranking
                                            if (startShow <= 0)
                                                startShow = 0;
                                            if (startShow >= amountBoard - 10)
                                                startShow = amountBoard - 10;
                                            if (amountBoard <= 10)
                                            {
                                                startShow = 0;
                                                limit = amountBoard;
                                            }

                                            // check the winner list
                                            if (fileSize == 0 || limit == 0)
                                            {
                                                drawRectangle(screen, 140, SCREEN_HEIGHT / 2, SCREEN_WIDTH - 280, 40, white, cornFlowerBlue);
                                                sprintf(text, "Winner list in empty");
                                                drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2 + 16, text, char_pic);
                                            }

                                            int placeShow = 0;
                                            for (int i = startShow; placeShow < limit; i++)
                                            {
                                                drawRectangle(screen, SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 190 + placeShow * 40, 400, 40, white, cornFlowerBlue);
                                                sprintf(text, "%d. Time: %.1lfs Score: %d", startShow + placeShow + 1, sizeRanking[i].endTime, sizeRanking[i].endScore);
                                                drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2 - 200 + 26 + placeShow * 40, text, char_pic);

                                                placeShow++;
                                            }

                                            while (SDL_PollEvent(&event))
                                            {
                                                switch (event.type)
                                                {
                                                case SDL_KEYDOWN:
                                                    if (event.key.keysym.sym == SDLK_ESCAPE)
                                                        show_ranking = 1;
                                                    if (event.key.keysym.sym == SDLK_t)
                                                        sortByTime(sizeRanking, amountBoard);
                                                    if (event.key.keysym.sym == SDLK_p)
                                                        sortByScore(sizeRanking, amountBoard);
                                                    else if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
                                                        startShow++;
                                                    else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
                                                        startShow--;
                                                    break;
                                                case SDL_QUIT:
                                                    quit = 1;
                                                    show_ranking = 1;
                                                    break;
                                                };
                                            };

                                            SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
                                            SDL_RenderCopy(renderer, scrtex, NULL, NULL);
                                            SDL_RenderPresent(renderer);
                                        }
                                        delete[] sizeRanking;
                                    }
                                    break;
                                case SDL_QUIT:
                                    quit = 1;
                                    pause_game = 1;
                                    break;
                                };
                            }

                            SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
                            SDL_RenderCopy(renderer, scrtex, NULL, NULL);
                            SDL_RenderPresent(renderer);
                        }
                    }
                    else if (event.key.keysym.sym == SDLK_r)
                    {
                        // pause game;
                        preWorldTime = worldTime;
                        preFps = fps;

                        // SHOW RANKING WINDOW
                        bool show_ranking = 0;
                        int amountBoard = 0;
                        int startShow = 0;
                        int limit = 10;

                        for (int i = 0; i < fileSize; i++)
                            if (size == winnerList[i].endSize)
                                amountBoard++;

                        PLAYERSCORE *sizeRanking = createRanking(winnerList, amountBoard, size, fileSize);

                        while (!show_ranking)
                        {
                            SDL_FillRect(screen, NULL, lavender);

                            drawRectangle(screen, 20, 3, SCREEN_WIDTH - 40, 48, white, cornFlowerBlue);

                            sprintf(text, "Winner list for %dx%d", size, size);
                            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 14, text, char_pic);

                            sprintf(text, "esc - back to game, t - sort by time, p - sort by points");
                            drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 30, text, char_pic);

                            // set start of ranking
                            if (startShow <= 0)
                                startShow = 0;
                            if (startShow >= amountBoard - 10)
                                startShow = amountBoard - 10;
                            if (amountBoard <= 10)
                            {
                                startShow = 0;
                                limit = amountBoard;
                            }

                            // check there is winner list
                            if (fileSize == 0 || limit == 0)
                            {
                                drawRectangle(screen, 140, SCREEN_HEIGHT / 2, SCREEN_WIDTH - 280, 40, white, cornFlowerBlue);
                                sprintf(text, "Winner list in empty");
                                drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2 + 16, text, char_pic);
                            }

                            int placeShow = 0;
                            for (int i = startShow; placeShow < limit; i++)
                            {
                                drawRectangle(screen, SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 190 + placeShow * 40, 400, 40, white, cornFlowerBlue);
                                sprintf(text, "%d. Time: %.1lfs Score: %d", startShow + placeShow + 1, sizeRanking[i].endTime, sizeRanking[i].endScore);
                                drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2 - 200 + 26 + placeShow * 40, text, char_pic);

                                placeShow++;
                            }

                            while (SDL_PollEvent(&event))
                            {
                                switch (event.type)
                                {
                                case SDL_KEYDOWN:
                                    if (event.key.keysym.sym == SDLK_ESCAPE)
                                        show_ranking = 1;
                                    if (event.key.keysym.sym == SDLK_t)
                                        sortByTime(sizeRanking, amountBoard);
                                    if (event.key.keysym.sym == SDLK_p)
                                        sortByScore(sizeRanking, amountBoard);
                                    else if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
                                        startShow++;
                                    else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
                                        startShow--;
                                    break;
                                case SDL_QUIT:
                                    quit = 1;
                                    show_ranking = 1;
                                    break;
                                };
                            };

                            SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
                            SDL_RenderCopy(renderer, scrtex, NULL, NULL);
                            SDL_RenderPresent(renderer);
                        }
                        delete[] sizeRanking;
                    }
                    else if (event.key.keysym.sym == SDLK_o)
                    {
                        //If the music is paused
                        if (Mix_PausedMusic() == 1)
                        {
                            //Resume the music
                            Mix_ResumeMusic();
                        }
                        //If the music is playing
                        else
                        {
                            //Pause the music
                            Mix_PauseMusic();
                        }
                    }
                    break;
                case SDL_KEYUP:

                    break;
                case SDL_QUIT:
                    quit = 1;
                    break;
                };
            };

            frames++;
        }
        // IF PLAYER LOSE AND ENDCSREEN
        else if (checkLose(tab, size))
        {
            double endTime = worldTime;
            bool loseWindow = 0;

            while (!loseWindow)
            {
                SDL_FillRect(screen, NULL, lavender);

                drawRectangle(screen, 100, 10, SCREEN_WIDTH - 200, 36, white, cornFlowerBlue);
                sprintf(text, "YOU LOSE :))  esc - quit, m - menu");
                drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 26, text, char_pic);

                drawRectangle(screen, SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 36, 400, 36, white, cornFlowerBlue);
                sprintf(text, "Time: %.1lfs  Score: %u", endTime, score);
                drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2 - 20, text, char_pic);

                while (SDL_PollEvent(&event))
                {
                    switch (event.type)
                    {
                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            loseWindow = 1;
                            quit = 1;
                        }
                        else if (event.key.keysym.sym == SDLK_m)
                        {
                            for (int i = 0; i < size; ++i)
                                delete[] tab[i];
                            delete[] tab;

                            for (int i = 0; i < size; ++i)
                                delete[] backtab[i];
                            delete[] backtab;

                            loseWindow = 1;
                            getStart = 0;
                        }
                        break;
                    case SDL_QUIT:
                        quit = 1;
                        break;
                    };
                };

                SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
                SDL_RenderCopy(renderer, scrtex, NULL, NULL);
                SDL_RenderPresent(renderer);
            }
        }
        //IF PLAYER WIN
        else if (checkWin(tab, size))
        {
            double endTime = worldTime;
            bool winWindow = 0;

            while (!winWindow)
            {
                SDL_FillRect(screen, NULL, lavender);

                drawRectangle(screen, 100, 10, SCREEN_WIDTH - 200, 36, white, cornFlowerBlue);
                sprintf(text, "YOU WIN!!!  s - save time, esc - quit");
                drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, 26, text, char_pic);

                drawRectangle(screen, SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 36, 400, 36, white, cornFlowerBlue);
                sprintf(text, "Time: %.1lfs  Score: %u", endTime, score);
                drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2 - 20, text, char_pic);

                while (SDL_PollEvent(&event))
                {
                    switch (event.type)
                    {
                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            winWindow = 1;
                            quit = 1;
                        }
                        else if (event.key.keysym.sym == SDLK_s)
                        {
                            savePointToFile(score, endTime, size);

                            bool saveWindow = 0;

                            while (!saveWindow)
                            {
                                SDL_FillRect(screen, NULL, lavender);

                                drawRectangle(screen, 150, SCREEN_HEIGHT / 2 - 10, SCREEN_WIDTH - 300, 40, white, cornFlowerBlue);
                                sprintf(text, "Score saved!");
                                drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, SCREEN_HEIGHT / 2 - 1, text, char_pic);
                                sprintf(text, "esc - close game");
                                drawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, SCREEN_HEIGHT / 2 + 14, text, char_pic);

                                while (SDL_PollEvent(&event))
                                {
                                    switch (event.type)
                                    {
                                    case SDL_KEYDOWN:
                                        if (event.key.keysym.sym == SDLK_ESCAPE)
                                        {
                                            for (int i = 0; i < size; ++i)
                                                delete[] tab[i];
                                            delete[] tab;

                                            for (int i = 0; i < size; ++i)
                                                delete[] backtab[i];
                                            delete[] backtab;

                                            saveWindow = 1;
                                            winWindow = 1;
                                            getStart = 0;
                                        }
                                        break;
                                    case SDL_QUIT:
                                        winWindow = 1;
                                        quit = 1;
                                        break;
                                    };
                                };

                                SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
                                SDL_RenderCopy(renderer, scrtex, NULL, NULL);
                                SDL_RenderPresent(renderer);
                            }
                        }
                        else if (event.key.keysym.sym == SDLK_m)
                        {
                            for (int i = 0; i < size; ++i)
                                delete[] tab[i];
                            delete[] tab;

                            for (int i = 0; i < size; ++i)
                                delete[] backtab[i];
                            delete[] backtab;

                            winWindow = 1;
                            getStart = 0;
                        }
                        break;
                    case SDL_QUIT:
                        quit = 1;
                        break;
                    };
                };

                SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
                SDL_RenderCopy(renderer, scrtex, NULL, NULL);
                SDL_RenderPresent(renderer);
            }
        }
    };

    //freeing all surfaces and memory
    for (int i = 0; i < size; ++i)
        delete[] tab[i];
    delete[] tab;

    for (int i = 0; i < size; ++i)
        delete[] backtab[i];
    delete[] backtab;

    delete[] winnerList;

    SDL_FreeSurface(char_pic);
    SDL_FreeSurface(screen);
    SDL_DestroyTexture(scrtex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // free music
    Mix_FreeMusic(gMusic);
    gMusic = NULL;
    Mix_Quit();

    SDL_Quit();

    return 0;
};
