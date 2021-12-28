#ifndef __GFX__C__
#define __GFX__C__

#include "data.c"
#include "utils.c"
#include "world.c"

#define oz_enableColorFilter() oz_setColorFilter(true)
#define oz_disableColorFilter() oz_setColorFilter(false)

oz_TypeWriterEffect __twe;
int __dy = 0;
int __ct = 0;

void oz_resetTypeWriterEffect(oz_TypeWriterEffect* twe)
{
	if (twe != NULL)
		*twe = oz_buildTypeWriterEffect(1);
	else
		__twe = oz_buildTypeWriterEffect(1);
}

void oz_setFilterColor(oz_Color fc)
{
	filter_color = fc;
}

void oz_setColorFilter(bool cf)
{
	color_filter = cf;
}

void oz_drawCharData(CHAR_INFO* buffer, oz_CharData c, int x, int y)
{
	int xy = _1D(x, y);
	if (color_filter)
		c.color = filter_color;
	buffer[xy].Char.AsciiChar = c.ascii;
	buffer[xy].Attributes = (!c.color.transparent_bg ? c.color.bg_color | c.color.fg_color : c.color.fg_color | oz_getWorldAt(x, y - 1).color.bg_color);
}

void oz_drawEntity(CHAR_INFO* buffer, oz_Entity* e)
{
	oz_drawCharData(buffer, oz_getAnimationFrame(&(e->sprite)), e->position.x, e->position.y);
}

void oz_drawWorld(CHAR_INFO* buffer)
{
	oz_Point p;
	for (int i = 0; i < ROOM_WIDTH * ROOM_HEIGHT; i++)
	{
		p = _2D(i);
		oz_drawCharData(buffer, oz_getAnimationFrame(&(world.rooms[current_room].map[p.x][p.y].sprite)), p.x, p.y + 1);
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

int oz_drawTokenizedString(CHAR_INFO* buffer, oz_StringTokens* st, int x, int y, int max_width)
{
	int dx = 0, dy = 0, len = 0;
	for (int i = 0; i < st->current_tok; i++)
	{
		len = st->tokens[i].length;
		if (dx + len >= max_width)
		{
			dy++;
			dx = 0;
		}
		oz_drawString(buffer, &(st->tokens[i]), x + dx, y + dy);
		oz_drawText(buffer, " ", st->tokens[0].text[0].frames[0].color, x + dx + len, y + dy);
		dx += len + 1;
	}
	return dy;
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

void oz_drawMessageBox(CHAR_INFO* buffer, oz_MessageBox* msg, int x, int y)
{
	oz_TypeWriterEffect* twe = msg->typeWriterEffect != NULL ? msg->typeWriterEffect : &__twe;
	oz_disableColorFilter();
	oz_Point p;
	for (int xy = 0; xy < msg->width * msg->height; xy++)
	{
		p = _2DL(xy, msg->width);
		oz_drawCharData(buffer, oz_getAnimationFrame(&(msg->data[xy])), x + p.x, y + p.y);
	}
	oz_String* nt = NULL;
	msg->str_tokens.current_tok = msg->str_tokens.n_tokens - 1; //FORCED SHORTCIRCUIT
	int dy = oz_drawTokenizedString(buffer, &msg->str_tokens, x + 1, y + 1, msg->width - 2);
	/*int dx = oz_curTokenTextWidth(&msg->str_tokens, __ct);
	if (__dy != dy)
	{
		oz_Logi(dx, "DX", false);
		oz_Logi(dy, "DY", false);
		oz_Logi(x, "X", false);
		oz_Logi(__dy, "_DY", true);
		__ct = msg->str_tokens.current_tok;
		dx = 0;
		__dy = dy;
	}
	oz_drawTypeWriterEffect(buffer, twe, oz_nextToken(&msg->str_tokens, false), x + dx + 1, y + dy + 1);
	if (oz_hasToknes(&msg->str_tokens) && twe->finished)
	{
		nt = oz_nextToken(&msg->str_tokens, true);
		oz_resetTypeWriterEffect(twe);
	}*/
	oz_setColorFilter(msg->col_filter);
	oz_setFilterColor(msg->filter_col);
}

void oz_drawTopBar(CHAR_INFO* buffer)
{
	oz_CharData cd;
	cd.ascii = ' ';
	cd.color.bg_color = BG_DARK_AQUA;
	cd.color.fg_color = FG_WHITE;
	cd.color.transparent_bg = false;
	for (int i = 0; i < WIDTH; i++)
		oz_drawCharData(buffer, cd, i, 0);
}

void oz_drawBottomBar(CHAR_INFO* buffer)
{
	oz_CharData cd;
	cd.ascii = ' ';
	cd.color.bg_color = BG_DARK_AQUA;
	cd.color.fg_color = FG_WHITE;
	cd.color.transparent_bg = false;
	for (int i = 0; i < WIDTH; i++)
		oz_drawCharData(buffer, cd, i, HEIGHT - 1);
}

void _print_version(CHAR_INFO* buffer)
{
	if (version == NULL)
	{
		version = malloc(sizeof(oz_String));
		*version = oz_buildString("OmniaZERO - v0.4.0a", DefaultColors.BLACK_ON_DARK_AQUA);
	}
	oz_drawString(buffer, version, WIDTH - 1 - version->length, HEIGHT - 1);
}

#endif
