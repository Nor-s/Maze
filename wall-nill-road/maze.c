#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <Windows.h>
#include "point.h"
#include "maze.h"
#include "control.h"

//#define DEBUG

// i == y,  j == x
bool checkNil(struct background *tmp)
{
	int i, j;

	for (i = 1; i < MAZE_SIZE - 1; i++) {
		for (j = 1; j < MAZE_SIZE - 1; j++) {
			if (*(*(tmp->map + i) + j) == NILL)
				return true;
		}
	}
	return false;
}
void makeOneWall(int x, int y, int **map)
{
	if (map[y][x] == NILL)
		map[y][x] = WALL;
}
void makeAdjWall(struct background *tmp, int handle)
{
	switch (handle) {
	case UP:
		makeOneWall(tmp->currentPos.x + 1, tmp->currentPos.y, tmp->map);
		makeOneWall(tmp->currentPos.x - 1, tmp->currentPos.y, tmp->map);
		makeOneWall(tmp->currentPos.x, tmp->currentPos.y + 1, tmp->map); break;
	case DOWN:
		makeOneWall(tmp->currentPos.x + 1, tmp->currentPos.y, tmp->map);
		makeOneWall(tmp->currentPos.x - 1, tmp->currentPos.y, tmp->map);
		makeOneWall(tmp->currentPos.x, tmp->currentPos.y - 1, tmp->map); break;
	case LEFT:
		makeOneWall(tmp->currentPos.x + 1, tmp->currentPos.y, tmp->map);
		makeOneWall(tmp->currentPos.x, tmp->currentPos.y + 1, tmp->map);
		makeOneWall(tmp->currentPos.x, tmp->currentPos.y - 1, tmp->map); break;
	case RIGHT:
		makeOneWall(tmp->currentPos.x - 1, tmp->currentPos.y, tmp->map);
		makeOneWall(tmp->currentPos.x, tmp->currentPos.y + 1, tmp->map);
		makeOneWall(tmp->currentPos.x, tmp->currentPos.y - 1, tmp->map); break;
	}
}
/* a better method: (around == nill -> push stack)  & (if !checkNext -> pop) */
/* another method:  linked list: start <- next <- nextnext......             */
struct point nextPoint(struct background *tmp)
{
	int tmphandle = rand() % 4 + 1;
	struct point next = tmp->currentPos;

	while (!checkNext(next.x, next.y, tmp->map, NILL)) {

		next = findDril(tmp->map);
		tmp->map[next.y][next.x] = ROAD;
#ifdef DEBUG
		gotoxy(70, 9);
		printf("dril x: %d, y: %d, handle: %d\n", next.x, next.y, next.handle);
#endif
	}
	while (checkNextNill(next.x, next.y, tmphandle, tmp->map)) {
		tmphandle = rand() % 4 + 1;
	}
	makeAdjWall(tmp, tmphandle);

	tmp->currentPos = handlePoint(next.x, next.y, tmphandle);
}

/* check all map -> exist NILL?            */
/* if true -> choice nextpoint -> set Road */
void mazeCons(struct background *tmp)
{
#ifdef DEBUG
	showMap(tmp);
	gotoxy(70, 5);
	printf("startpoint handle: %d\n", tmp->currentPos.handle);
#endif
	while (checkNil(tmp)) {
		nextPoint(tmp);
#ifdef DEBUG
		gotoxy(70, 6);
		printf("nextpoint handle: %d\n", tmp->currentPos.handle);
#endif
		if (tmp->map[tmp->currentPos.y][tmp->currentPos.x] == NILL) {
			tmp->map[tmp->currentPos.y][tmp->currentPos.x] = ROAD;
#ifdef DEBUG
			gotoxy(70, 7);
			printf("Draw Road: %d, %d\n", tmp->currentPos.x, tmp->currentPos.y);
#endif
		}
#ifdef DEBUG
		gotoxy(70, 8);
		printf("current Road: %d, %d\n", tmp->currentPos.x, tmp->currentPos.y);
		showCurrentMap(tmp);
#endif
	}
}

void initialMap(struct background *tmp)
{
	int i, j;
	tmp->map = (int **)malloc(MAZE_SIZE * sizeof(int *));
	for (i = 0; i < MAZE_SIZE; i++)
		tmp->map[i] = (int *)malloc(MAZE_SIZE * sizeof(int));


	for (i = 0; i < MAZE_SIZE; i++)
		for (j = 0; j < MAZE_SIZE; j++)
			if (i == 0 || j == 0 || i == MAZE_SIZE - 1 || j == MAZE_SIZE - 1)
				*(*(tmp->map + i) + j) = WALL;
			else
				*(*(tmp->map + i) + j) = NILL;
	tmp->currentPos = tmp->startPos = startPoint();
	*(*(tmp->map + tmp->startPos.y) + tmp->startPos.x) = START_POS;

	mazeCons(tmp);
	tmp->endPos = initialPoint(tmp->currentPos.x, tmp->currentPos.y, 0);
	*(*(tmp->map + tmp->currentPos.y) + tmp->currentPos.x) = END_POS;
}

void showMap(struct background *tmp)
{
	int i, j;

	for (i = 0; i < MAZE_SIZE; i++) {
		for (j = 0; j < MAZE_SIZE; j++) {

			gotoxy(j * 2, i);
			switch (*(*(tmp->map + i) + j)) {
			case NILL:      printf(_NILL);  break;
			case ROAD:      printf(_ROAD);  break;
			case WALL:      printf(_WALL);  break;
			case START_POS: printf(_START);  break;
			case END_POS:   printf(_END);  break;
			}
		}
	}
}

void showCurrentMap(struct background *tmp)
{
	int i, j;

	for (i = tmp->currentPos.y - 1; i < tmp->currentPos.y + 2; i++) {
		for (j = tmp->currentPos.x - 1; j < tmp->currentPos.x + 2; j++) {
			gotoxy(j * 2, i);
			switch (*(*(tmp->map + i) + j)) {
			case NILL:      printf(_NILL);  break;
			case ROAD:      printf(_ROAD);  break;
			case WALL:      printf(_WALL);  break;
			case START_POS: printf(_START);  break;
			case END_POS:   printf(_END);  break;
			}
		}
	}
}