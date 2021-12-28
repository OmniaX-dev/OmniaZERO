#ifndef __SERIAL__C__
#define __SERIAL__C__

#include <stdio.h>
#include "data.c"
#include "bits.c"
#include "clean.c"
#include "world.c"

oz_BitBuffer oz_serializeCharData(oz_CharData* cd)
{
	int size = 2;
	oz_Bits* serialized = alloc_array(oz_Bits, size);
	oz_writeFull(&serialized[0], OZ_ID_CHARDATA);
	oz_Bits* tmp = &(serialized[1]);
	oz_writeByte(tmp, 0, cd->ascii);
	oz_writeByte(tmp, 8, oz_getColorIndex(cd->color.bg_color));
	oz_writeByte(tmp, 16, oz_getColorIndex(cd->color.fg_color));
	oz_writeBit(tmp, 24, cd->color.transparent_bg);
	oz_BitBuffer buffer;
	buffer.data = serialized;
	buffer.size = size;
	return buffer;
}

oz_CharData oz_deserializeCharData(oz_BitBuffer buffer)
{
	oz_CharData cd;
	if (buffer.size != 2 || buffer.data[0].bits != OZ_ID_CHARDATA)
		return cd;
	cd.ascii = oz_readByte(&buffer.data[1], 0);
	cd.color.bg_color = oz_getColorFromIndex(oz_readByte(&buffer.data[1], 8));
	cd.color.fg_color = oz_getColorFromIndex(oz_readByte(&buffer.data[1], 16));
	cd.color.transparent_bg = oz_getBit(&buffer.data[1], 24);
	return cd;
}

oz_BitBuffer oz_serializeAnimation(oz_Animation* anim, bool store_id)
{
	int size = (store_id ? 2 : 1) + anim->frame_count;
	oz_Bits* serialized = alloc_array(oz_Bits, size);
	int i = 0;
	if (store_id)
		oz_writeFull(&serialized[i++], OZ_ID_ANIMATION);
	oz_Bits* tmp = &(serialized[i]);
	oz_writeNBits(tmp, 0, anim->frame_count, 5);
	oz_writeBit(tmp, 5, anim->_static);
	oz_writeByte(tmp, 6, anim->delay);
	oz_writeByte(tmp, 14, anim->random.min_delay);
	oz_writeByte(tmp, 22, anim->random.max_delay);
	oz_writeBit(tmp, 30, anim->random.rnd_delay);
	oz_writeBit(tmp, 31, anim->random.rnd_frames);
	oz_BitBuffer buffer;
	for (int i = 0; i < anim->frame_count; i++)
	{
		buffer = oz_serializeCharData(&(anim->frames[i]));
		serialized[i + (store_id ? 2 : 1)] = buffer.data[1];
		oz_destroyBitBuffer(&buffer);
	}
	buffer.data = serialized;
	buffer.size = size;
	return buffer;
}

oz_Animation oz_deserializeAnimation(oz_BitBuffer buffer)
{
	oz_Animation anim;
	if (buffer.size < 1 || buffer.data[0].bits != OZ_ID_ANIMATION)
		return anim;
	anim.current_frame = 0;
	anim._count = 0;
	anim.frame_count = oz_readNBits(&buffer.data[1], 0, 5);
	anim._static = oz_getBit(&buffer.data[1], 5);
	anim.delay = oz_readByte(&buffer.data[1], 6);
	anim.random.min_delay = oz_readByte(&buffer.data[1], 14);
	anim.random.max_delay = oz_readByte(&buffer.data[1], 22);
	anim.random.rnd_delay = oz_getBit(&buffer.data[1], 30);
	anim.random.rnd_frames = oz_getBit(&buffer.data[1], 31);
	oz_BitBuffer b;
	for (int i = 2; i < buffer.size; i++)
	{
		b = oz_createBitBuffer(2);
		oz_writeFull(&b.data[0], OZ_ID_CHARDATA);
		b.data[1] = buffer.data[i];
		anim.frames[i - 2] = oz_deserializeCharData(b);
		oz_destroyBitBuffer(&b);
	}
	return anim;
}

oz_BitBuffer oz_serializeTile(oz_Tile* tile, bool store_id)
{
	oz_BitBuffer buffer = oz_serializeAnimation(&tile->sprite, false);
	int size = (store_id ? 2 : 1) + buffer.size;
	oz_Bits* serialized = alloc_array(oz_Bits, size);
	int i = 0;
	if (store_id)
		oz_writeFull(&serialized[i++], OZ_ID_TILE);
	oz_Bits* tmp = &(serialized[i]);
	oz_writeBit(tmp, 0, tile->solid);
	oz_writeNBits(tmp, 1, tile->x, 7);
	oz_writeNBits(tmp, 8, tile->y, 7);
	for (int j = 0; j < buffer.size; j++)
		serialized[i + j + 1] = buffer.data[j];
	oz_destroyBitBuffer(&buffer);
	buffer.data = serialized;
	buffer.size = size;
	return buffer;
}

oz_Tile oz_deserializeTile(oz_BitBuffer buffer)
{
	oz_Tile tile;
	if (buffer.size < 3 || buffer.data[0].bits != OZ_ID_TILE)
		return tile;
	tile.solid = oz_getBit(&buffer.data[1], 0);
	tile.x = oz_readNBits(&buffer.data[1], 1, 7);
	tile.y = oz_readNBits(&buffer.data[1], 8, 7);
	oz_BitBuffer tmpb = oz_createBitBuffer(buffer.size - 1);
	tmpb.data[0].bits = OZ_ID_ANIMATION;
	for (int i = 1; i < tmpb.size; i++)
		tmpb.data[i].bits = buffer.data[i + 1].bits;
	tile.sprite = oz_deserializeAnimation(tmpb);
	oz_destroyBitBuffer(&tmpb);
	return tile;
}

