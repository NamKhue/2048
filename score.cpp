#include "score.h"

#include <SDL.h>
#include <SDL_main.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <string>

// bubble sort
void sortByScore(PLAYERSCORE *&tab, int size)
{
    PLAYERSCORE helper;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (tab[j].endScore > tab[j + 1].endScore)
            {
                helper = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = helper;
            }
        }
    }

    for (int i = 0; i < size / 2; i++)
    {
        helper = tab[i];
        tab[i] = tab[size - i - 1];
        tab[size - i - 1] = helper;
    }
}

void sortByTime(PLAYERSCORE *&tab, int size)
{
    PLAYERSCORE helper;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (tab[j].endTime > tab[j + 1].endTime)
            {
                helper = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = helper;
            }
        }
    }
}

// create list of score for each board size
PLAYERSCORE *createRanking(PLAYERSCORE *tab, int amount, int size, int fileSize)
{
    PLAYERSCORE *ranking = new PLAYERSCORE[amount];
    int j = 0;
    for (int i = 0; i < fileSize; i++)
    {
        if (tab[i].endSize == size)
        {
            ranking[j].endScore = tab[i].endScore;
            ranking[j].endTime = tab[i].endTime;
            ranking[j].endSize = tab[i].endSize;
            j++;
        }
    }
    return ranking;
}

// void save_pretab(int score, double time, int size)
// {
//     FILE *fileList = fopen("text//winner list.txt", "a");
//     fprintf(fileList, "%u %.1lf %d\n", score, time, size);

//     fclose(fileList);
// }

void save_pretab(int **&tab, int size)
{
    FILE *tabList = fopen("text//size.txt", "a");

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            fprintf(tabList, "%d ", tab[i][j]);
        }
        fprintf(tabList, "\n");
    }

    fclose(tabList);
}

PLAYERSCORE *openPretabFile(int &lines)
{
    FILE *fileList = fopen("text//size.txt", "r");
    int ch = 0;

    if (fileList == NULL)
    {
        return 0;
    }

    while (!feof(fileList))
    {
        ch = fgetc(fileList);
        if (ch == '\n')
        {
            lines++;
        }
    }

    PLAYERSCORE *list = new PLAYERSCORE[lines];
    fseek(fileList, 0, SEEK_SET);
    for (int i = 0; i < lines; i++)
    {
        fscanf(fileList, "%d %lf %d", &list[i].endScore, &list[i].endTime, &list[i].endSize);
    }
    fclose(fileList);

    return list;
}

void openPretabFile(int **&pTab, int size)
{
    FILE *f = fopen("text//size.txt", "r");
    int ch = 0;

    if (f == NULL)
    {
        return 0;
    }

    while (!feof(f))
    {
        ch = fgetc(f);
        if (ch == '\n')
        {
            lines++;
        }
    }

    PLAYERSCORE *list = new PLAYERSCORE[lines];
    fseek(f, 0, SEEK_SET);

    // temp
    for (int i = 0; i < lines; i++)
    {
        fscanf(f, "%d %lf %d", &list[i].endScore, &list[i].endTime, &list[i].endSize);
    }

    // idk
    fseek(f, 0, SEEK_SET);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            fscanf(f, "%d ", &pTab[i][j]);
        }
        fscanf(f, "\n");
    }

    fclose(f);
    return list;
}

void savePointToFile(int score, double time, int size)
{
    FILE *fileList = fopen("text//winner list.txt", "a");
    fprintf(fileList, "%u %.1lf %d\n", score, time, size);

    fclose(fileList);
}

// create whole list of scores
PLAYERSCORE *openPointFile(int &lines)
{
    FILE *fileList = fopen("text//winner list.txt", "r");
    int ch = 0;

    if (fileList == NULL)
    {
        return 0;
    }

    while (!feof(fileList))
    {
        ch = fgetc(fileList);
        if (ch == '\n')
        {
            lines++;
        }
    }

    PLAYERSCORE *list = new PLAYERSCORE[lines];
    fseek(fileList, 0, SEEK_SET);
    for (int i = 0; i < lines; i++)
    {
        fscanf(fileList, "%d %lf %d", &list[i].endScore, &list[i].endTime, &list[i].endSize);
    }
    fclose(fileList);

    return list;
}
