#ifndef MAZE_H
#define MAZE_H

#define MAZE_SIZE 15
#define NILL 0
#define WALL 1
#define ROAD 2
#define START_POS 3

struct background{
    int **map;
    struct point startPos;
    struct point currentPos;
};

struct point nextPoint(struct background *tmp);
void initialMap(struct background *tmp);
void showMap(struct background *tmp);
#endif