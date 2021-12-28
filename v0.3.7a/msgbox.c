#ifndef __MSGBOX__C__
#define __MSGBOX__C__

#include "data.c"
#include "utils.c"

void oz_fillMessageBoxData(oz_MessageBox* msg)
{
	int xy = 0;
	oz_CharData cd;

	cd.ascii = ' ';
	cd.color = msg->bg_color;
	for (int xy = 0; xy < msg->height * msg->width; xy++)
		msg->data[xy] = oz_buildStaticAnimation(cd);
	cd.color = msg->border_color;
	cd.ascii = border_types[0][BORDER_HORIZONTAL];
	for (int x = 0; x < msg->width; x++)
	{
		xy = _1DL(x, 0, msg->width);
		msg->data[xy] = oz_buildStaticAnimation(cd);
		xy = _1DL(x, msg->height - 1, msg->width);
		msg->data[xy] = oz_buildStaticAnimation(cd);
	}
	cd.ascii = border_types[0][BORDER_VERTICAL];
	for (int y = 0; y < msg->height; y++)
	{
		xy = _1DL(0, y, msg->width);
		msg->data[xy] = oz_buildStaticAnimation(cd);
		xy = _1DL(msg->width - 1, y, msg->width);
		msg->data[xy] = oz_buildStaticAnimation(cd);
	}
	cd.ascii = border_types[0][BORDER_UP_LEFT];
	msg->data[_1DL(0, 0, msg->width)] = oz_buildStaticAnimation(cd);
	cd.ascii = border_types[0][BORDER_UP_RIGHT];
	msg->data[_1DL(msg->width - 1, 0, msg->width)] = oz_buildStaticAnimation(cd);
	cd.ascii = border_types[0][BORDER_DOWN_RIGHT];
	msg->data[_1DL(msg->width - 1, msg->height - 1, msg->width)] = oz_buildStaticAnimation(cd);
	cd.ascii = border_types[0][BORDER_DOWN_LEFT];
	msg->data[_1DL(0, msg->height - 1, msg->width)] = oz_buildStaticAnimation(cd);
}

oz_MessageBox oz_buildMessageBox(int width, int height)
{
	oz_MessageBox msg;
	msg.width = width;
	msg.height = height;
	msg.text = NULL;
	msg.typeWriter = true;
	msg.typeWriterEffect = NULL;
	msg.data = alloc_array(oz_Animation, width * height);
	msg.border_color = DefaultColors.DARK_BLUE_ON_DARK_AQUA;
	msg.bg_color = DefaultColors.YELLOW_ON_DARK_RED;
	msg.filter_col = DefaultColors.LIGHT_GRAY_ON_GRAY;
	msg.col_filter = true;
	oz_fillMessageBoxData(&msg);
	return msg;
}

void oz_setMessageBoxText(oz_MessageBox* msg, oz_String* text)
{
	msg->text = malloc(sizeof(*text));
	*(msg->text) = *text;
	oz_setStringColor(msg->text, msg->bg_color);
	msg->str_tokens = oz_tokenizeString(msg->text, ' ');
}

void oz_setMessageBoxTWE(oz_MessageBox* msg, oz_TypeWriterEffect* twe)
{
	msg->typeWriterEffect = twe;
}

#endif
