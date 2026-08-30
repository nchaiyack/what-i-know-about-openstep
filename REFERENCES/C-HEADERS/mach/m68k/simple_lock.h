/* Copyright (c) 1991 NeXT Computer, Inc.  All rights reserved.
 * 
 *	File:	mach/m68k/simple_lock.h
 *
 *	This file contains machine dependent code for exclusion
 *	lock handling on NeXT 68K-based products.
 *
 * HISTORY
 * 20-May-91  Mike DeMoney (mike@next.com)
 *	Created.
 */
 
#import <mach/boolean.h>

#ifndef	_MACH_M68K_SIMPLE_LOCK_
#define _MACH_M68K_SIMPLE_LOCK_

#define	_MACHINE_SIMPLE_LOCK_DATA_

struct slock {
	int		lock_data;	/* in general 1 bit is sufficient */
};

typedef struct slock	simple_lock_data_t;
typedef struct slock	*simple_lock_t;

extern void		(simple_lock_init)();
extern void		(simple_lock)();
extern void		(simple_unlock)();
extern boolean_t	(simple_lock_try)();

#endif	_MACH_M68K_SIMPLE_LOCK_
