#ifndef __STR__C__
#define __STR__C__

#include "data.c"
#include "clean.c"
#include "log.c"
#include "utils.c"

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

void oz_setStringColor(oz_String* str, oz_Color col)
{
	for (int i = 0; i < str->length; i++)
		str->text[i].frames[0].color = col;
}

//All frame information is lost, only the first frame of each character is saved
char* _string_to_c_str(oz_String* str, oz_CharData** cd)
{
	char* _str = alloc_array(char, str->length + 1);
	if (cd != NULL)
		*cd = realloc(*cd, sizeof(oz_CharData) * str->length);
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

oz_StringTokens oz_tokenizeString(oz_String* str, char separator)
{
	oz_StringTokens st;
	st.n_tokens = 0;
	st.current_tok = 0;
	int tl = 0;
	int tok_len[MAX_NUM_TOKENS];
	int cur_t = 0;
	for (int i = 0; i < str->length; i++)
	{
		if (str->text[i].frames[0].ascii != separator)
			tl++;
		else if (i < str->length - 1)
		{
			st.n_tokens++;
			tok_len[cur_t++] = tl;
			tl = 0;
		}
	}
	st.n_tokens++;
	tok_len[cur_t++] = tl;
	cur_t = 0;
	tl = 0;
	for (int i = 0; i < st.n_tokens; i++)
	{
		st.tokens[cur_t].text = alloc_array(oz_Animation, tok_len[i]);
		st.tokens[cur_t].length = tok_len[i];
		for (int j = 0; j < tok_len[i]; j++)
			st.tokens[cur_t].text[j] = str->text[tl++];
		cur_t++;
		tl++;
	}
	return st;
}

oz_String* oz_nextToken(oz_StringTokens* st, bool increment)
{
	if (st->current_tok < st->n_tokens)
		return &st->tokens[increment ? st->current_tok++ : st->current_tok];
	return &st->tokens[st->n_tokens - 1];
}

oz_String* oz_prevToken(oz_StringTokens* st)
{
	if (st->current_tok > 0)
		return &st->tokens[st->current_tok - 1];
	return &st->tokens[0];
}

int oz_curTokenTextWidth(oz_StringTokens* st, int start)
{
	int w = 0;
	for (int i = start; i < st->current_tok; i++)
		w += st->tokens[i].length + 1;
	return w;
}

void oz_resetStringTokens(oz_StringTokens* st)
{
	st->current_tok = 0;
}

bool oz_hasToknes(oz_StringTokens* st)
{
	return st->current_tok < st->n_tokens;
}

#endif
