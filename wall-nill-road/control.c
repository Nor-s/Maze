#include <Windows.h>
#include "control.h"

void gotoxy(short x, short y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}