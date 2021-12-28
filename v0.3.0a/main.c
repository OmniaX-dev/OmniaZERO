#include "OZCore.c"

oz_Entity player;
DIRECTION current_dir = NONE;
oz_Animation water[100];
oz_String str;

void onKeyPressed(int key)
{
	switch (key)
	{
		case 'W':
			current_dir = UP;
		break;
		case 'S':
			current_dir = DOWN;
		break;
		case 'A':
			current_dir = LEFT;
		break;
		case 'D':
			current_dir = RIGHT;
		break;
		case VK_RETURN:
			oz_resetTypeWriterEffect(NULL);
		break;
		case 'E':
			current_room = (current_room == 0 ? 1 : 0);
		break;
		default:
		break;
	}
}

void onKeyReleased(int key)
{
	current_dir = NONE;
}

void loadTestData(void)
{
	player.position.x = 10;
	player.position.y = 10;
	player.speed = 20;

	world = oz_buildWorld(2);
	oz_CharData cd;
	cd.ascii = 205;
	cd.color = DefaultColors.PURPLE_ON_BLACK;
	for (int i = 0; i < WIDTH; i++)
	{
		world.rooms[0].map[i][0].sprite = oz_buildStaticAnimation(cd);
		world.rooms[0].map[i][0].solid = true;
		world.rooms[0].map[i][HEIGHT - 1].sprite = oz_buildStaticAnimation(cd);
		world.rooms[0].map[i][HEIGHT - 1].solid = true;
	}
	cd.ascii = 186;
	for (int i = 0; i < HEIGHT; i++)
	{
		world.rooms[0].map[0][i].sprite = oz_buildStaticAnimation(cd);
		world.rooms[0].map[0][i].solid = true;
		world.rooms[0].map[WIDTH - 1][i].sprite = oz_buildStaticAnimation(cd);
		world.rooms[0].map[WIDTH - 1][i].solid = true;
	}
	world.rooms[0].map[0][0].sprite.frames[0].ascii = 201;
	world.rooms[0].map[WIDTH - 1][0].sprite.frames[0].ascii = 187;
	world.rooms[0].map[0][HEIGHT - 1].sprite.frames[0].ascii = 200;
	world.rooms[0].map[WIDTH - 1][HEIGHT - 1].sprite.frames[0].ascii = 188;

	cd.ascii = 217;
	cd.color = DefaultColors.DARK_GREEN_T;
	world.rooms[1].map[20][20].sprite = oz_buildStaticAnimation(cd);
	world.rooms[1].map[20][20].solid = true;

	player.sprite = oz_buildAnimation(3, 10);
	oz_CharData cds[3] = {
		{'@', {BG_RED, FG_BLUE, true}},
		{'@', {BG_RED, FG_PINK, true}},
		{'@', {BG_RED, FG_LIGHT_GRAY, true}}
	};
	oz_fillAnimation(&(player.sprite), cds);

	str = oz_buildString("CICCIO CIAO", DefaultColors.WHITE_ON_BLACK);

	oz_CharData cds2[5] = {
		{',', {BG_BLUE, FG_DARK_BLUE, false}},
		{')', {BG_BLUE, FG_DARK_AQUA, false}},
		{' ', {BG_BLUE, FG_DARK_BLUE, false}},
		{'.', {BG_BLUE, FG_DARK_BLUE, false}},
		{' ', {BG_BLUE, FG_DARK_BLUE, false}}
	};
	for (int i = 0; i < 100; i++)
	{
		water[i] = oz_buildRndAnimation(5, 1, 10, true, true);
		oz_fillAnimation(&(water[i]), cds2);
	}
}

void onFrame(float delta, oz_GfxBuffer* buffer)
{
	oz_move(&player, current_dir);
	int x = 5, y = 5;
	for (int i = 0; i < 100; i++)
	{
		if (++x % 15 == 0)
		{
			x = 5;
			y++;
		}
		oz_drawCharData(buffer, oz_getAnimationFrame(&(water[i])), x, y);
	}
	oz_drawEntity(buffer, &player);
	oz_drawTypeWriterEffect(buffer, NULL, &str, 12, 12);
}

int main(int argc, char** argv)
{
	oz_Init();
	oz_setLogRealTimeUpdate(true);
	oz_setWindowTitle("OmniaZERO - v0.3.0a >>> DOS Game Test");
	oz_setKeyPressed(&onKeyPressed);
	oz_setKeyReleased(&onKeyReleased);
	oz_setFrameCallback(&onFrame);

	loadTestData();

	oz_startGameLoop();

	return 0;
}
