#ifndef __UTILS__C__
#define __UTILS__C__

#include "data.c"
#include "anim.c"
#include "err.c"
#include "str.c"

oz_Point _2D(int i)
{
	oz_Point p;
	p.x = i % WIDTH;
	p.y = i / WIDTH;
	return p;
}

int _1D(int x, int y)
{
	return x + (WIDTH * y);
}

oz_TypeWriterEffect oz_buildTypeWriterEffect(int delay)
{
	oz_TypeWriterEffect twe;
	twe.text = NULL;
	twe.finished = false;
	twe.current_char = 0;
	twe.delay = delay;
	twe.current = 0;
	return twe;
}

bool oz_tweCanWrite(oz_TypeWriterEffect* twe, bool increment)
{
	if (increment)
		twe->current += (*delta * 10.0f);
	if (twe->current < twe->delay)
		return false;
	twe->current = 0;
	return true;
}

#endif
