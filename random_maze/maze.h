#ifndef MAZE_H
#define MAZE_H

#define MAZE_SIZE 15
#define NILL 0
#define WALL 1
#define ROAD 2
#define START_POS 3

struct maze{
    int **map;
    struct point startPos;
    struct point currentPos;
};

void initialMap(struct maze *tmp);
#endif