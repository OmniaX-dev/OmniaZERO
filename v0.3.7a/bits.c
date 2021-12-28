#ifndef __BITS__C__
#define __BITS__C__

#include "data.c"

#define oz_setBit(bits, bit) oz_writeBit(bits, bit, true)
#define oz_clrBit(bits, bit) oz_writeBit(bits, bit, false)
#define oz_readByte(bits, pos) oz_readNBits(bits, pos, 8)
#define oz_writeByte(bits, pos, b) oz_writeNBits(bits, pos, b, 8)
#define oz_read2Bits(bits, pos) oz_readNBits(bits, pos, 2)
#define oz_write2Bits(bits, pos, b) oz_writeNBits(bits, pos, b, 2)
#define oz_read4Bits(bits, pos) oz_readNBits(bits, pos, 4)
#define oz_write4Bits(bits, pos, b) oz_writeNBits(bits, pos, b, 4)
#define oz_readFull(bits) oz_readNBits(bits, 0, 32)
#define oz_writeFull(bits, b) oz_writeNBits(bits, 0, b, 32)

bool oz_getBit(oz_Bits* bits, int bit)
{
	return (bits->bits & (1 << bit)) != 0;
}

void oz_writeBit(oz_Bits* bits, int bit, bool value)
{
	if (value)
		bits->bits |= 1 << bit;
	else
		bits->bits &= ~(1 << bit);
}

void oz_tglBit(oz_Bits* bits, int bit)
{
	bits->bits ^= 1 << bit;
}

oz_Bits oz_buildBits(void)
{
	oz_Bits bits;
	bits.bits = 0;
	return bits;
}

void oz_writeNBits(oz_Bits* bits, int pos, int data, int n_bits)
{
	for (int i = 0; i < n_bits; i++)
		oz_writeBit(bits, pos + i, data & (1 << i));
}

int oz_readNBits(oz_Bits* bits, int pos, int n_bits)
{
	int data = 0;
	int j = 0;
	for (int i = pos; i < pos + n_bits; i++, j++)
	{
		if (oz_getBit(bits, i))
			data |= (1 << j);
	}
	return data;
}

oz_BitBuffer oz_createBitBuffer(int size)
{
	if (size < 1)
		size = 10;
	oz_BitBuffer buffer;
	buffer.size = size;
	buffer.data = alloc_array(oz_Bits, size);
	for (int i = 0; i < size; i++)
		buffer.data[i] = oz_buildBits();
	return buffer;
}

#endif
