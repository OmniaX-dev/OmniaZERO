#ifndef __TIMER__C__
#define __TIMER__C__

#include <time.h>
#include "data.c"

#define _time_diff(t1, t2) (((double)t2 - t1) / CLOCKS_PER_SEC * 1000)

long oz_startTime(oz_Timer* timer)
{
	long t = (long)clock();
	if (timer != NULL)
	{
		timer->start_time = timer->current_time = t;
		timer->elapsed = 0;
		timer->running = true;
		timer->delta = 0.0f;
	}
	return (long)t;
}

long oz_getTimeElapsed(oz_Timer* timer)
{
	long t = (long)clock();
	if (timer != NULL && timer->running)
	{
		timer->current_time = t;
		timer->elapsed = _time_diff(timer->start_time, t);
		timer->delta = (float)(timer->elapsed) / 1000.0f;
		return timer->elapsed;
	}
	else if (timer != NULL)
	{
		return timer->elapsed;
	}
	return t;
}

long oz_nextTime(oz_Timer* timer)
{
	long t = (long)clock();
	if (timer != NULL)
	{
		timer->start_time = timer->current_time;
		return oz_getTimeElapsed(timer);
	}
	return (long)t;
}

long oz_stopTime(oz_Timer* timer)
{
	long t = (long)clock();
	if (timer != NULL && timer->running)
	{
		t = oz_getTimeElapsed(timer);
		timer->running = false;
	}
	return t;
}

#endif
