#ifndef POINT_H
#define POINT_H

struct point{
    int x;
    int y;
    int handle;
    struct point* beforePoint;
};



#endif