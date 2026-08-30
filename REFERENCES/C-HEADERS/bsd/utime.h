/* Copyright 1993 NeXT Computer, Inc - WMG */

#ifndef _UTIME_
#define _UTIME_

#include <standards.h>

#ifdef _POSIX_SOURCE
	#ifndef _TIME_T
		#define _TIME_T
		typedef long time_t;
	#endif

	struct utimbuf {
		time_t	actime;		/* Access time */
		time_t	modtime;	/* Modification time */
	};

	#ifdef __STDC__
		extern int utime(const char *path,
			const struct utimbuf *times);
	#else
		extern int utime();
	#endif /* __STDC__ */
#endif /*_POSIX_SOURCE */
#endif /* _UTIME_ */
