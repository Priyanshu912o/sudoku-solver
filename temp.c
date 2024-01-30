#include <stdio.h>
#include <stdlib.h>

void input_sudoku();
void remover();
int repeater();
void zero();
int checker();
void rowchecker();
void columnchecker();

int main()
{
    int o = 1, R, C, sudoku[10][9][9], replica[2][9][9];

    // Input of array

    input_sudoku(sudoku, R, C);

    // Checking begins

    while (repeater(replica, o) == 1)
    {
        for (R = 0; R < 9; R++)
        {
            for (C = 0; C < 9; C++)
            {
                if (sudoku[0][R][C] == 0)
                {
                    int a = 0, b = 0, c = 2, d = 2, e = 3, f = 3, grid = 0, j;

                    // from here two nested loops create upper & lower bound conditions for 9 sudoku grids to check positioning of the element.

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
                        if (j < 3)
                        {
                            break; // here the outer loop is exited iff the inner loop breaks in between which will happen when the right grid is found using the checker function.
                        }
                    }

                    for (int k = 0; k < 9; k++)
                    {
                        if ((C != k) && (sudoku[0][R][k] != 0))
                        {
                            remover(sudoku[0][R][k], sudoku, R, C); // fixed this (was entering sudoku[10][9][9] as second argument)
                        }
                        columnchecker(sudoku, R, C);
                    }

                    zero(sudoku, R, C);

                    for (int h = 0; h < 9; h++)
                    {
                        if ((R != h) && (sudoku[0][h][C] != 0))
                        {
                            remover(sudoku[0][h][C], sudoku, R, C); // same error fixed as 10 lines above
                        }
                        rowchecker(sudoku, R, C);
                    }

                    zero(sudoku, R, C);
                }
            }
        }
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                replica[o % 2][i][j] = sudoku[0][i][j]; // here the latest face of sudoku gets stored in an another array for further coparison(for while loop condition).
            }
        }
        o++;
    }

    // Display answer

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            printf("%d ", sudoku[0][i][j]);
        }
        printf("\n");
    }
}

// Functions

void input_sudoku(int sudoku[10][9][9], int R, int C)
{

    // This function inputs sudoku from text file. An example problem is given in input.txt

    FILE *fptr = fopen("input.txt", "r");

    if (fptr == NULL)
    {
        printf("Error While opening file");
        exit(1);
    }

    int thisChar;

    for (R = 0; R < 9; R++)
    {
        for (C = 0; C < 9; C++)
        {
            thisChar = fgetc(fptr);
            sudoku[0][R][C] = thisChar - '0'; // this converts char number to int number
            if (sudoku[0][R][C] == 0)
            {
                for (int i = 1; i < 10; i++)
                {
                    sudoku[i][R][C] = i;
                }
            }
            else
            {
                for (int i = 1; i < 10; i++)
                {
                    sudoku[i][R][C] = 0;
                }
            }
        }
    }
}

void remover(int x, int sudoku[10][9][9], int R, int C)
{
    for (int i = 1; i <= 9; i++)
    {
        if (*(*(*(sudoku + i) + R) + C) == x)
        {
            *(*(*(sudoku + i) + R) + C) = 0;
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
int repeater(int replica[2][9][9], int o)
{
    if (o > 100000)
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

        for (int i = 1; i < 10; i++)
        {

            if (sudoku[i][R][C] != 0)
            {
                int x = sudoku[i][R][C];
                for (int k = a; k < e; k++)
                {
                    for (int h = b; h < f; h++)
                    {
                        if ((sudoku[0][k][h] == 0) && ((k != R) || (h != C)))
                        {
                            for (int j = 1; j < 10; j++)
                            {
                                if (x == sudoku[j][k][h])
                                {
                                    goto afterForLoop;
                                }
                            }
                        }
                    }
                }
                sudoku[0][R][C] = sudoku[i][R][C];
            }

        afterForLoop:
            zero(sudoku, R, C);
            return 1;
        }
    }
}
void columnchecker(int sudoku[10][9][9], int R, int C)
{
    for (int i = 1; i < 10; i++)
    {
        if (sudoku[i][R][C] != 0)
        {
            int x = sudoku[i][R][C];
            for (int h = 0; h < 9; h++)
            {
                if ((sudoku[0][R][h] == 0) && (C != h))
                {
                    for (int j = 1; j < 10; j++)
                    {
                        if (x == sudoku[j][R][h])
                        {
                            goto afterForLoop2;
                        }
                    }
                }
            }
            sudoku[0][R][C] = sudoku[i][R][C];
            int count = 0;
            count++;
        afterForLoop2:
            if (count == 1)
            {
                for (int num = 1; num < 10; num++)
                {
                    sudoku[num][R][C] = 0;
                }
            }
        }
    }
}
void rowchecker(int sudoku[10][9][9], int R, int C)
{
    for (int i = 1; i < 10; i++)
    {
        if (sudoku[i][R][C] != 0)
        {
            int x = sudoku[i][R][C];
            for (int k = 0; k < 9; k++)
            {
                if ((sudoku[0][k][C] == 0) && (R != k))
                {
                    for (int j = 1; j < 10; j++)
                    {
                        if (x == sudoku[j][k][C])
                        {
                            goto afterForLoop3;
                        }
                    }
                }
            }
            sudoku[0][R][C] = sudoku[i][R][C];
            int count = 0;
            count++;
        afterForLoop3:
            if (count == 1)
            {
                for (int num = 1; num < 10; num++)
                {
                    sudoku[num][R][C] = 0;
                }
            }
        }
    }
}