#if TIMER_MODE == TIMER_MODE_INTERVAL

#include "common.h"

#include <signal.h>

double interval_timer_value;

/** Resolution of clock (clock update period). */
static const struct timeval interval_timer_resolution = {
	.tv_sec = 0,
	.tv_usec = 10 * 1e3,
};

/** A tick of interval timer, SIGALRM handler. */
static void
interval_timer_tick(int signum)
{
	(void)signum;
	interval_timer_value = clock_gettime_in_seconds(CLOCK_MONOTONIC);
}

void
time_init(void)
{
	/* Initial tick. */
	interval_timer_value = clock_gettime_in_seconds(CLOCK_MONOTONIC);

	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = interval_timer_tick;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGALRM, &sa, NULL) == -1)
		exit(-2);

	struct itimerval timer;
	timer.it_interval = interval_timer_resolution;
	timer.it_value = interval_timer_resolution;
	if (setitimer(ITIMER_REAL, &timer, NULL) == -1)
		exit(-3);
}

#else

void
time_init(void) {}

#endif

