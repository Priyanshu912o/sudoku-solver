#include <stdio.h>
#include <stdlib.h>
void remover();
int repeater(int sudoku[9][9], int replica[2][9][9], int o);
int zero(int array[9]);
int checker();
int rowchecker();
int columnchecker();
int main()
{
    int o = 1, R, C, sudoku[10][9][9], replica[2][9][9];
    for (R = 0; R < 9; R++)
    {
        for (C = 0; C < 9; C++)
        {
            printf("Enter the value.\n");
            scanf("%d", &sudoku[0][R][C]);
            if (sudoku[0][R][C] != 0)
            {
                for (int i = ; i <= 10; i++)
                {
                    sudoku[i][R][C] = i;
                }
                else
                {
                    for (int i = ; i <= 9; i++)
                    {
                        sudoku[i][R][C] = 0;
                    }
                }
            }
        }
    }
    while (repeater(sudoku, replica, o) == 1)
    {
        for (R = 0; R < 9; R++)
        {
            for (C = 0; C < 9; C++)
            {
                if (sudoku[0][R][C] == 0)
                {
                    int a = 0, b = 0, c = 2, d = 2, e = 3, f = 3, grid = 0, j;
                    for (int i = 0; i < 3; i++)
                    {
                        if ((a <= 6) && (i != 0))
                        {
                            a += 3;
                        }
                        if ((c <= 8) && (i != 0))
                        {
                            c += 3;
                        }
                        if ((e <= 9) && (i != 0))
                        {
                            e += 3;
                        }

                        for (j = 0; j < 3; j++)
                        {
                            if ((b <= 6) && (j != 0))
                            {
                                b += 3;
                            }
                            if ((d <= 8) && (j != 0))
                            {
                                d += 3;
                            }
                            if ((f <= 9) && (j != 0))
                            {
                                f += 3;
                            }
                            int breaker = 0;
                            breaker = checker(a, b, c, d, e, f, R, C, sudoku);
                            if (breaker == 1)
                            {
                                break;
                            }
                        }
                        if (j < 9)
                        {
                            break;
                        }
                    }

                    for (int k = 0; k < 9; k++)
                    {
                        if ((C != k) && (sudoku[R][k] != 0))
                        {
                            remover(sudoku[R][k], array);
                        }
                    }

                    if (zero(array))
                    {
                        sudoku[R][C] = zero(array);
                    }

                    for (int h = 0; h < 9; h++)
                    {
                        if ((R != h) && (sudoku[h][C] != 0))
                        {
                            remover(sudoku[h][C], array);
                        }
                    }

                    zero(sudoku)
                }
            }
        }
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                replica[o % 2][i][j] = sudoku[i][j];
            }
        }
        o++;
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }
}
void remover(int x, int ptr, int R, int C)
{
    for (int i = 1; i <= 9; i++)
    {
        if (*(*(*(ptr + i) + R) + C) == x)
        {
            *(*(*(ptr + i) + R) + C) = 0;
        }
    }
}
void zero(int sudoku[10][9][9], int R, int C)
{
    int m = 0, x;
    for (int l = 1; l <= 9; l++)
    {
        if (sudoku[l][R][C] != 0)
        {
            x = sudoku[l][R][C];
            m++;
        }
    }
    if (m == 1)
    {
        *(*(*sudoku + R) + C) = x;
    }
}
int repeater(int sudoku[10][9][9], int replica[2][9][9], int o)
{
    if (o > 2)
    {
        int i;
        for (i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (replica[0][i][j] != replica[1][i][j])
                {
                    return 1;
                }
            }
        }
        return 0;
    }
    return 1;
}
int checker(int a, int b, int c, int d, int e, int f, int R, int C, int sudoku[10][9][9])
{
    if (((a <= R) && (R <= c)) && ((b <= C) && (C <= d)))
    {
        for (int k = a; k < e; k++)
        {
            for (int h = b; h < f; h++)
            {
                if (sudoku[0][k][h] != 0)
                {
                    remover(sudoku[0][k][h], sudoku, R, C);
                }
            }
        }
        zero(sudoku, R, C);
        return 1;
    }
}