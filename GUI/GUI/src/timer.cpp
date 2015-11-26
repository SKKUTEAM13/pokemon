#include "timer.h"

timer timer::TimerInit(void)
{
	timer Timer;
	memset(&Timer, 0, sizeof(Timer));

	if (!QueryPerformanceFrequency((LARGE_INTEGER *)&Timer.frequency))
	{
		Timer.performance_timer = false;
		Timer.mm_timer_start = timeGetTime();
		Timer.resolution = 1.0f / 1000.0f;
		Timer.frequency = 1000;
		Timer.mm_timer_elapsed = Timer.mm_timer_start;
	}
	else
	{
		QueryPerformanceCounter((LARGE_INTEGER *)&Timer.performance_timer_start);
		Timer.performance_timer = true;
		Timer.resolution = (float)(((double)1.0f) / ((double)Timer.frequency));
		Timer.performance_timer_elapsed = Timer.performance_timer_start;
	}
	return Timer;
}

float timer::TimerGetTime() {
	__int64 time;

	if (performance_timer)                        // Are We Using The Performance Timer?
	{
		QueryPerformanceCounter((LARGE_INTEGER *)&time);       // Grab The Current Performance Time
															   // Return The Current Time Minus The Start Time Multiplied By The Resolution And 1000 (To Get MS)
		return ((float)(time - performance_timer_start) * resolution)*1000.0f;
	}
	else
	{
		// Return The Current Time Minus The Start Time Multiplied By The Resolution And 1000 (To Get MS)
		return((float)(timeGetTime() - mm_timer_start) * resolution)*1000.0f;
	}
}