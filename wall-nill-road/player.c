#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>
#include <string.h>
#include <conio.h>
#include "control.h"
#include "point.h"
#include "maze.h"
#include "player.h"


struct object initialPlayer(struct point *startPos)
{
	struct object player;
	player.current = *startPos;
	player.current.handle = NILL;
	player.link = NULL;
	player.sight = 8;

	return player;
}

void showDown(struct background *back, struct object *player)
{
	int i, j;
	for (i = player->current.y; i < player->current.y + player->sight; i++) {
		for (j = player->current.x - 1; j < player->current.x + 2; j++) {
			showObject(j, i, back);
			if (*(*(back->map + i) + player->current.x) == WALL) {
				printf("[]");
				return;
			}
		}
	}
}
void showUp(struct background *back, struct object *player)
{
	int i, j;
	for (i = player->current.y; i > player->current.y - player->sight; i--) {
		for (j = player->current.x - 1; j < player->current.x + 2; j++) {
			showObject(j, i, back);
			if (*(*(back->map + i) + player->current.x) == WALL) {
				printf("[]");
				return;
			}
		}
	}
}
void showRight(struct background *back, struct object *player)
{
	int i, j;
	for (j = player->current.x; j < player->current.x + player->sight; j++) {
		for (i = player->current.y - 1; i < player->current.y + 2; i++) {
			showObject(j, i, back);
			if (*(*(back->map + player->current.y) + j) == WALL) {
				gotoxy(j * 2, player->current.y);
				printf("[]");
				return;
			}
		}
	}
}
void showLeft(struct background *back, struct object *player)
{
	int i, j;
	for (j = player->current.x; j > player->current.x - player->sight; j--) {
		for (i = player->current.y - 1; i < player->current.y + 2; i++) {
			showObject(j, i, back);
			if (*(*(back->map + player->current.y) + j) == WALL) {
				gotoxy(j * 2, player->current.y);
				printf("[]");
				return;
			}
		}
	}
}
void showSightPlayer(struct background *back, struct object *player)
{
	system("cls");
	switch (player->current.handle) {
	case UPKEY:    showUp(back, player); break;
	case DOWNKEY:  showDown(back, player); break;
	case LEFTKEY:  showLeft(back, player); break;
	case RIGHTKEY: showRight(back, player); break;
	}
}

void moveObject(struct object *player)
{
	switch (player->current.handle) {
	case UPKEY:    player->current.y--; break;
	case DOWNKEY:  player->current.y++; break;
	case LEFTKEY:  player->current.x--; break;
	case RIGHTKEY: player->current.x++; break;
	}
}

bool checkWall(struct background *back, struct object tmp)
{
	moveObject(&tmp);
#ifdef DEBUG
	gotoxy(60, 2);
	printf("tmpObject x, y, handle: %3d %3d %3d", tmp.current.x, tmp.current.y, tmp.current.handle);
#endif
	if (back->map[tmp.current.y][tmp.current.x] == WALL) {
#ifdef DEBUG
		gotoxy(60, 4);
		printf("map: %d", back->map[tmp.current.y][tmp.current.x]);
#endif
		return true;
	}
	else
		return false;
}

bool gameStart(struct background *back, struct object *player)
{
	char handle;
	struct object tmpObject;
	tmpObject.current = player->current;

	while (1) {
		handle = getch();
		tmpObject.current = player->current;
		tmpObject.current.handle = handle;
		if (!(handle == UPKEY || handle == DOWNKEY || handle == LEFTKEY || handle == RIGHTKEY))
			continue;
		if (checkWall(back, tmpObject))
			continue;

		player->current.handle = handle;
		moveObject(player);
		showSightPlayer(back, player);
		back->currentPos = player->current;
		showMap(back->currentPos.y - 1, back->currentPos.y + 2, back->currentPos.x - 1, back->currentPos.x + 2, back);
#ifdef DEBUG
		gotoxy(60, 1);
		printf("player x, y, handle: %3d %3d %3d", player->current.x, player->current.y, player->current.handle);
#endif
		gotoxy(player->current.x * 2, player->current.y);
		printf("><");
		if (back->endPos.x == player->current.x &&back->endPos.y == player->current.y)
			return true;
	}
	return false;
}