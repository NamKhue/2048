#include "create_block.h"

#include <SDL.h>
#include <SDL_main.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <string>

//create table with 2 random positions
int **createTab(int size)
{
	int **tab;
	tab = new int *[size];

	for (int i = 0; i < size; i++)
	{
		tab[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			tab[i][j] = 0;
		}
	}

	int X, Y, preX, preY;

	preX = rand() % size;
	preY = rand() % size;
	tab[preX][preY] = 2;

	do
	{
		X = rand() % size;
		Y = rand() % size;
	} while (preX == X && preY == Y);
	tab[X][Y] = 2;

	return tab;
}
