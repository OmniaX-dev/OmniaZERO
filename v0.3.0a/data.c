#ifndef __DATA__C__
#define __DATA__C__

#include <stdio.h>
#include <time.h>
#include <windows.h>

#define alloc_array(type, size) malloc(sizeof(type) * size)

#define bool BOOL
#define true TRUE
#define false FALSE

#define MAX_LOG_STREAMS 3
#define MAX_ANIM_LEN 12
#define MAX_STR_LEN 2000

#define WIDTH 80
#define HEIGHT 35

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
	FG_DARK_YELLOW = FOREGROUND_BLUE | FOREGROUND_GREEN,

	FG_GRAY = 0 | FOREGROUND_INTENSITY,
	FG_RED = FOREGROUND_RED | FOREGROUND_INTENSITY,
	FG_GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	FG_BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	FG_WHITE = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	FG_AQUA = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	FG_PINK = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	FG_YELLOW = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,


	BG_BLACK = 0,
	BG_DARK_RED = BACKGROUND_RED,
	BG_DARK_GREEN = BACKGROUND_GREEN,
	BG_DARK_BLUE = BACKGROUND_BLUE,
	BG_LIGHT_GRAY = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN,
	BG_DARK_AQUA = BACKGROUND_BLUE | BACKGROUND_GREEN,
	BG_PURPLE = BACKGROUND_RED | BACKGROUND_BLUE,
	BG_DARK_YELLOW = BACKGROUND_BLUE | BACKGROUND_GREEN,

	BG_GRAY = 0 | BACKGROUND_INTENSITY,
	BG_RED = BACKGROUND_RED | BACKGROUND_INTENSITY,
	BG_GREEN = BACKGROUND_GREEN | BACKGROUND_INTENSITY,
	BG_BLUE = BACKGROUND_BLUE | BACKGROUND_INTENSITY,
	BG_WHITE = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY,
	BG_AQUA = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY,
	BG_PINK = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
	BG_YELLOW = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY


} COLORS;

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
	float speed;
} oz_Entity;

typedef struct _tile {
	struct _animation sprite;
	bool solid;
} oz_Tile;

typedef struct _string {
	struct _animation* text;
	int length;
} oz_String;

typedef struct _typeWriterEffect {
	struct _string* text;
	bool finished;
	int current_char;
	int delay;
	float current;
} oz_TypeWriterEffect;

typedef struct _room {
	struct _tile map[WIDTH][HEIGHT];
	int width;
	int height;
} oz_Room;

typedef struct _world {
	struct _room* rooms;
} oz_World;

typedef struct _messageBox {
	int width;
	int height;
	struct _string text;
	bool typeWriter;
	struct _typeWriterEffect* typeWriterEffect;
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
	{BG_BLACK, FG_PURPLE, false}
};

struct _world world;
int current_room;
struct _string* version;
float* delta;


#endif
