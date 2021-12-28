#ifndef __ENTITY__C__
#define __ENTITY__C__

#include "data.c"

bool oz_move(oz_Entity* e, DIRECTION dir)
{
	float nx = 0, ny = 0;
	switch (dir) {
		case UP:
			ny -= (*delta * e->speed);
		break;
		case DOWN:
			ny += (*delta * e->speed);
		break;
		case LEFT:
			nx -= (*delta * e->speed);
		break;
		case RIGHT:
			nx += (*delta * e->speed);
		break;
		default:
			return false;
	}
	if (world.rooms[current_room].map[(int)(e->position.x + nx)][(int)(e->position.y + ny)].solid)
		return false;
	e->position.x += nx;
	e->position.y += ny;
	return true;
}

#endif
