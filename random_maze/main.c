#include <stdio.h>
#include "point.h"
#include "maze.h"

int main(void)
{
	struct background maze;
	initialMap(&maze);
	showMap(&maze);
}