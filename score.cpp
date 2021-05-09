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

void save_pretab(int **&tab, int size)
{
    FILE *tabList;

    switch (size)
    {
    case 3:
        tabList = fopen("text//size 3.txt", "w");
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                fprintf(tabList, "%d ", tab[i][j]);
            }
            fprintf(tabList, "\n");
        }
        break;
    case 4:
        tabList = fopen("text//size 4.txt", "w");
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                fprintf(tabList, "%d ", tab[i][j]);
            }
            fprintf(tabList, "\n");
        }
        break;
    case 5:
        tabList = fopen("text//size 5.txt", "w");
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                fprintf(tabList, "%d ", tab[i][j]);
            }
            fprintf(tabList, "\n");
        }
        break;
    case 6:
        tabList = fopen("text//size 6.txt", "w");
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                fprintf(tabList, "%d ", tab[i][j]);
            }
            fprintf(tabList, "\n");
        }
        break;
    case 7:
        tabList = fopen("text//size 7.txt", "w");
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                fprintf(tabList, "%d ", tab[i][j]);
            }
            fprintf(tabList, "\n");
        }
        break;
    case 8:
        tabList = fopen("text//size 8.txt", "w");
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                fprintf(tabList, "%d ", tab[i][j]);
            }
            fprintf(tabList, "\n");
        }
        break;
    case 9:
        tabList = fopen("text//size 9.txt", "w");
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                fprintf(tabList, "%d ", tab[i][j]);
            }
            fprintf(tabList, "\n");
        }
        break;
    default:
        tabList = fopen("text//size 10.txt", "w");
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                fprintf(tabList, "%d ", tab[i][j]);
            }
            fprintf(tabList, "\n");
        }
        break;
    }

    fclose(tabList);
}

void openPretabFile(int **&pTab, int size)
{
    FILE *f;

    switch (size)
    {
    case 3:
        f = fopen("text//size 3.txt", "r");

        if (f == NULL)
        {
            pTab = NULL;
        }

        fseek(f, 0, SEEK_SET);
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                fscanf(f, "%d ", &pTab[i][j]);
            }
            fscanf(f, "\n");
        }
        break;
    case 4:
        f = fopen("text//size 4.txt", "r");

        if (f == NULL)
        {
            pTab = NULL;
        }

        fseek(f, 0, SEEK_SET);
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                fscanf(f, "%d ", &pTab[i][j]);
            }
            fscanf(f, "\n");
        }
        break;
    case 5:
        f = fopen("text//size 5.txt", "r");

        if (f == NULL)
        {
            return;
        }

        fseek(f, 0, SEEK_SET);
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                fscanf(f, "%d ", &pTab[i][j]);
            }
            fscanf(f, "\n");
        }
        break;
    case 6:
        f = fopen("text//size 6.txt", "r");

        if (f == NULL)
        {
            return;
        }

        fseek(f, 0, SEEK_SET);
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                fscanf(f, "%d ", &pTab[i][j]);
            }
            fscanf(f, "\n");
        }
        break;
    case 7:
        f = fopen("text//size 7.txt", "r");

        if (f == NULL)
        {
            return;
        }

        fseek(f, 0, SEEK_SET);
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                fscanf(f, "%d ", &pTab[i][j]);
            }
            fscanf(f, "\n");
        }
        break;
    case 8:
        f = fopen("text//size 8.txt", "r");

        if (f == NULL)
        {
            return;
        }

        fseek(f, 0, SEEK_SET);
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                fscanf(f, "%d ", &pTab[i][j]);
            }
            fscanf(f, "\n");
        }
        break;
    case 9:
        f = fopen("text//size 9.txt", "r");

        if (f == NULL)
        {
            return;
        }

        fseek(f, 0, SEEK_SET);
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                fscanf(f, "%d ", &pTab[i][j]);
            }
            fscanf(f, "\n");
        }
        break;
    default:
        f = fopen("text//size 10.txt", "r");

        if (f == NULL)
        {
            return;
        }

        fseek(f, 0, SEEK_SET);
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                fscanf(f, "%d ", &pTab[i][j]);
            }
            fscanf(f, "\n");
        }
        break;
    }

    fclose(f);
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
