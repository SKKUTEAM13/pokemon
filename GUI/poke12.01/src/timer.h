#pragma once

#include <windows.h>		// Header File For Windows

class timer {
public:
	timer TimerInit(void);
	float TimerGetTime();
	void  SleepTime(int steps, int MicroSecond);
private:
	__int64		  frequency;					// Timer Frequency
	float		  resolution;					// Timer Resolution
	unsigned long mm_timer_start;				// Multimedia Timer Start Value
	unsigned long mm_timer_elapsed;				// Multimedia Timer Elapsed Time
	bool		  performance_timer;			// Using Ther performance Timer?
	__int64		  performance_timer_start;		// Performance Timer Start Value
	__int64		  performance_timer_elapsed;	// performance Timer Elapsed Time
};