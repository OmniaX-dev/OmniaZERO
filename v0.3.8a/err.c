#ifndef __ERR__C__
#define __ERR__C__

#define is_error(errcode) errcode != ERR_NO_ERRORS

typedef enum {
	ERR_NO_ERRORS = 0,

	ERR_SPLIT_STR_FAILED = 10,
	ERR_LOG_FILE_IS_NULL,
	ERR_LOG_FILE_NOT_INITIALIZED
} _ERR_CODES;


#endif
