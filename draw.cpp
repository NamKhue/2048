#include "draw.h"

#include <SDL.h>
#include <SDL_main.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <string>

// draw a text txt on surface screen, starting from the point (x, y)
// char_pic is a 128x128 bitmap containing character images
void drawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *char_pic)
{
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text)
	{
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(char_pic, &s, screen, &d);
		x += 8;
		text++;
	};
};

// draw a single pixel
void drawPixel(SDL_Surface *surface, int x, int y, Uint32 color)
{
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *)p = color;
};

// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void drawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color)
{
	for (int i = 0; i < l; i++)
	{
		drawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};

// draw a rectangle of size l by k
void drawRectangle(SDL_Surface *screen, int x, int y, int l, int k,
				   Uint32 outlineColor, Uint32 fillColor)
{
	int i;
	drawLine(screen, x, y, k, 0, 1, outlineColor);
	drawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	drawLine(screen, x, y, l, 1, 0, outlineColor);
	drawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);

	for (i = y + 1; i < y + k - 1; i++)
		drawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};

//Draw point of block in the middle of it
void drawPoint(SDL_Surface *screen, int X, int Y, int width, const char *number, SDL_Surface *char_pic)
{
	int length = strlen(number);
	drawString(screen, (X + width / 2) - length * 4, Y + width / 2, number, char_pic);
}

// int get_power(int x)
// {
//  	int n = 0;
//  	while (x)
//  	{
//  		x /= 2;
//  		n++;
//  	}
//  	return n;
// }

//draw board with all block and points
void drawBoard(SDL_Surface *screen, int **tab, int size, Uint32 outlineColor, Uint32 fillColor, SDL_Surface *char_pic)
{
	int width = (BOARD_WIDTH / size);
	int X, Y;
	char number[5];
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			X = 1.5 * BOARD_X + (BOARD_WIDTH / size) * i;
			Y = 1.5 * BOARD_Y + (BOARD_WIDTH / size) * j;

			// int color_power = get_power(tab[i][j]);

			drawRectangle(screen, Y, X, width, width, outlineColor, fillColor);
			// SDL_MapRGB(screen->format, 130, 120, 160 + 10 * color_power)

			if (tab[i][j] == 0)
				sprintf(number, "");
			else
				sprintf(number, "%d", tab[i][j]);
			drawPoint(screen, Y, X, width, number, char_pic);
		}
	}
}

void drawScore(SDL_Surface *screen, unsigned int score, Uint32 outlineColor, Uint32 fillColor, SDL_Surface *char_pic)
{
	int X = 1.5 * BOARD_X;
	int Y = 1.5 * BOARD_Y + BOARD_WIDTH + 100;
	int width = 40;
	char number[18];

	drawRectangle(screen, Y - 40, X + 3, width + 82, width, outlineColor, fillColor);
	sprintf(number, "Score: %u", score);
	drawPoint(screen, Y, X, width, number, char_pic);
}
