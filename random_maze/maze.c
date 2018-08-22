#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <Windows.h>
#include "point.h"
#include "maze.h"


void gotoxy(short x, short y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// i == y,  j == x
bool checkNil(struct background *tmp)
{
    int i, j;

    for (i = 1; i < MAZE_SIZE - 1 ; i++) {
        for (j = 1; j < MAZE_SIZE - 1 ; j++){
            if (*(*(tmp->map + i)+ j) == NILL)
                return true;    
        }
    }
    return false;
}
void makeOneWall( int x,  int y, int **map)
{
    if (map[y][x] == NILL)
        map[y][x] = WALL;
}
void makeAdjWall(struct background *tmp, int handle)
{
    switch(handle) {
        case UP:    
                    makeOneWall(tmp->currentPos.x+1,tmp->currentPos.y, tmp->map); 
                    makeOneWall(tmp->currentPos.x-1,tmp->currentPos.y, tmp->map); 
                    makeOneWall(tmp->currentPos.x,tmp->currentPos.y+1, tmp->map); break;
        case DOWN:
                    makeOneWall(tmp->currentPos.x+1,tmp->currentPos.y, tmp->map); 
                    makeOneWall(tmp->currentPos.x-1,tmp->currentPos.y, tmp->map); 
                    makeOneWall(tmp->currentPos.x,tmp->currentPos.y-1, tmp->map); break;
        case LEFT:
                    makeOneWall(tmp->currentPos.x+1,tmp->currentPos.y, tmp->map); 
                    makeOneWall(tmp->currentPos.x,tmp->currentPos.y+1, tmp->map); 
                    makeOneWall(tmp->currentPos.x,tmp->currentPos.y-1, tmp->map); break;
        case RIGHT:
                    makeOneWall(tmp->currentPos.x-1,tmp->currentPos.y, tmp->map); 
                    makeOneWall(tmp->currentPos.x,tmp->currentPos.y+1, tmp->map); 
                    makeOneWall(tmp->currentPos.x,tmp->currentPos.y-1, tmp->map); break;
    }
}
struct point nextPoint(struct background *tmp)
{
    int tmphandle = rand() % 4 + 1;
    struct point next = tmp->currentPos;

    while (!checkNext(next.x, next.y, tmp->map)) {            // a better method: (around == nill -> push stack)  & (if !check -> pop) 
                                        // if "next" is start point -> Look for WALL adjacent to NILL
           printf("!dril: %d\n", next.handle);
           next = findDril(tmp->map);
           tmp->map[next.y][next.x] = ROAD;
    }
    while (checkNextNill(next.x, next.y, tmphandle, tmp->map)) {
        tmphandle = rand() % 4 + 1;
    }
     makeAdjWall(tmp,tmphandle);                                    //order change ->        

    tmp->currentPos = handlePoint(next.x, next.y, tmphandle); ;        // it's now Road & around = wall
}
void mazeCons(struct background *tmp)
{
    printf("startpoint handle: %d\n", tmp->currentPos.handle);
   // makeAdjWall(tmp);
    while(checkNil(tmp)) {
        nextPoint(tmp);
        printf("nextpoint handle: %d\n", tmp->currentPos.handle);
        if (tmp->map[tmp->currentPos.y][tmp->currentPos.x] == NILL){
            tmp->map[tmp->currentPos.y][tmp->currentPos.x] = ROAD;
            printf("Draw Road: %d, %d\n",tmp->currentPos.x ,tmp->currentPos.y);
        }
        else{
             printf("current Road: %d, %d\n",tmp->currentPos.x ,tmp->currentPos.y);
        }
        showMap(tmp);
    }
}

void initialMap(struct background *tmp)
{
    int i, j;
    tmp->map = (int **)malloc(MAZE_SIZE * sizeof(int *));
    for (i = 0; i < MAZE_SIZE; i++) 
        tmp->map[i] = (int *)malloc(MAZE_SIZE * sizeof(int));
    

    for (i = 0; i < MAZE_SIZE ; i++) 
        for (j =0; j < MAZE_SIZE ; j++) 
            if (i == 0 || j== 0 || i == MAZE_SIZE - 1 || j == MAZE_SIZE -1)
                *(*(tmp->map + i)+ j) = WALL;
            else
                *(*(tmp->map + i)+ j) = NILL;
    tmp->currentPos = tmp->startPos = startPoint();
    *(*(tmp->map + tmp->startPos.y) + tmp->startPos.x) = START_POS;
 
    mazeCons(tmp);
    *(*(tmp->map + tmp->currentPos.y) + tmp->currentPos.x) = END_POS;
}

void showMap(struct background *tmp)   //goto xy
{
    int i, j;

    for (i = 0; i < MAZE_SIZE ; i++) {
        for (j = 0; j < MAZE_SIZE ; j++){
            //gotoxy(j * 2, i);
            switch (*(*(tmp->map + i)+ j)) {
                case NILL:      printf("..");  break;
                case ROAD:      printf("  ");  break;
                case WALL:      printf("[]");  break;
                case START_POS: printf("SS");  break;
                case END_POS:   printf("GG");  break;
            }
        }
        putchar('\n');
    }
}