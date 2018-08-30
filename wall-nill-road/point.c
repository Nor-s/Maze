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
void initialStack(struct stack *tmpStack)
{
	tmpStack->size = MAZE_SIZE * MAZE_SIZE;
	tmpStack->top = 0;
	tmpStack->stack = (struct point*)malloc(tmpStack->size * sizeof(struct point));
}
void stackPush(struct stack *tmpStack, struct point tmpPoint)
{
	tmpStack->stack[tmpStack->top++] = tmpPoint;
}
struct point stackRandPop(struct stack *tmpStack)
{
	int randPos = rand() % tmpStack->top;
	struct point tmpPoint = tmpStack->stack[randPos];
	tmpStack->stack[randPos] = tmpStack->stack[tmpStack->top - 1];
	tmpStack->top--;
	return tmpPoint;
}

struct point findDril(int **map)
{
	int i, j;
	struct stack tmpStack;
	struct point tmpPoint;
	initialStack(&tmpStack);
	for (i = 1; i < MAZE_SIZE - 1; i++) {
		for (j = 1; j < MAZE_SIZE - 1; j++) {
			if (*(*(map + i) + j) == WALL && checkNext(j, i, map, NILL) && !checkNext(j, i, map, START_POS))
				stackPush(&tmpStack, initialPoint(j, i, rand() % 4 + 1));
		}
	}

	tmpPoint = stackRandPop(&tmpStack);
	free(tmpStack.stack);
	return tmpPoint;
}