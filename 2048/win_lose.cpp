#include "win_lose.h"
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

// check is there 2048 on board
bool checkWin(int **&tab, int size)
{
    bool win = 0;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (tab[i][j] == 2048)
                win = 1;
        }
    }

    return win;
}

//check that player can make any move
bool checkLose(int **&tab, int size)
{
    bool lose = 1;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (tab[i][j] == tab[i][j + 1])
                lose = 0;
        }
    }
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (tab[i][j] == tab[i + 1][j])
                lose = 0;
        }
    }

    if (checkPut(tab, size))
        lose = 0;

    return lose;
}
