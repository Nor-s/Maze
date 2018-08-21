#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "point.h"
#include "maze.h"
// i == y,  j == x
bool checkNil(const struct background* tmp)
{
    int i, j;

    for (i = 1; i < MAZE_SIZE ; i++) {
        for (j = 1; j < MAZE_SIZE ; j++){
            if (*(*(tmp->map + i)+ j) == NILL)
                return true;    
        }
    }
    return false;
}

void mazeCons(struct background* tmp)
{
    while(checkNil(tmp)) {

    }
}

void initialMap(struct background* tmp)
{
    int i, j;
    tmp->map = (int **)malloc(MAZE_SIZE * sizeof(int *));
    for (i = 0; i < MAZE_SIZE; i++) 
        tmp->map[i] = (int *)malloc(MAZE_SIZE * sizeof(int));
    

    for (i = 0; i < MAZE_SIZE ; i++) 
        for (j =0; j < MAZE_SIZE ; j++) 
            if (i == 0 || j== 0 || i == MAZE_SIZE - 1 || j == MAZE_SIZE -1)
                *(*(tmp->map + i)+ j) = WALL;
            else
                *(*(tmp->map + i)+ j) = NILL;
    tmp->currentPos = tmp->startPos = randPoint();
    *(*(tmp->map + tmp->startPos.y)+ tmp->startPos.x) = START_POS;

    mazeCons(tmp);
}

void showMap(const struct background *tmp) 
{
    int i, j;

    for (i = 0; i < MAZE_SIZE ; i++) {
        for (j = 0; j < MAZE_SIZE ; j++)
            switch (*(*(tmp->map + i)+ j)) {
                case NILL:      printf(".."); break;
                case ROAD:      printf("  "); break;
                case WALL:      printf("[]");  break;
                case START_POS: printf("SG");  break;
            }
        putchar('\n');
    }
}