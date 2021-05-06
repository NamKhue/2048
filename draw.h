#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED


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


void drawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset);
void drawPixel(SDL_Surface *surface, int x, int y, Uint32 color);
void drawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color);
void drawRectangle(SDL_Surface *screen, int x, int y, int l, int k,
                   Uint32 outlineColor, Uint32 fillColor);
void drawPoint(SDL_Surface *screen, int X, int Y, int width, const char *number, SDL_Surface *charset);
int get_power(int x);
void drawBoard(SDL_Surface *screen, int **tab, int size, Uint32 outlineColor, Uint32 fillColor, SDL_Surface *charset);
void drawScore(SDL_Surface *screen, unsigned int score, Uint32 outlineColor, Uint32 fillColor, SDL_Surface *charset);


#endif // DRAW_H_INCLUDED
