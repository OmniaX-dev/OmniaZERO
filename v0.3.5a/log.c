#ifndef __LOG__C__
#define __LOG__C__

#include <stdio.h>

FILE* __log_file = NULL;
bool __log_rt_update = false;
const char* __log_file_path = NULL;
bool _text_shown = false;

void oz_setLogRealTimeUpdate(bool lrtu)
{
	__log_rt_update = lrtu;
}

bool oz_openLogFile(const char* filename)
{
	__log_file = fopen(filename, "a+");
	__log_file_path = filename;
	return __log_file != NULL;
}

void oz_closeLogFile(bool print_separator)
{
	if (print_separator && _text_shown)
		fprintf(__log_file, "\n--------------------------------------\n\n\n\n");
	fclose(__log_file);
	__log_file = NULL;
}

int oz_clearLogFile(void)
{
	if (__log_file_path == NULL)
		return ERR_LOG_FILE_NOT_INITIALIZED;
	if (__log_file != NULL)
		oz_closeLogFile(false);
	__log_file = fopen(__log_file_path, "w");
	_text_shown = true;
	return ERR_NO_ERRORS;
}

int oz_Log(const char* str, const char* varname, bool nl)
{
	if (__log_file == NULL)
		return ERR_LOG_FILE_IS_NULL;
	if (varname != NULL)
		fprintf(__log_file, "|-%s: %s-|", varname, str);
	else
		fprintf(__log_file, "%s", str);
	if (nl)
		fprintf(__log_file, "\n");
	if (__log_rt_update)
	{
		oz_closeLogFile(false);
		oz_openLogFile(__log_file_path);
	}
	_text_shown = true;
	return ERR_NO_ERRORS;
}

int oz_Logstr(oz_String* str, const char* varname, bool nl)
{
	if (__log_file == NULL)
		return ERR_LOG_FILE_IS_NULL;
	if (varname != NULL)
		fprintf(__log_file, "|-%s: ", varname);
	for (int i = 0; i < str->length; i++)
		fprintf(__log_file, "%c", str->text[i].frames[0].ascii);
	if (varname != NULL)
		fprintf(__log_file, "-|");
	if (nl)
		fprintf(__log_file, "\n");
	if (__log_rt_update)
	{
		oz_closeLogFile(false);
		oz_openLogFile(__log_file_path);
	}
	_text_shown = true;
	return ERR_NO_ERRORS;
}

int oz_Logi(int n, const char* varname, bool nl)
{
	if (__log_file == NULL)
		return ERR_LOG_FILE_IS_NULL;
	if (varname != NULL)
		fprintf(__log_file, "|-%s: %d-|", varname, n);
	else
		fprintf(__log_file, "%d", n);
	if (nl)
		fprintf(__log_file, "\n");
	if (__log_rt_update)
	{
		oz_closeLogFile(false);
		oz_openLogFile(__log_file_path);
	}
	_text_shown = true;
	return ERR_NO_ERRORS;
}

int oz_Logf(float n, const char* varname, bool nl)
{
	if (__log_file == NULL)
		return ERR_LOG_FILE_IS_NULL;
	if (varname != NULL)
		fprintf(__log_file, "|-%s: %f-|", varname, n);
	else
		fprintf(__log_file, "%f", n);
	if (nl)
		fprintf(__log_file, "\n");
	if (__log_rt_update)
	{
		oz_closeLogFile(false);
		oz_openLogFile(__log_file_path);
	}
	_text_shown = true;
	return ERR_NO_ERRORS;
}

int oz_Logb(bool b, const char* varname, bool nl)
{
	if (__log_file == NULL)
		return ERR_LOG_FILE_IS_NULL;
	if (varname != NULL)
		fprintf(__log_file, "|-%s: %s-|", varname, (b ? "true" : "false"));
	else
		fprintf(__log_file, "%s", (b ? "true" : "false"));
	if (nl)
		fprintf(__log_file, "\n");
	if (__log_rt_update)
	{
		oz_closeLogFile(false);
		oz_openLogFile(__log_file_path);
	}
	_text_shown = true;
	return ERR_NO_ERRORS;
}

#endif
