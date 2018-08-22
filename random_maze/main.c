#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "point.h"
#include "maze.h"

int main(void)
{
	srand(time(NULL));
	struct background maze;
	initialMap(&maze);
	showMap(&maze);
}