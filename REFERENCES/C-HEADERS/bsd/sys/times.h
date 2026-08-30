/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	times.h,v $
 *  7-Jan-93  Mac Gillon (mgillon) at NeXT
 *	Integrated POSIX support
 *
 * Revision 2.3  89/03/09  22:08:46  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  17:57:12  gm0w
 * 	Changes for cleanup.
 * 
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)times.h	7.1 (Berkeley) 6/4/86
 */

#ifndef	_SYS_TIMES_H_
#define _SYS_TIMES_H_

#if !defined(KERNEL)
	#include <standards.h>
#endif

#if defined(_POSIX_SOURCE)
	#ifndef _CLOCK_T
		#define _CLOCK_T
		typedef unsigned long int clock_t;
	#endif /* _CLOCK_T */
#else
	#import <sys/types.h>	/* for time_t */
#endif	/* _POSIX_SOURCE */

/*
 * Structure returned by times()
 */
struct tms {
#if defined(_POSIX_SOURCE) && !defined(KERNEL)
	clock_t	tms_utime;		/* user time */
	clock_t	tms_stime;		/* system time */
	clock_t	tms_cutime;		/* user time, children */
	clock_t	tms_cstime;		/* system time, children */
#else
	time_t	tms_utime;		/* user time */
	time_t	tms_stime;		/* system time */
	time_t	tms_cutime;		/* user time, children */
	time_t	tms_cstime;		/* system time, children */	
#endif /* _POSIX_SOURCE */
};

#if defined(_POSIX_SOURCE) && !defined(KERNEL)
	#ifdef __STDC__
		extern clock_t	times(struct tms *buffer);
	#else
		extern clock_t	times();
	#endif /* __STDC__ */
#endif /* _POSIX_SOURCE */
#endif	_SYS_TIMES_H_
