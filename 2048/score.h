#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <string>

#include <SDL.h>
#include <SDL_main.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define BOARD_SIZE 4

#define BOARD_WIDTH 300
#define BOARD_X 50
#define BOARD_Y 10

struct PLAYERSCORE
{
    int endScore;
    double endTime;
    int endSize;
    std::string username;
};

void sortByScore(PLAYERSCORE *&tab, int size);
void sortByTime(PLAYERSCORE *&tab, int size);
PLAYERSCORE *createRanking(PLAYERSCORE *tab, int amount, int size, int fileSize);
void save_pretab(int **&tab, int size);
void openPretabFile(int **&pTab, int size);
void savePointToFile(int score, double time, int size);
PLAYERSCORE *openPointFile(int &lines);

#endif // SCORE_H_INCLUDED
