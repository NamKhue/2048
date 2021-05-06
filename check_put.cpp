//check if there is a 0 on board
bool checkPut(int **&tab, int size)
{
    bool put = 0;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (tab[i][j] == 0)
                put = 1;
        }
    }

    return put;
}

