#ifndef __WORLD__C__
#define __WORLD__C__

#include "data.c"
#include "anim.c"

oz_Room oz_buildRoom(void)
{
	oz_Room room;
	oz_CharData cd = {' ', DefaultColors.BLACK_ON_BLACK};
	room.width = WIDTH;
	room.height = HEIGHT;
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			room.map[x][y].x = x;
			room.map[x][y].y = y;
			room.map[x][y].sprite = oz_buildStaticAnimation(cd);
			room.map[x][y].solid = false;
		}
	}
	return room;
}

oz_World oz_buildWorld(int n_rooms, bool build_rooms)
{
	oz_World w;
	w.rooms = alloc_array(oz_Room, n_rooms);
	if (!build_rooms)
		return w;
	for (int i = 0; i < n_rooms; i++)
		w.rooms[i] = oz_buildRoom();
	return w;
}

oz_CharData oz_getWorldAt(int x, int y)
{
	oz_Animation* tmp = NULL;
	if (x < 0 || y < 0 || x >= world.rooms[current_room].width ||  y >= world.rooms[current_room].height)
		tmp = &world.rooms[current_room].map[0][0].sprite;
	else
		tmp = &world.rooms[current_room].map[x][y].sprite;
	return tmp->frames[tmp->current_frame];
}

#endif
