#ifndef MAZE_H
#define MAZE_H

#define MAZE_SIZE 20
#define NILL 0
#define WALL 1
#define ROAD 2
#define START_POS 3
#define END_POS 4

struct background {
	int **map;
	struct point startPos;
	struct point currentPos;
	struct point endPos;
};

struct point nextPoint(struct background *tmp);
void initialMap(struct background *tmp);
void showObject(int j, int i,  struct background *tmp);
void showMap(int ii, int ie, int jj, int je, struct background *tmp);
#endif