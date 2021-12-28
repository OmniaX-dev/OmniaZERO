#ifndef __CLEAN__C__
#define __CLEAN__C__

#include "data.c"

void oz_destroyString(oz_String* str)
{
	free(str->text);
}

#endif
