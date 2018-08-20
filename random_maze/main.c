#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{
	srand(time(NULL));
	maze game(25);
	game.show_maze();
}