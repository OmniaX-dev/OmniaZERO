#include <stdio.h>
#include <time.h>
#include <windows.h>

#define alloc_array(type, size) malloc(sizeof(type) * size)
#define abs(i) i < 0 ? 0 : i

#define bool BOOL
#define true TRUE
#define false FALSE

typedef unsigned char oz_byte;
