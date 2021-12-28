#ifndef __DATA__C__
#define __DATA__C__

#include <stdio.h>
#include <time.h>
#include <windows.h>

#define alloc_array(type, size) malloc(sizeof(type) * size)
#define abs(i) i < 0 ? 0 : i

#define bool BOOL
#define true TRUE
#define false FALSE

#define MAX_ANIM_LEN 12
#define MAX_STR_LEN 2000
#define MAX_NUM_TOKENS 100

#define WIDTH 80
#define HEIGHT 35

typedef unsigned char oz_byte;

typedef enum {
	LEFT = 0, RIGHT, DOWN, UP, NONE
} DIRECTION;

typedef enum {
	FG_BLACK = 0,
	FG_DARK_RED = FOREGROUND_RED,
	FG_DARK_GREEN = FOREGROUND_GREEN,
	FG_DARK_BLUE = FOREGROUND_BLUE,
	FG_LIGHT_GRAY = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN,
	FG_DARK_AQUA = FOREGROUND_BLUE | FOREGROUND_GREEN,
	FG_PURPLE = FOREGROUND_RED | FOREGROUND_BLUE,
	FG_DARK_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN,

	FG_GRAY = 0 | FOREGROUND_INTENSITY,
	FG_RED = FOREGROUND_RED | FOREGROUND_INTENSITY,
	FG_GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	FG_BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	FG_WHITE = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	FG_AQUA = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	FG_PINK = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	FG_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,


	BG_BLACK = 0,
	BG_DARK_RED = BACKGROUND_RED,
	BG_DARK_GREEN = BACKGROUND_GREEN,
	BG_DARK_BLUE = BACKGROUND_BLUE,
	BG_LIGHT_GRAY = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN,
	BG_DARK_AQUA = BACKGROUND_BLUE | BACKGROUND_GREEN,
	BG_PURPLE = BACKGROUND_RED | BACKGROUND_BLUE,
	BG_DARK_YELLOW = BACKGROUND_RED | BACKGROUND_GREEN,

	BG_GRAY = 0 | BACKGROUND_INTENSITY,
	BG_RED = BACKGROUND_RED | BACKGROUND_INTENSITY,
	BG_GREEN = BACKGROUND_GREEN | BACKGROUND_INTENSITY,
	BG_BLUE = BACKGROUND_BLUE | BACKGROUND_INTENSITY,
	BG_WHITE = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY,
	BG_AQUA = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY,
	BG_PINK = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
	BG_YELLOW = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY


} COLORS;

typedef enum {
	OZ_ID_COLOR = 9,
	OZ_ID_CHARDATA,
	OZ_ID_RNDINFO,
	OZ_ID_ANIMATION,
	OZ_ID_POINTF,
	OZ_ID_POINT,
	OZ_ID_ENTITY,
	OZ_ID_TILE,
	OZ_ID_STRING,
	OZ_ID_ROOM,
	OZ_ID_WORLD,
	OZ_ID_MESSAGEBOX
} DATA_IDS;

typedef struct _bits {
	int bits;
} oz_Bits;

typedef struct _bitBuffer {
	struct _bits* data;
	int size;
} oz_BitBuffer;

typedef struct _timer {
	long start_time;
	long current_time;
	long elapsed;
	bool running;
	float delta;
} oz_Timer;

typedef struct _color {
	COLORS bg_color;
	COLORS fg_color;
	bool transparent_bg;
} oz_Color;

typedef struct _charData {
	char ascii;
	struct _color color;
} oz_CharData;

typedef struct _rndInfo {
	int min_delay;
	int max_delay;
	bool rnd_delay;
	bool rnd_frames;
} oz_RndInfo;

typedef struct _animation {
	struct _charData frames[MAX_ANIM_LEN];
	int delay;
	int current_frame;
	float _count;
	int frame_count;
	bool _static;
	struct _rndInfo random;
} oz_Animation;

typedef struct _pointF {
	float x, y;
} oz_PointF;

typedef struct _point {
	int x, y;
} oz_Point;

typedef struct _entity {
	struct _pointF position;
	struct _animation sprite;
	int speed;
} oz_Entity;

typedef struct _tile {
	struct _animation sprite;
	bool solid;
	int x;
	int y;
} oz_Tile;

typedef struct _string {
	struct _animation* text;
	int length;
} oz_String;

typedef struct _stringTokens {
	struct _string tokens[MAX_NUM_TOKENS];
	int n_tokens;
	int current_tok;
} oz_StringTokens;

