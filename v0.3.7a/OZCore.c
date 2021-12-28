#ifndef __OZ_CORE__C__
#define __OZ_CORE__C__

#include <signal.h>
#include "entity.c"
#include "gfx.c"
#include "world.c"
#include "timer.c"
#include "log.c"
#include "msgbox.c"
#include "serial.c"

typedef void (*_evt_callback)(int);
typedef CHAR_INFO oz_GfxBuffer;

struct {
	void (*_close_evt_callback)();
	void (*_on_frame_callback)(float, oz_GfxBuffer*);

	HANDLE whnd;
	HANDLE rhnd;

	SMALL_RECT windowSize;
	COORD buffSize;

	COORD charBuffSize;
	COORD charBuffPos;
	SMALL_RECT wArea;

	CHAR_INFO buffer[WIDTH * HEIGHT];
	BOOL key_down;
	int last_key;

	INPUT_RECORD *eventBuffer;
	DWORD numEventsRead;

	_evt_callback okp_ptr;
	_evt_callback okr_ptr;

	oz_Timer timer;
} _oz_cd;



void SigBreak_Handler(int n_signal)
{
	oz_clearLogFile();
	oz_closeLogFile(false);
	if (_oz_cd._close_evt_callback != NULL)
		(*(_oz_cd._close_evt_callback))();
    exit(2);
}

DWORD getInput(INPUT_RECORD **eventBuffer)
{
	  DWORD numEvents = 0;
	  DWORD numEventsRead = 0;
	  GetNumberOfConsoleInputEvents(_oz_cd.rhnd, &numEvents);

	  if (numEvents)
	  {
		  *eventBuffer = malloc(sizeof(INPUT_RECORD) * numEvents);
		  ReadConsoleInput(_oz_cd.rhnd, *eventBuffer, numEvents, &numEventsRead);
	  }

	  return numEventsRead;
}

void keyPressed(INPUT_RECORD* evt, int key)
{
	if (!evt->Event.KeyEvent.bKeyDown && _oz_cd.last_key == key)
	{
		_oz_cd.key_down = false;
		if (_oz_cd.okr_ptr != NULL)
			(*(_oz_cd.okr_ptr))(key);
		return;
	}
	else if (!evt->Event.KeyEvent.bKeyDown)
	{
		return;
	}
	_oz_cd.key_down = true;
	_oz_cd.last_key = key;
	if (_oz_cd.okp_ptr != NULL)
		(*(_oz_cd.okp_ptr))(key);
}

void oz_setKeyPressed(_evt_callback ptr)
{
	_oz_cd.okp_ptr = ptr;
}

void oz_setKeyReleased(_evt_callback ptr)
{
	_oz_cd.okr_ptr = ptr;
}

void oz_setCloseCallback(void (*ptr)())
{
	_oz_cd._close_evt_callback = ptr;
}

void oz_setFrameCallback(void (*ptr)(float, oz_GfxBuffer*))
{
	_oz_cd._on_frame_callback = ptr;
}

void oz_Init(void)
{
	srand(time(NULL));

	_oz_cd.whnd = GetStdHandle(STD_OUTPUT_HANDLE);
	_oz_cd.rhnd = GetStdHandle(STD_INPUT_HANDLE);

	_oz_cd._close_evt_callback = NULL;
	_oz_cd._on_frame_callback = NULL;
	_oz_cd.windowSize = (struct _SMALL_RECT){0, 0, WIDTH - 1, HEIGHT - 1};
	_oz_cd.buffSize = (struct _COORD){WIDTH, HEIGHT};
	_oz_cd.charBuffPos = (struct _COORD){0, 0};
	_oz_cd.charBuffSize =(struct _COORD) {WIDTH, HEIGHT};
	_oz_cd.wArea = (struct _SMALL_RECT){0, 0, WIDTH - 1, HEIGHT - 1};
	_oz_cd.key_down =  false;
	_oz_cd.last_key = -10;
	_oz_cd.okp_ptr = NULL;
	_oz_cd.okr_ptr = NULL;

	SetConsoleWindowInfo(_oz_cd.whnd, TRUE, &(_oz_cd.windowSize));
	SetConsoleScreenBufferSize(_oz_cd.whnd, _oz_cd.buffSize);

	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = false;
	cci.dwSize = 1;
	SetConsoleCursorInfo(_oz_cd.whnd, &cci);

	signal(SIGBREAK, &SigBreak_Handler);

	delta = &(_oz_cd.timer.delta);
	filter_color = DefaultColors.LIGHT_GRAY_ON_GRAY;

	oz_resetTypeWriterEffect(NULL);
	oz_openLogFile("console.log");
	oz_setLogRealTimeUpdate(false);

	oz_startTime(&(_oz_cd.timer));
}

void oz_setWindowTitle(const char* title)
{
	SetConsoleTitle(title);
}

void oz_updateEvents(void)
{
	_oz_cd.numEventsRead = getInput(&(_oz_cd.eventBuffer));
	if (_oz_cd.numEventsRead)
	{
		 for (int i = 0; i < _oz_cd.numEventsRead; i++)
		 {
			 switch (_oz_cd.eventBuffer[i].EventType)
			 {
				case KEY_EVENT:
					keyPressed(&(_oz_cd.eventBuffer[i]), _oz_cd.eventBuffer[i].Event.KeyEvent.wVirtualKeyCode);
				break;
			}
		}
	}
	free(_oz_cd.eventBuffer);
}

void oz_startGameLoop(void)
{
	while(1)
	{
		oz_updateEvents();
		oz_drawWorld(_oz_cd.buffer);
		if (_oz_cd._on_frame_callback != NULL)
			(*(_oz_cd._on_frame_callback))(*delta, _oz_cd.buffer);
		_print_version(_oz_cd.buffer);
		WriteConsoleOutputA(_oz_cd.whnd, _oz_cd.buffer, _oz_cd.charBuffSize, _oz_cd.charBuffPos, &(_oz_cd.wArea));
		oz_nextTime(&(_oz_cd.timer));
	}
}

#endif
