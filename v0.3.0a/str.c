#ifndef __STR__C__
#define __STR__C__

#include "data.c"
#include "clean.c"

oz_String oz_buildString(const char* str, oz_Color color)
{
	oz_String _str;
	_str.length = strlen(str);
	_str.text = alloc_array(oz_Animation, _str.length);
	oz_CharData c;
	c.color = color;
	for (int i = 0; i < _str.length; i++)
	{
		c.ascii = str[i];
		_str.text[i] = oz_buildStaticAnimation(c);
	}
	return _str;
}

//All frame information is lost, only the first frame of each character is saved
char* _string_to_c_str(oz_String* str, oz_CharData** cd)
{
	char* _str = alloc_array(char, str->length + 1);
	if (cd != NULL)
		*cd = (oz_CharData*)(realloc(*cd, sizeof(oz_CharData) * str->length));
	for (int i = 0; i < str->length; i++)
	{
		_str[i] = str->text[i].frames[0].ascii;
		if (cd != NULL)
			*cd[i] = str->text[i].frames[0];
	}
	_str[str->length] = '\0';
	return _str;
}

int oz_splitString(oz_String* str, int split_point, oz_String* half1, oz_String* half2)
{
	if (split_point < 0 || split_point > str->length - 2)
		return ERR_SPLIT_STR_FAILED;
	int len1 = split_point + 1;
	int len2 = str->length - split_point - 1;
	if (half1 != NULL)
	{
		oz_Animation* h1 = alloc_array(oz_Animation, len1);
		memcpy(h1, str->text, len1 * sizeof(oz_Animation));
		half1->length = len1;
		half1->text = h1;
	}
	if (half2 != NULL)
	{
		oz_Animation* h2 = alloc_array(oz_Animation, len2);
		memcpy(h2, str->text + len1, len2 * sizeof(oz_Animation));
		half2->length = len2;
		half2->text = h2;
	}
	return ERR_NO_ERRORS;
}

#endif
