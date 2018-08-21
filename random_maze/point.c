#include <stdlib.h>
#include <time.h>
#include "point.h"
#include "maze.h"

struct point initialPoint(const int x, const int y, const int handle, const struct point* before)
{
    struct point temp;
    temp.x = x;
    temp.y = y;
    temp.handle = handle;
    temp.beforePoint = before;

    return temp;
}

struct point randPoint(void)
{
    srand((unsigned int)time(NULL));

    struct point temp = initialPoint( rand() % (MAZE_SIZE-2) + 1, rand() % (MAZE_SIZE-2) + 1, STAY, NULL);

    return temp;
}

struct point* handlePoint(struct point *temp, const int handle)
{
    switch (handle) {
        case UP:    temp->y--; break;
        case DOWN:  temp->y++; break;
        case LEFT:  temp->x--; break;
        case RIGHT: temp->x++; break;
    }
    return temp; //maybe use
}

struct point nextPoint(const struct point *temp) //temp = current
{
    srand((unsigned int)time(NULL));
    struct point next = *temp;
    handlePoint(&next, (rand() % 4 + 1));

    return next;
}