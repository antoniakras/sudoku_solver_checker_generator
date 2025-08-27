#include "sudoku.h"
#include <ctype.h>
#include <assert.h>
#include <string.h>

int sudoku[9][9];

Grid_T sudoku_read(void)
{

    char arr[2];
    int input;
    int c = 0;
    int i = 0; /* row */
    int j = 0; /* col */
    int flag = 0;
    Grid_T grid;

    while ((arr[0] = getchar()) != EOF)
    {

        if (isdigit((int)arr[0]))
        {
            input = atoi(arr);
            if (input < 0 || input > 9)
            {
                fprintf(stderr, "error wrong num range\n");
                flag = 1;
            }

            /*else: update grid with values and move on*/
            grid_update_value(&grid, i, j, input);
            sudoku[i][j] = input;
            j++;
            /*increment valid input counter*/
            c++;
        }

        if (arr[0] == '\n')
        {
            /*new grid line : go to the beg. of the next row*/
            i++;
            j = 0;
        }
    }
    if (c != 81)
    {
        fprintf(stderr, "error, wrong number of inputs.\n");
        flag = 1;
    }
    return grid;

    /*check values < 9 &space*/
    /*total num of inputs must be=81*/
    /*check if unique*/
}

void sudoku_print(FILE *s, Grid_T g)
{
    int i;
    int j;

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            fprintf(s, " %d ", grid_read_value(g, i, j));
        }
        fprintf(s, "\n");
    }
}

