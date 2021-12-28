#ifndef __DATA__C__
#define __DATA__C__

#include "color.c"

#define MAX_ANIM_LEN 12
#define MAX_STR_LEN 2000
#define MAX_NUM_TOKENS 100

#define WIDTH 80
#define HEIGHT 35

typedef enum {
	LEFT = 0, RIGHT, DOWN, UP, NONE
} DIRECTION;

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
