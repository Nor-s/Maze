#ifndef PLAYER_H
#define PLAYER_H

#define LEFTKEY 'h'
#define DOWNKEY 'j'
#define UPKEY 'k'
#define RIGHTKEY 'l'

struct object {
	struct point current;
	int sight;
	struct object* link;
};

struct object initialPlayer(struct point *startPos);
bool gameStart(struct background *back, struct object *player);
#endif