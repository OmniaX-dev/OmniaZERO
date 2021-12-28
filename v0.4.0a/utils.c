#ifndef __UTILS__C__
#define __UTILS__C__

#include "data.c"
#include "anim.c"
#include "err.c"
#include "str.c"

oz_Point _2DL(int i, int width)
{
	oz_Point p;
	p.x = i % width;
	p.y = i / width;
	return p;
}

oz_Point _2D(int i)
{
	return _2DL(i, WIDTH);
}

int _1DL(int x, int y, int width)
{
	return x + (width * y);
}

int _1D(int x, int y)
{
	return _1DL(x, y, WIDTH);
}

oz_TypeWriterEffect oz_buildTypeWriterEffect(int delay)
{
	oz_TypeWriterEffect twe;
	twe.text = NULL;
	twe.finished = false;
	twe.current_char = 0;
	twe.delay = delay;
	twe.current = 0;

	twe.str_tokens.n_tokens = 0;
	twe.str_tokens.current_tok = 0;
	twe.tokenized = false;

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