typedef struct _typeWriterEffect {
	struct _string* text;
	bool finished;
	int current_char;
	int delay;
	float current;
	oz_StringTokens str_tokens;
	bool tokenized;
} oz_TypeWriterEffect;

typedef struct _room {
	struct _tile map[WIDTH][HEIGHT];
	struct _bits evt_map[WIDTH][HEIGHT];
	int width;
	int height;
} oz_Room;

typedef struct _world {
	struct _room* rooms;
} oz_World;

typedef struct _messageBox {
	int width;
	int height;
	struct _string* text;
	bool typeWriter;
	struct _typeWriterEffect* typeWriterEffect;
	struct _animation* data;
	struct _color border_color;
	struct _color bg_color;
	bool col_filter;
	struct _color filter_col;
	struct _stringTokens str_tokens;
} oz_MessageBox;

struct {
	const struct _color BLACK_ON_BLACK;
	const struct _color WHITE_ON_BLACK;
	const struct _color PURPLE_ON_GRAY;
	const struct _color DARK_GREEN_T;
	const struct _color DARK_RED_ON_DARK_AQUA;
	const struct _color DARK_GREEN_ON_BLACK;
	const struct _color PURPLE_ON_LIGHT_GRAY;
	const struct _color GREEN_ON_BLACK;
	const struct _color PINK_ON_WHITE;
	const struct _color PINK_ON_BLACK;
	const struct _color GREEN_ON_DARK_GREEN;
	const struct _color PURPLE_ON_BLACK;
	const struct _color LIGHT_GRAY_ON_GRAY;
	const struct _color BLUE_ON_DARK_AQUA;
	const struct _color BLACK_ON_AQUA;
	const struct _color DARK_BLUE_ON_DARK_AQUA;
	const struct _color BLACK_ON_DARK_RED;
	const struct _color GRAY_ON_BLUE;
	const struct _color GRAY_ON_DARK_BLUE;
	const struct _color WHITE_ON_DARK_BLUE;
	const struct _color DARK_GREEN_ON_LIGHT_GRAY;
	const struct _color DARK_GREEN_ON_GRAY;
	const struct _color LIGHT_GRAY_ON_BLACK;
	const struct _color YELLOW_ON_DARK_RED;
	const struct _color YELLOW_ON_DARK_YELLOW;
	const struct _color DARK_YELLOW_ON_YELLOW;
} DefaultColors = {
	{BG_BLACK, FG_BLACK, false},
	{BG_BLACK, FG_WHITE, false},
	{BG_GRAY, FG_PURPLE, false},
	{BG_BLACK, FG_DARK_GREEN, true},
	{BG_DARK_AQUA, FG_DARK_RED, false},
	{BG_BLACK, FG_DARK_GREEN, false},
	{BG_LIGHT_GRAY, FG_PURPLE, false},
	{BG_BLACK, FG_GREEN, false},
	{BG_WHITE, FG_PINK, false},
	{BG_BLACK, FG_PINK, false},
	{BG_DARK_GREEN, FG_GREEN, false},
	{BG_BLACK, FG_PURPLE, false},
	{BG_GRAY, FG_LIGHT_GRAY, false},
	{BG_DARK_AQUA, FG_BLUE, false},
	{BG_AQUA, FG_BLACK, false},
	{BG_DARK_AQUA, FG_DARK_BLUE, false},
	{BG_DARK_RED, FG_BLACK, false},
	{BG_BLUE, FG_GRAY, false},
	{BG_DARK_BLUE, FG_GRAY, false},
	{BG_DARK_BLUE, FG_WHITE, false},
	{BG_LIGHT_GRAY, FG_DARK_GREEN, false},
	{BG_GRAY, FG_DARK_GREEN, false},
	{BG_BLACK, FG_LIGHT_GRAY, false},
	{BG_DARK_RED, FG_YELLOW, false},
	{BG_DARK_YELLOW, FG_YELLOW, false},
	{BG_YELLOW, FG_DARK_YELLOW, false}
};

typedef enum {
	BORDER_UP_LEFT = 0,
	BORDER_UP_RIGHT,
	BORDER_DOWN_RIGHT,
	BORDER_DOWN_LEFT,
	BORDER_VERTICAL,
	BORDER_HORIZONTAL
} BORDER_PARTS;

struct _world world;
int current_room;
struct _string* version;
float* delta;
const char border_types[2][6] = {
	{201, 187, 188, 200, 186, 205},
	{218, 191, 217, 192, 179, 196}
};
bool color_filter = false;
struct _color filter_color;

#endif
