#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED


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


void rushTop(int **&tab, int size);
void moveTop(int **&tab, int size, unsigned int &score);
void rushBot(int **&tab, int size);
void moveBot(int **&tab, int size, unsigned int &score);
void rushRight(int **&tab, int size);
void moveRight(int **&tab, int size, unsigned int &score);
void rushLeft(int **&tab, int size);
void moveLeft(int **&tab, int size, unsigned int &score);

void copyTab(int **&tab1, int **&tab2, int size);
void move(SDL_Event event, int **&tab, int size, int **&backtab, unsigned int &score, unsigned int &backScore);


#endif // MOVE_H_INCLUDED
