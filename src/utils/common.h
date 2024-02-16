#pragma once

#include <time.h>
#include <stdlib.h>

static inline double
clock_gettime_in_seconds(int mode)
{
	struct timespec ts;
	int rc = clock_gettime(mode, &ts);
	if (rc != 0)
		exit(-1);
	return (double) ts.tv_sec + ts.tv_nsec / 1e9;
}

/**
 * Macro TIMER_MODE must be defined.
 * It specifies type of used timer:
 * 0 - clock_gettime (syscall)
 * 1 - clock_gettime (vDSO)
 * 2 - clock_gettime (COARSE - low resolution timer)
 * 3 - interval timer
 */

#define TIMER_MODE_SYSCALL 0
#define TIMER_MODE_VDSO 1
#define TIMER_MODE_COARSE 2
#define TIMER_MODE_INTERVAL 3
#define TIMER_MODE_NOOP 4

#ifndef TIMER_MODE
	#error "TIMER_MODE must be set"
#endif


#if TIMER_MODE == TIMER_MODE_INTERVAL

extern double interval_timer_value;

#endif

static inline double
get_time(void)
{

#if TIMER_MODE == TIMER_MODE_SYSCALL

	return time(NULL);

#elif TIMER_MODE == TIMER_MODE_VDSO

	return clock_gettime_in_seconds(CLOCK_MONOTONIC);

#elif TIMER_MODE == TIMER_MODE_COARSE

	return clock_gettime_in_seconds(CLOCK_MONOTONIC_COARSE);

#elif TIMER_MODE == TIMER_MODE_INTERVAL

	return interval_timer_value;

#elif TIMER_MODE == TIMER_MODE_NOOP
	return 0.0;
#else
	#error "Invalid TIMER_MODE value"
#endif

}

void
time_init(void) {}