oz_BitBuffer oz_serializeRoom(oz_Room* room, bool store_id)
{
	int r_size = 0;
	for (int x = 0; x < room->width; x++)
		for (int y = 0; y < room->height; y++)
			r_size += 1 + 1 + room->map[x][y].sprite.frame_count + 1;
			//1 for tile data, 1 for animation data, frame_count for every tile, 1 for evt_map
	int size = (store_id ? 2 : 1) + r_size;
	oz_Bits* serialized = alloc_array(oz_Bits, size);
	int i = 0;
	if (store_id)
		oz_writeFull(&serialized[i++], OZ_ID_ROOM);
	oz_Bits* tmp = &(serialized[i]);
	oz_writeByte(tmp, 0, room->width);
	oz_writeByte(tmp, 8, room->height);
	oz_BitBuffer buffer;
	i++;
	for (int x = 0; x < room->width; x++)
	{
		for (int y = 0; y < room->height; y++)
		{
			serialized[i++] = room->evt_map[x][y];
			buffer = oz_serializeTile(&(room->map[x][y]), false);
			for (int k = 0; k < buffer.size; k++)
				serialized[i++] = buffer.data[k];
			oz_destroyBitBuffer(&buffer);
		}
	}
	buffer.data = serialized;
	buffer.size = size;
	return buffer;
}

oz_Room oz_deserializeRoom(oz_BitBuffer buffer)
{
	oz_Room room = oz_buildRoom();
	if (buffer.size < 3 || buffer.data[0].bits != OZ_ID_ROOM)
		return room;
	room.width = oz_readByte(&buffer.data[1], 0);
	room.height = oz_readByte(&buffer.data[1], 8);
	int i = 2, ts = 0;
	oz_BitBuffer tmpb;
	for (int x = 0; x < room.width; x++)
	{
		for (int y = 0; y < room.height; y++)
		{
			room.evt_map[x][y].bits = buffer.data[i++].bits;
			ts = 2 + oz_readNBits(&buffer.data[i + 1], 0, 5);
			tmpb = oz_createBitBuffer(ts + 1);
			tmpb.data[0].bits = OZ_ID_TILE;
			for (int k = 1; k < tmpb.size; k++)
				tmpb.data[k].bits = buffer.data[i + k - 1].bits;
			room.map[x][y] = oz_deserializeTile(tmpb);
			oz_destroyBitBuffer(&tmpb);
			i += ts;
		}
	}
	return room;
}

oz_BitBuffer oz_serializeEntity(oz_Entity* e, bool store_id)
{
	oz_BitBuffer buffer = oz_serializeAnimation(&e->sprite, false);
	int size = (store_id ? 2 : 1) + buffer.size;
	oz_Bits* serialized = alloc_array(oz_Bits, size);
	int i = 0;
	if (store_id)
		oz_writeFull(&serialized[i++], OZ_ID_ENTITY);
	oz_Bits* tmp = &(serialized[i]);
	oz_writeByte(tmp, 0, e->speed);
	oz_writeNBits(tmp, 8, e->position.x, 7);
	oz_writeNBits(tmp, 15, e->position.y, 7);
	for (int j = 0; j < buffer.size; j++)
		serialized[i + j + 1] = buffer.data[j];
	oz_destroyBitBuffer(&buffer);
	buffer.data = serialized;
	buffer.size = size;
	return buffer;
}

oz_Entity oz_deserializeEntity(oz_BitBuffer buffer)
{
	oz_Entity entity;
	if (buffer.size < 3 || buffer.data[0].bits != OZ_ID_ENTITY)
		return entity;
	entity.speed = oz_readByte(&buffer.data[1], 0);
	entity.position.x = oz_readNBits(&buffer.data[1], 8, 7);
	entity.position.y = oz_readNBits(&buffer.data[1], 15, 7);
	oz_BitBuffer tmpb = oz_createBitBuffer(buffer.size - 1);
	tmpb.data[0].bits = OZ_ID_ANIMATION;
	for (int i = 1; i < tmpb.size; i++)
		tmpb.data[i].bits = buffer.data[i + 1].bits;
	entity.sprite = oz_deserializeAnimation(tmpb);
	oz_destroyBitBuffer(&tmpb);
	return entity;
}

void oz_writeBitBufferToFile(oz_BitBuffer buffer, const char* filename)
{
	FILE* file = fopen(filename, "w");
	fprintf(file, "%d ", buffer.size);
	for (int i = 0; i < buffer.size; i++)
		fprintf(file, "%d ", buffer.data[i].bits);
	fclose(file);
}

oz_BitBuffer oz_readBitBufferFromFile(const char* fname)
{
	int num = 0;
	FILE* file = fopen(fname, "r");
	fscanf(file, "%d", &num);
	oz_BitBuffer buffer = oz_createBitBuffer(num);
	int i = 0;
	fscanf(file, "%d", &num);
	while(!feof(file) && i < buffer.size)
	{
		buffer.data[i++].bits = num;
		fscanf(file, "%d", &num);
	}
	return buffer;
}

#endif
