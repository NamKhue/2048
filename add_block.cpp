#include "add_block.h"
#include "check_put.h"


#include <SDL.h>
#include <SDL_main.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <string>

//check there is any move
bool checkToRandom(int **&tab, int **&backTab, int size)
{
	int can_put = 0;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (tab[i][j] != backTab[i][j])
				can_put = 1;
		}
	}
	return can_put;
}

//get point on random place in board
void randomOnBoard(int **&tab, int size)
{
	if (checkPut(tab, size))
	{
		int values[10] = {2, 2, 2, 2, 2, 4, 4, 4, 4, 4};
		int value = values[rand() % 10];

		int X = rand() % size;
		int Y = rand() % size;
		if (tab[X][Y] == 0)
			tab[X][Y] = 2;
		else
		{
			while (tab[X][Y] != 0)
			{
				X = rand() % size;
				Y = rand() % size;
			}
			tab[X][Y] = value;
		}
	}
}
