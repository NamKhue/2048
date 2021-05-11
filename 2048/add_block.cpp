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

//add value 2 or 4 in a random place on board
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
