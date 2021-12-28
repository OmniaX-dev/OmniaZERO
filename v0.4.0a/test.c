#include "OZCore.c"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("Wrong number of arguments.\n");
		return 1;
	}
	oz_BitBuffer buffer = oz_readBitBufferFromFile(argv[1]);
	int id = buffer.data[0].bits;
	if (id == OZ_ID_ROOM)
	{
		oz_Room room = oz_deserializeRoom(buffer);
		printf("%d - %d\n", room.width, room.height);
	}
	else
	{
		printf("Unknown OZ file type.\n");
		return 2;
	}
	return 0;
}
