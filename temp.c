#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void input_sudoku();
void row_column_grid_remover();
void filler();
bool repeater();
void layer_checker();

int main()
{
    int sudoku[10][9][9], R, C, o = 0;
    input_sudoku(sudoku);
    while (repeater(sudoku, o))
    {
        for (int R = 0; R < 9; R++)
        {
            for (int C = 0; C < 9; C++)
            {
                if (sudoku[0][R][C] != 0)
                {
                    row_column_grid_remover(sudoku[0][R][C], sudoku, R, C);
                }
            }
        }

        filler(sudoku);
        layer_checker(sudoku);

        o++;
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            printf("%d ", sudoku[0][i][j]);
        }
        printf("\n");
    }
}

void input_sudoku(int sudoku[10][9][9])
{
    int R, C;

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

void row_column_grid_remover(int garbage, int sudoku[10][9][9], int ROW, int COLUMN)
{
    for (int i = 0; i < 9; i++)
    {
        *(*(*(sudoku + garbage) + ROW) + i) = 0;
        *(*(*(sudoku + garbage) + i) + COLUMN) = 0;
    }

    int grid_row_lowerbound = ((int)(ROW / 3) * 3);
    int grid_column_lowerbound = ((int)(COLUMN / 3) * 3);
    for (int i = grid_row_lowerbound; i < (grid_row_lowerbound + 3); i++)
    {
        for (int j = grid_column_lowerbound; j < (grid_column_lowerbound + 3); j++)
        {
            *(*(*(sudoku + garbage) + i) + j) = 0;
        }
    }
}

void filler(int sudoku[10][9][9])
{
    for (int ROW = 0; ROW < 9; ROW++)
    {
        for (int COLUMN = 0; COLUMN < 9; COLUMN++)
        {
            int possibilty = 0;
            int number_of_possibilities = 0;
            if (sudoku[0][ROW][COLUMN] == 0)
            {
                for (int possibilties = 1; (possibilties < 10) && (sudoku[possibilties][ROW][COLUMN] != 0); possibilties++)
                {
                    possibilty = possibilties;
                    number_of_possibilities++;
                }
                if (number_of_possibilities == 1)
                {
                    *(*(*sudoku + ROW) + COLUMN) = possibilty;
                    for (int grid = 1; grid < 10; grid++)
                    {
                        *(*(*(sudoku + grid) + ROW) + COLUMN) = 0;
                    }
                }
            }
        }
    }
}

bool repeater(int sudoku[10][9][9], int turn)
{
    static int comparing_array[2][9][9];
    for (int ROW = 0; ROW < 9; ROW++)
    {
        for (int COLUMN = 0; COLUMN < 9; COLUMN++)
        {
            comparing_array[turn][ROW][COLUMN] = sudoku[0][ROW][COLUMN];
        }
    }

    if (turn > 2)
    {
        for (int ROW = 0; ROW < 9; ROW++)
        {
            for (int COLUMN = 0; COLUMN < 9; COLUMN++)
            {
                if (comparing_array[0][ROW][COLUMN] != comparing_array[1][ROW][COLUMN])
                {
                    return true;
                }
            }
        }
    }

    if (turn <= 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void layer_checker(int sudoku[10][9][9])
{
    for (int grid = 1; grid < 10; grid++)
    {
        for (int ROW = 0; ROW < 9; ROW++)
        {
            int possibility;
            int number_of_possibilities = 0;
            int possible_row = 0;
            int possible_column = 0;
            for (int COLUMN = 0; (COLUMN < 9) && (sudoku[grid][ROW][COLUMN] == grid); COLUMN++)
            {
                possible_row = ROW;
                possible_column = COLUMN;
                possibility = grid;
                number_of_possibilities++;
            }
            if (number_of_possibilities == 1)
            {
                *(*(*(sudoku + grid) + possible_row) + possible_column) = possibility;
                for (int layer = 1; layer < 10; layer++)
                {
                    *(*(*(sudoku + layer) + possible_row) + possible_column) = 0;
                }
            }
        }

        for (int COLUMN = 0; COLUMN < 9; COLUMN++)
        {
            int possibility;
            int number_of_possibilities = 0;
            int possible_row = 0;
            int possible_column = 0;
            for (int ROW = 0; (ROW < 9) && (sudoku[grid][ROW][COLUMN] == grid); ROW++)
            {
                possibility = grid;
                number_of_possibilities++;
            }
            if (number_of_possibilities == 1)
            {
                *(*(*(sudoku + grid) + possible_row) + possible_column) = possibility;
                for (int layer = 1; layer < 10; layer++)
                {
                    *(*(*(sudoku + layer) + possible_row) + possible_column) = 0;
                }
            }
        }
    }
}