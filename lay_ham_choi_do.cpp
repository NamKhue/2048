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

// take previous tab
int **takePreTab(int size)
{
    copyTab(tab, backtab, size);
}