#ifndef __CLEAN__C__
#define __CLEAN__C__

#include "data.c"

void oz_destroyString(oz_String* str)
{
	free(str->text);
	str->text = NULL;
}

void oz_destroyMessageBox(oz_MessageBox* msg)
{
	free(msg->data);
	oz_destroyString(&msg->text);
	msg->data = NULL;
}

void oz_destroyBitBuffer(oz_BitBuffer* buffer)
{
	free(buffer->data);
	buffer->data = NULL;
	buffer->size = 0;
}

#endif