int check_row_dupes(Grid_T g, int row)
{
    int i, j, l;
    int arr[9];

    for (l = 0; l < 9; l++)
    {
        arr[l] = grid_read_value(g, row, l);
    }

    for (i = 0; i < 9; i++)
    {
        for (j = i + 1; j < 9; j++)
        {
            if (arr[i] == arr[j])
            {
                if (arr[i] != 0)
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}

int check_col_dupes(Grid_T g, int col)
{

    int i, j, l;
    int arr[9];

    for (l = 0; l < 9; l++)
    {
        arr[l] = grid_read_value(g, l, col);
    }

    for (i = 0; i < 9; i++)
    {
        for (j = i + 1; j < 9; j++)
        {
            if (arr[i] == arr[j])
            {
                if (arr[i] != 0)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int check_grid_dupes(Grid_T g, int row, int col)
{

    int i, j, l;
    int arr[3][3];
    int tmp[10];
    int tmp_col;
    tmp_col = col;
    l = 0;
    tmp[9] = -1;
    /*tmp array that contains sub grid elements*/

    /*fill sub-grid matrix with grid values*/

    for (i = 0; i < 3; i++)
    {
        col = tmp_col;

        for (j = 0; j < 3; j++)
        {
            arr[i][j] = grid_read_value(g, row, col);
            tmp[l] = arr[i][j];
            l++;
            col++;
        }
        row++;
    }

    /*check if sub-grid matrix arr has duplicates.*/

    for (i = 0; i < 9; i++)
    {
        for (j = i + 1; j < 9; j++)
        {
            if (tmp[i] == tmp[j])
            {
                /*dupe is found return 1*/
                if (tmp[i] != 0)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int sudoku_solution_is_unique(Grid_T g)
{
    return grid_read_unique(g);
}

int sudoku_is_correct(Grid_T g)
{
    /*check row, col and subgrid for dupes.
    if found: return 1/has errors.
    */
    int i, j;
    int flag, row_flag, col_flag, grid_flag;
    int col_err;
    int row_err;
    row_err = 0;
    col_err = 0;
    flag = 0;
    grid_flag = 0;
    row_flag = 0;
    col_flag = 0;

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            col_flag = check_col_dupes(g, j);
            if (col_flag == 1)
                col_err = 1;
        }
        row_flag = check_row_dupes(g, i);
        if (row_flag == 1)
            row_err = 1;
    }

    /*subgrid check*/
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if ((i % 3 == 0) && (j % 3 == 0))
            {
                grid_flag = check_grid_dupes(g, i, j);
                if (grid_flag == 1)
                    break;
            }
            if (grid_flag == 1)
                break;
        }
        if (grid_flag == 1)
            break;
    }

    if (row_err == 1)
    {
        flag = 1;
        fprintf(stderr, "ERROR: duplicate found in row.\n");
    }
    if (col_err == 1)
    {
        flag = 1;
        fprintf(stderr, "ERROR: duplicate found in column.\n");
    }
    if (grid_flag == 1)
    {
        flag = 1;
        fprintf(stderr, "ERROR: duplicate found in subgrid.\n");
    }

    return flag;
}

static void sudoku_init_choices(Grid_T *g)
{
    int i, j, n, tmp_i, tmp_j;
    int row_flag, col_flag, grid_flag;
    grid_set_unique(g);
    /*set as unique and if multiple solutions are found while solving remove.*/
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (grid_read_value(*g, i, j) != 0)
            {
                continue;
            }
            if ((i % 3 == 0) && (j % 3 == 0))
            {
                grid_flag = check_grid_dupes(*g, i, j);
            }
            else
            {
                tmp_i = i;
                tmp_j = j;
                while ((tmp_i % 3 != 0) && (tmp_j % 3 != 0))
                {
                    if (tmp_i % 3 != 0)
                    {
                        tmp_i--;
                    }
                    if (tmp_j % 3 != 0)
                    {
                        tmp_j--;
                    }
                }
                grid_flag = check_grid_dupes(*g, tmp_i, tmp_j);
            }
            for (n = 1; n < 10; n++)
            {
                grid_update_value(g, i, j, n);
                row_flag = check_row_dupes(*g, i);
                col_flag = check_col_dupes(*g, j);

                if ((col_flag == 0) && (row_flag == 0) && (grid_flag == 0))
                {
                    /*update temp grid with possible choices?*/
                    grid_set_choice(g, i, j, n);
                    grid_set_count(g, i, j);
                }
                else
                {
                    /*dupes are found set value back to 0.*/
                    grid_update_value(g, i, j, 0);
                }
            }
        }
    }
}

void sudoku_eliminate_choice(Grid_T *g, int r, int c, int n)
{
    int i, j, row, col;
    /*remove choice n from row,col,subgrid*/
    for (i = 0; i < 9; i++)
    {
        grid_remove_choice(g, i, c, n);
        grid_remove_choice(g, r, i, n);
    }
    row = r - r % 3;
    col = c - c % 3;
    /*if r%3 = 0 correct subgrid if r%3 = 1 at pos 1||4||7 move 1 pos back
    if r%3=2 at pos 2||5||8 move 2 pos back.*/
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            grid_remove_choice(g, i + row, j + col, n);
        }
    }
}

int check_if_done(Grid_T g, int zero_count)
{
    if (zero_count == 0)
    {
        return 0;
    }
    else
    {
        sudoku_solve(g, zero_count);
    }
    return 1;
}

Grid_T sudoku_solve(Grid_T g, int zero)
{
    int i, j, n;

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {

            for (n = 1; n <= 9; n++)
            {
                if (grid_choice_is_valid(g, i, j, n))
                {
                    if (grid_read_count(g, i, j) == 1)
                    {
                        grid_update_value(&g, i, j, n);
                        if (sudoku_is_correct(g))
                        {
                            grid_update_value(&g, i, j, 0);
                        }
                        sudoku_eliminate_choice(&g, i, j, n);
                    }
                }
            }
            if (grid_read_value(g, i, j) != 0)
            {
                zero--;
            }
        }
    }

    if (zero != 0 && zero > 0)
    {
        sudoku_init_choices(&g);
        sudoku_solve(g, zero);
    }

    return g;
}

int main(int argc, char **argv)
{
    Grid_T grid;
    Grid_T tmp_grid;
    Grid_T solved;
    int els;

    switch (argc)
    {

    case 2:
        /*with 2 args, input must be  -c: */
        if (!(strcmp(argv[1], "-c") == 0))
        {
            fprintf(stderr, "Error: wrong command\n");
            break;
        }

        grid = sudoku_read();
        tmp_grid = grid;
        sudoku_print(stderr, grid);
        /*check if correct*/

        if (sudoku_is_correct(grid) == 0)
        {
            fprintf(stderr, "PUZZLE IS CORRECT!\n");
        }
        else
        {
            fprintf(stderr, "ERROR: PUZZLE IS NOT CORRECT \n");
        }

        break;

    case 4:
        /*input is -g: */
        if (!(strcmp(argv[1], "-g") == 0) || !(strcmp(argv[3], "-u") == 0))
        {
            fprintf(stderr, "Error: wrong command\n");

            break;
        }
        else
        {
            els = atoi(argv[2]);
            /**/
            fprintf(stderr, "ola good me testtttt\n");
            fprintf(stderr, "num of els is: %d\n", els);
        }

        break;

    case 1:
        /*input w/o parameters:
        -read, print input puzzle.
        -solve puzzle
        -check if correct.
        -solve,check if: 1(unique) , none , ore more solutions
         error solutions/no solution found
         if solution exists print possible solution. */
        fprintf(stderr, "Input puzzle:\n");
        grid = sudoku_read();
        sudoku_print(stderr, grid);

        fprintf(stderr, "Puzzle has NO dupes, can be solved.\n");
        sudoku_init_choices(&grid);
        solved = sudoku_solve(grid, 81);
        fprintf(stderr, "SOLVED PUZZLE IS:\n");
        sudoku_print(stderr, solved);

        break;
    }

    return 0;
}
