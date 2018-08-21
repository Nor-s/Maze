#ifndef POINT_H
#define POINT_H

#define STAY  0
#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4

struct point{
    int x;
    int y;
    int handle;
    struct point* beforePoint;
};

struct point randPoint(void);
struct point nextPoint(const struct point *temp);

#endif