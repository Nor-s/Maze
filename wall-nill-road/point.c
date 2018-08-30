#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "point.h"
#include "maze.h"

struct point initialPoint(int x, int y, int handle)
{
	struct point temp;
	temp.x = x;
	temp.y = y;
	temp.handle = handle;

	return temp;
}

struct point startPoint(void)
{
	return initialPoint(rand() % (MAZE_SIZE - 2) + 1, rand() % (MAZE_SIZE - 2) + 1, rand() % 4 + 1);
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

//can't find what -> false
bool checkNext(int x, int y, int **map, int what)
{
	if (map[y][x + 1] == what || map[y][x - 1] == what ||
		map[y + 1][x] == what || map[y - 1][x] == what)
		return true;
	return false;
}

//it is NILL -> false
bool checkNextNill(int x, int y, int handle, int **map)
{
	struct point temp = initialPoint(x, y, handle);
	temp = handlePoint(temp.x, temp.y, handle);

	if (*(*(map + temp.y) + temp.x) == NILL)
		return false;
	return true;
}


struct point findDril(int **map)
{
	int i, j, count = 0;
	struct point pointAry[MAZE_SIZE * MAZE_SIZE];

	for (i = 1; i < MAZE_SIZE - 1; i++) {
		for (j = 1; j < MAZE_SIZE - 1; j++) {
			if (*(*(map + i) + j) == WALL && checkNext(j, i, map, NILL) && !checkNext(j, i, map, START_POS))
				pointAry[count++] = initialPoint(j, i, rand() % 4 + 1);
		}
	}

	return pointAry[rand() % count];
}