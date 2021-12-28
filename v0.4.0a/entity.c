#ifndef __ENTITY__C__
#define __ENTITY__C__

#include "data.c"

oz_PointF oz_getEntityRelativePosition(oz_Entity* ent)
{
	oz_PointF p;
	p.x = ent->position.x;
	p.y = ent->position.y - 1.0f;
	return p;
}

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
	oz_PointF rp = oz_getEntityRelativePosition(e);
	if (world.rooms[current_room].map[(int)(rp.x + nx)][(int)(rp.y + ny)].solid)
		return false;
	e->position.x += nx;
	e->position.y += ny;
	return true;
}

#endif
