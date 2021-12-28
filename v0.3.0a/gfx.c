#ifndef __GFX__C__
#define __GFX__C__

#include "data.c"
#include "utils.c"

oz_TypeWriterEffect __twe;

void oz_drawCharData(CHAR_INFO* buffer, oz_CharData c, int x, int y)
{
	int xy = _1D(x, y);
	buffer[xy].Char.AsciiChar = c.ascii;
	buffer[xy].Attributes = (!c.color.transparent_bg ? c.color.bg_color | c.color.fg_color : c.color.fg_color | oz_getAnimationFrame(&(world.rooms[current_room].map[x][y].sprite)).color.bg_color);
}

void oz_drawEntity(CHAR_INFO* buffer, oz_Entity* e)
{
	oz_drawCharData(buffer, oz_getAnimationFrame(&(e->sprite)), e->position.x, e->position.y);
}

void oz_drawWorld(CHAR_INFO* buffer)
{
	oz_Point p;
	for (int i = 0; i < WIDTH * HEIGHT; i++)
	{
		p = _2D(i);
		oz_drawCharData(buffer, oz_getAnimationFrame(&(world.rooms[current_room].map[p.x][p.y].sprite)), p.x, p.y);
	}
}

void oz_drawString(CHAR_INFO* buffer, oz_String* str, int x, int y)
{
	oz_Point p;
	int xy = _1D(x, y);
	for (int i = 0; i < str->length; i++)
	{
		p = _2D(xy + i);
		oz_drawCharData(buffer, oz_getAnimationFrame(&(str->text[i])), p.x, p.y);
	}
}

void oz_drawText(CHAR_INFO* buffer, const char* str, oz_Color color, int x, int y)
{
	oz_String _str = oz_buildString(str, color);
	oz_drawString(buffer, &_str, x, y);
	oz_destroyString(&_str);
}

void oz_drawTypeWriterEffect(CHAR_INFO* buffer, oz_TypeWriterEffect* twe, oz_String* str, int x, int y)
{
	oz_TypeWriterEffect* _twe = &__twe;
	if (twe != NULL)
		_twe = twe;
	if (_twe->finished)
	{
		oz_drawString(buffer, str, x, y);
		return;
	}
	if (_twe->text == NULL)
		_twe->text = str;
	oz_String str1;
	int err = oz_splitString(str, _twe->current_char, &str1, NULL);
	if (err == ERR_SPLIT_STR_FAILED)
	{
		_twe->finished = true;
		oz_drawString(buffer, str, x, y);
		return;
	}
	if (oz_tweCanWrite(_twe, true))
		_twe->current_char++;
	oz_drawString(buffer, &str1, x, y);
}

void oz_resetTypeWriterEffect(oz_TypeWriterEffect* twe)
{
	if (twe != NULL)
		*twe = oz_buildTypeWriterEffect(1);
	else
		__twe = oz_buildTypeWriterEffect(1);
}

void _print_version(CHAR_INFO* buffer)
{
	if (version == NULL)
	{
		version = malloc(sizeof(oz_String));
		*version = oz_buildString("OmniaZERO - v0.3.0a", DefaultColors.GREEN_ON_BLACK);
	}
	oz_CharData* cd = NULL;
	for (int i = 0; i < version->length; i++)
	{
		cd = &(version->text[i].frames[0]);
		if (i > 4 && i < 9)
			cd->color = DefaultColors.PINK_ON_BLACK;
		else if (i == 10)
			cd->color.fg_color = FG_BLUE;
		else if (i == 12)
			cd->color.fg_color = FG_RED;
		else if (i > 10)
			cd->color.fg_color = FG_AQUA;
	}
	oz_drawString(buffer, version, 2, HEIGHT - 1);
}

#endif
