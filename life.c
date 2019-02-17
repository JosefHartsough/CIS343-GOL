
//*********************************************************
//Filename: life.c
//
//Author: Josef Hartsough, Jarod Collier, Maz Ashgar
//*********************************************************

#include <stdlib.h>
#include <stdio.h>
#include "life.h"
/*
 * get_grid creates new memory for a "grid".
 * x is the height and y is the width.
 */
char** get_grid(int x, int y) {
    int i;
    // allocate space for data
    char *data = malloc(sizeof(char) * x * y);
    // create array of pointers to first elem in each 2D row
    char **ptr_array = malloc(sizeof(char*) * x);
    for (i = 0; i < x; i++) {
        ptr_array[i] = data + (i*y);

    }
    return ptr_array;

}
/*
 * print_grid attempts to print an x height
 * by y width grid stored at the location
 * provided by grid
 */
void print_grid(int x, int y, char** grid) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            printf("%01X ", (char)grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
/*
 * mutate takes a grid and mutates that grid
 * according to Conway's rules.  A new grid
 * is returned.
 */
char** mutate(int x, int y, char** grid) {
    // Every cell interacts with its eight neighbours
    // that are horizontally, vertically, or diagonally adjacent
    char** new_grid = get_grid(x, y); // creates new blank slate to be updated
    // grid points to previous game state, new_grid points to new game state
    // update new game state according to rules applied to previous game state
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            int live_neighbors = get_neighbors(i, j, x, y, grid); // count live neighbors
            // live cell with less than two live neighbors dies
            if (grid[i][j] != 0 && live_neighbors < 2) { new_grid[i][j] = 0; }
            else
                // live cell with two or three live neighbors lives
            if (grid[i][j] != 0 && live_neighbors <= 3 ) { new_grid[i][j] = 1; }
            else
                // live cell with more than three neighbors dies
            if (grid[i][j] != 0 && live_neighbors > 3) { new_grid[i][j] = 0; }
            else
                // dead cell with three live neighbors becomes live
            if (grid[i][j] == 0 && live_neighbors == 3) { new_grid[i][j] = 1; }
            else
                // if we get this far then no changes required, so just copy this element
                new_grid[i][j] = grid[i][j];  // copy element from old game state to new game state
        }
    }
    // no longer need previous game state so free related heap allocations
    free(*grid); // free the memory that contains the actual data rows
    free(grid);  // free the memory that contains the pointers to the data rows
    return new_grid; // return pointer to newly updated game state

}
/* get_neighbors is a helper method that returns
 * the number of live neighbors a cell has.
 */
int get_neighbors(int i, int j, int x, int y, char** grid) {
    // Each cell has 8 neighbors
    int live_neighbors = 0;
    // 3 neighbors on row above cell
    if (i-1 >= 0 && j-1 >= 0 && grid[i-1][j-1] > 0) live_neighbors++;   // test cell up-left
    if (i-1 >= 0             && grid[i-1][j]   > 0) live_neighbors++;   // test cell up
    if (i-1 >= 0 && j+1 < y  && grid[i-1][j+1] > 0) live_neighbors++;   // test cell up-right
    // 2 neighbors on same row as cell
    if (j-1 >= 0             && grid[i][j-1] > 0) live_neighbors++;     // test cell left
    if (j+1 <  y             && grid[i][j+1] > 0) live_neighbors++;     // test cell right
    // 3 neighbors on row below cell
    if (i+1 < x && j-1 >= 0  && grid[i+1][j-1] > 0) live_neighbors++;    // test cell down-left
    if (i+1 < x              && grid[i+1][j] > 0)   live_neighbors++;    // test cell down
    if (i+1 < x && j+1 < y   && grid[i+1][j+1] > 0) live_neighbors++;    // test cell down-right
    return live_neighbors;
}
