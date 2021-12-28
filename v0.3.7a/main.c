#include "OZCore.c"

oz_Entity player;
DIRECTION current_dir = NONE;

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
	world = oz_buildWorld(1, false);
	oz_BitBuffer buffer = oz_readBitBufferFromFile("world2.w");
	world.rooms[0] = oz_deserializeRoom(buffer);
	oz_destroyBitBuffer(&buffer);

	buffer = oz_readBitBufferFromFile("player.p");
	player = oz_deserializeEntity(buffer);
	oz_destroyBitBuffer(&buffer);
}

void onFrame(float delta, oz_GfxBuffer* buffer)
{
	oz_move(&player, current_dir);
	oz_drawEntity(buffer, &player);
}

int main(int argc, char** argv)
{
	oz_Init();
	oz_setLogRealTimeUpdate(true);
	oz_setWindowTitle("OmniaZERO - v0.3.7a >>> DOS Game Test");
	oz_setKeyPressed(&onKeyPressed);
	oz_setKeyReleased(&onKeyReleased);
	oz_setFrameCallback(&onFrame);

	loadTestData();

	oz_startGameLoop();

	return 0;
}
