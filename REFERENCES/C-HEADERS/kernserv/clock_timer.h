/*
 * The machine independent clock and timer definitions.
 *
 * Copyright (c) 1989 NeXT, Inc.
 *
 * HISTORY
 *
 *  6Dec91 Brian Pinkerton at NeXT
 *	Created.
 */
#import <mach/mach_types.h>
#import	<mach/boolean.h>
#import <bsd/sys/time.h>
#import <bsd/sys/callout.h>

typedef	unsigned long long	ns_time_t;	/* nanoseconds! */

typedef struct chrono_attributes {
	ns_time_t	max_value;	/* max value of clock or timer */
	ns_time_t	resolution;	/* actual hardware accuracy */
} *chrono_attributes_t;

typedef enum {
	Calendar,	/* assumed battery back-up */
	System,		/* assumed "highest resolution available" */
} clock_types_t;


/*
 *  Clock functions.  These can be called from any ipl.
 */
ns_time_t clock_value(clock_types_t which_clock);
void set_clock(clock_types_t which_clock, ns_time_t ns);
const struct chrono_attributes *clock_attributes(clock_types_t which_clock);

