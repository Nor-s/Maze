#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "point.h"
#include "maze.h"

struct point initialPoint(int x,  int y, int handle)
{
    struct point temp;
    temp.x = x;
    temp.y = y;
    temp.handle = handle;

    return temp;
}

struct point startPoint(void)
{
    struct point temp = initialPoint( rand() % (MAZE_SIZE-2) + 1, rand() % (MAZE_SIZE-2) + 1, rand()%4 + 1);

    return temp;
}

struct point handlePoint(int x, int y, int handle)
{
    switch (handle) {
        case UP:    y--; break;
        case DOWN:  y++; break;
        case LEFT:  x--; break;
        case RIGHT: x++; break;
    }

    return  initialPoint(x, y, handle);
}

//can't find NILL -> false
bool checkNext(int x, int y, int **map)
{
    if (map[y][x + 1] == NILL || map[y][x - 1]  == NILL  ||
        map[y + 1][x] == NILL || map[y - 1][x] == NILL)
       return true;
    return false;
}

//it is NILL -> true
bool checkNextNill( int x, int y,int handle,int **map)
{
    struct point temp = initialPoint(x, y, handle);
    temp = handlePoint(temp.x, temp.y, handle);
    
    if (*(*(map + temp.y) + temp.x) == NILL)
        return false;
    return true;
}

struct point findDril(int **map)
{
    int i, j;

    for (i = 1; i < MAZE_SIZE - 1 ; i++) {
        for (j = 1; j < MAZE_SIZE - 1 ; j++) {
            if (*(*(map + i) + j) == WALL && checkNext(j, i, map))
               return initialPoint(j, i, rand()%4+1);
        }
    }
}
