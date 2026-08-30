/* Copyright (c) 1993 NeXT Computer, Inc.  All rights reserved.
 * 
 *	File:	mach/hppa/simple_lock.h
 *
 *	This file contains machine dependent code for exclusion
 *	lock handling on HPPA-based products.
 *
 * HISTORY
 * 2-July-1993  Mac Gillon at NeXT
 *	Created.
 */

#import <mach/hppa/boolean.h>

#ifndef	_MACH_HPPA_SIMPLE_LOCK_
#define _MACH_HPPA_SIMPLE_LOCK_

#define	_MACHINE_SIMPLE_LOCK_DATA_

struct slock{
	volatile unsigned int lock_data[4];/* in general 1 bit is sufficient */
};

typedef struct slock	simple_lock_data_t;
typedef struct slock	*simple_lock_t;

#if	!defined(DEFINE_SIMPLE_LOCK_PRIMS)
static __inline__
#endif
void
simple_lock_init(
    simple_lock_t	slock
)
{
    *((volatile int *)(((int)(slock) + 0x0c) & ~0x0f))  = 1;
}

#if	!defined(DEFINE_SIMPLE_LOCK_PRIMS)
static __inline__
#endif
void
simple_unlock(
    simple_lock_t	slock
)
{
    *((volatile int *)(((int)(slock) + 0x0c) & ~0x0f))  = 1;
}

#if	!defined(DEFINE_SIMPLE_LOCK_PRIMS)
static __inline__
#endif
boolean_t
simple_lock_try(
    simple_lock_t	slock
)
{
    boolean_t		result;
	volatile int   *lock_word;
    
	lock_word = (volatile int *)(((int)(slock) + 0x0c) & ~0x0f);
	
    asm volatile (
    	"ldcws 0(%1),%0"
	    : "=r" (result): "r" (lock_word));
	
    return (result);
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
	    while (*((volatile int *)(((int)(slock) + 0x0c) & ~0x0f))  == 0)
		continue;
	}
    while (!simple_lock_try(slock));
}

#endif	_MACH_HPPA_SIMPLE_LOCK_
