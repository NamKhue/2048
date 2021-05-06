#ifndef ADD_BLOCK_H_INCLUDED
#define ADD_BLOCK_H_INCLUDED


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


bool checkToRandom(int **&tab, int **&backTab, int size);
void randomOnBoard(int **&tab, int size);


#endif // ADD_BLOCK_H_INCLUDED
