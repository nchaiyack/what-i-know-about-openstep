/*
 * The machine independent clock and timer definitions.
 *
 * Copyright (c) 1991 NeXT, Inc.
 *
 * HISTORY
 *
 *  6Dec91 Brian Pinkerton at NeXT
 *	Created.
 */
#import <kernserv/clock_timer.h>	/* for ns_time_t */
#import <bsd/sys/time.h>

void ns_timeout(func proc, void *arg, ns_time_t time, int pri);
void ns_abstimeout(func proc, void *arg, ns_time_t deadline, int pri);
boolean_t ns_untimeout(func proc, void *arg);
void ns_sleep(ns_time_t delay);

ns_time_t timeval_to_ns_time(struct timeval *tv);
void ns_time_to_timeval(ns_time_t nano_time, struct timeval *tvp);

