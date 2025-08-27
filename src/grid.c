#include "grid.h"

void grid_update_value(Grid_T *g, int i, int j, int n)
{
    g->elts[i][j].val = n;
}

int grid_read_value(Grid_T g, int i, int j)
{
    return g.elts[i][j].val;
}

void grid_set_choice(Grid_T *g, int i, int j, int n)
{
    g->elts[i][j].choices.num[n] = 1;
}
void grid_clear_choice(Grid_T *g, int i, int j, int n)
{
    g->elts[i][j].choices.num[n] = 0;
}

int grid_choice_is_valid(Grid_T g, int i, int j, int n)
{
    if (g.elts[i][j].choices.num[n] == 1)
    {
        return 1;
    }
    return 0;
}

/* remove n from choices of elt i,j and adjust count only if n is a
   valid choice for elt i,j */
void grid_remove_choice(Grid_T *g, int i, int j, int n)
{

    if (grid_choice_is_valid(*g, i, j, n))
    {
        g->elts[i][j].choices.count = g->elts[i][j].choices.count - 1;
        grid_clear_choice(g, i, j, n);
    }
    else
    {
        printf("error removing\n");
    }
}

int grid_read_count(Grid_T g, int i, int j)
{
    return g.elts[i][j].choices.count;
}
void grid_set_count(Grid_T *g, int i, int j)
{
    g->elts[i][j].choices.count = g->elts[i][j].choices.count + 1;
}
void grid_clear_count(Grid_T *g, int i, int j)
{
    g->elts[i][j].choices.count = 0;
}

int grid_read_unique(Grid_T g)
{
    return g.unique;
}
void grid_set_unique(Grid_T *g)
{
    g->unique = 1;
}
void grid_clear_unique(Grid_T *g)
{
    g->unique = 0;
}
