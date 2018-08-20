#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "maze.h"


void initialMap(struct maze* tmp)
{
    int i, j;
    tmp->map =(struct maze**)malloc(MAZE_SIZE * sizeof(struct maze*));
    for(i = 0; i < MAZE_SIZE; i++){
        *(tmp->map + i) = (struct maze*)malloc(MAZE_SIZE * sizeof(struct maze));
    }

    for(i = 0; i < MAZE_SIZE ; i++){
        for(j =0; j < MAZE_SIZE ; j++){
            if (i == 0 || j== 0 || i == MAZE_SIZE - 1 || j == MAZE_SIZE -1)
                *(*(tmp->map + i)+ j) = WALL;
            else
                *(*(tmp->map + i)+ j) = NILL;
        }
    }
}