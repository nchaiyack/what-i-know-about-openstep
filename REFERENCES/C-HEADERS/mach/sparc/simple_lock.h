/* Copyright (c) 1994 NeXT Computer, Inc.  All rights reserved.
 * 
 *	File:	mach/sparc/simple_lock.h
 *
 *	This file contains machine dependent code for exclusion
 *	lock handling on SPARC-based products.
 *
 * HISTORY
 * 21-Apr-1994  Mac Gillon at NeXT
 *	Created.
 */

#import <mach/boolean.h>

#ifndef	_MACH_SPARC_SIMPLE_LOCK_
#define _MACH_SPARC_SIMPLE_LOCK_

#define _MACHINE_SIMPLE_LOCK_DATA_

struct slock {
    volatile boolean_t	locked;
};

typedef struct slock	simple_lock_data_t;
typedef struct slock	*simple_lock_t;

extern simple_lock_t	simple_lock_alloc(void);
extern void		simple_lock_free(simple_lock_t);
extern boolean_t	simple_lock_try();

#if	!defined(DEFINE_SIMPLE_LOCK_PRIMS)
static __inline__
#endif
void
simple_lock_init(
    simple_lock_t	slock
)
{
    slock->locked = FALSE;
}

#if	!defined(DEFINE_SIMPLE_LOCK_PRIMS)
static __inline__
#endif
void
simple_lock(
    simple_lock_t	slock
)
{    
    do
    	{
	    while (slock->locked)
		continue;
	}
    while (!simple_lock_try(slock));
}

#if	!defined(DEFINE_SIMPLE_LOCK_PRIMS)
static __inline__
#endif
void
simple_unlock(
    simple_lock_t	slock
)
{
    slock->locked = FALSE;
}

#endif	_MACH_SPARC_SIMPLE_LOCK_
