/*
 * Copyright (c) 1983, 1987 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)time.h	1.2 (Berkeley) 3/4/87
 */

/* Copyright (c) 1988,1992 NeXT, Inc. - 9/8/88 CCH */

#ifndef _ANSI_TIME_H
#define _ANSI_TIME_H

#include <standards.h>

#ifndef __STRICT_BSD__

#ifdef _NEXT_SOURCE
#import <stddef.h>
#define CLK_TCK 64
#endif /* _NEXT_SOURCE */

#if defined(_NEXT_SOURCE) || defined(__STRICT_ANSI__)
#ifndef _CLOCK_T
#define _CLOCK_T	
typedef unsigned long int clock_t;
#endif /* _CLOCK_T */
#ifndef _TIME_T
#define _TIME_T
typedef long time_t;
#endif /* _TIME_T */
#endif  /* _NEXT_SOURCE || __STRICT_ANSI__ */

#if defined(__STRICT_ANSI__)
#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long size_t;
#endif  /* _SIZE_T */
#endif  /* __STRICT_ANSI__ */

#endif /* !__STRICT_BSD__ */

#if defined(__STRICT_ANSI__)
#ifndef NULL
#define NULL ((void *)0)
#endif  /* NULL */
#endif  /* __STRICT_ANSI__ */

/*
 * Structure returned by gmtime and localtime calls (see ctime(3)).
 */

#if defined(_NEXT_SOURCE) || defined(__STRICT_ANSI__)
struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
#ifdef _NEXT_SOURCE	
    long tm_gmtoff;
    char *tm_zone;
#endif  /* _NEXT_SOURCE */
};
#endif	/* __STRICT_ANSI__ || _NEXT_SOURCE */

#ifdef __STRICT_BSD__
extern	struct tm *gmtime(), *localtime();
extern	char *asctime(), *ctime();
#elif !defined(KERNEL)
/*
 * Don't let these function declarations be visible to the
 * kernel.  The declaration of the time() function collides
 * with the definition of the time kernel variable.
 */
#ifdef __STDC__

/* ANSI C functions */
clock_t clock(void);
double difftime(time_t time1, time_t time0);
time_t mktime(struct tm *timeptr);
size_t strftime(char *s, size_t maxsize,
const char *format, const struct tm *timeptr);

/* BSD and ANSI C functions */
time_t time(time_t *timer);
char *asctime(const struct tm *timeptr);
char *ctime(const time_t *timer);
struct tm *gmtime(const time_t *timer);
struct tm *localtime(const time_t *timer);
#else

/* ANSI C functions */
clock_t clock();
double difftime();
time_t mktime();
size_t strftime();

/* BSD and ANSI C functions */
time_t time();
char *asctime();
char *ctime();
struct tm *gmtime();
struct tm *localtime();
#endif  /*__STDC__ */
#endif /* __STRICT_BSD__ */

#ifdef _POSIX_SOURCE
#ifdef __STDC__
void tzset(void);
#else
void tzset();
#endif	/* __STDC__ */

extern char *tzname[2];

#endif   /* _POSIX_SOURCE */

#endif /* _ANSI_TIME_H */
