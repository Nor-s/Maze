#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>
#include "point.h"
#include "maze.h"
#include "player.h"
#include "control.h"

#define DEBUG

int main(void)
{
	srand(time(NULL));

	struct background maze;
	initialMap(&maze);
#ifdef DEBUG
	showMap(0, MAZE_SIZE, 0, MAZE_SIZE, &maze);
#endif
	struct object player = initialPlayer(&maze.startPos);
	if (gameStart(&maze, &player)) {
		system("cls");
		showMap(0, MAZE_SIZE, 0, MAZE_SIZE, &maze);
		gotoxy(player.current.x * 2, player.current.y);
		printf("><");
		gotoxy(MAZE_SIZE - 2, MAZE_SIZE / 2);
		printf("CLEAR!!");
		Sleep(1000000);
	}
	else {
		system("cls");
		printf("YOU DIE\n");
	}
	//free(maze.map);
}