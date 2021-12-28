#include "OZCore.c"

oz_Entity player;
DIRECTION current_dir = NONE;
oz_MessageBox msgbox;

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
	oz_BitBuffer buffer = oz_readBitBufferFromFile("world.oz");
	world.rooms[0] = oz_deserializeRoom(buffer);
	oz_destroyBitBuffer(&buffer);

	buffer = oz_readBitBufferFromFile("player.oz");
	player = oz_deserializeEntity(buffer);
	oz_destroyBitBuffer(&buffer);

	msgbox = oz_buildMessageBox(20, 10);
	oz_String str = oz_buildString("CIAO CICCIO adjdif p", DefaultColors.DARK_GREEN_ON_GRAY);
	oz_setMessageBoxText(&msgbox, str);

	for (int x = 0; x < ROOM_WIDTH; x++)
	{
		for (int y = 0; y < ROOM_HEIGHT; y++)
		{
			oz_Logi(world.rooms[0].map[x][y].type, "TYPE", true);
		}
	}
}

void onFrame(float delta, oz_GfxBuffer* buffer)
{
	oz_move(&player, current_dir);
	oz_drawEntity(buffer, &player);
	//oz_drawMessageBox(buffer, &msgbox, 10, 10);
}

int main(int argc, char** argv)
{
	oz_Init();
	oz_setLogRealTimeUpdate(true);
	oz_setWindowTitle("OmniaZERO - v0.4.0a >>> DOS Game Test");
	oz_setKeyPressed(&onKeyPressed);
	oz_setKeyReleased(&onKeyReleased);
	oz_setFrameCallback(&onFrame);

	loadTestData();

	oz_startGameLoop();

	return 0;
}
