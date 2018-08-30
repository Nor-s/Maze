#ifndef MAZE_H
#define MAZE_H

#define MAZE_SIZE 20
#define NILL 0
#define WALL 1
#define ROAD 2
#define START_POS 3
#define END_POS 4

#define _WALL "[]"
#define _ROAD "  "
#define _START "SS"
#define _END "GG"
#define _PLAYER "><"
#define _NILL ".."

struct background {
	int **map;
	struct point startPos;
	struct point currentPos;
	struct point endPos;
};

struct point nextPoint(struct background *tmp);
void initialMap(struct background *tmp);
void showMap(struct background *tmp);
void showCurrentMap(struct background *tmp);
#endif