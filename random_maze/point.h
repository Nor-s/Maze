#ifndef POINT_H
#define POINT_H

#define UP     1
#define DOWN   2
#define LEFT   3
#define RIGHT  4

struct point {
	int x;
	int y;
	int handle;
};
struct stack{
    int size;
    int top;
    struct point *stack;
};

struct point initialPoint(int x, int y, int handle);
struct point startPoint(void);
struct point handlePoint(int x, int y, int handle);
bool checkNext(int x, int y, int **map);
bool checkNextNill(int x, int y, int handle, int **map);
struct point findDril(int **map);

#endif