#ifndef __WORLD__C__
#define __WORLD__C__

#include "data.c"

oz_World oz_buildWorld(int n_rooms)
{
	oz_CharData cds[4] = {
		{161, DefaultColors.GREEN_ON_DARK_GREEN},
		{140, DefaultColors.GREEN_ON_DARK_GREEN},
		{141, DefaultColors.GREEN_ON_DARK_GREEN},
		{139, DefaultColors.GREEN_ON_DARK_GREEN},
	};
	oz_World w;
	w.rooms = alloc_array(oz_Room, n_rooms);
	int rnd = 0;
	char c = 0;
	int tmp = 1;
	oz_CharData cd;
	cd.ascii = ' ';
	cd.color = DefaultColors.GREEN_ON_DARK_GREEN;
	for (int i = 0; i < n_rooms; i++)
	{
		w.rooms[i].width = WIDTH;
		w.rooms[i].height = HEIGHT;
		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				rnd = rand() % 100;
				if (rnd > 95)
				{
					w.rooms[i].map[x][y].sprite = oz_buildRndAnimation(4, 1, 5, true, true);
					oz_fillAnimation(&(w.rooms[i].map[x][y].sprite), cds);
				}
				else
				{
					w.rooms[i].map[x][y].sprite = oz_buildStaticAnimation(cd);
				}
				w.rooms[i].map[x][y].solid = false;
			}
		}
	}
	return w;
}

#endif
