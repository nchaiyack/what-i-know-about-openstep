/*
 *  Copyright (c) 1994 by NeXT Computer, Inc.
 */

#ifndef	_MACH_SPARC_THREAD_STATUS_H_
#define	_MACH_SPARC_THREAD_STATUS_H_

#include <architecture/sparc/reg.h>

/*
 *	sparc_thread_state_regs
 *		This is the structure that is exported
 *      to user threads for use in set/get status
 *      calls.  This structure should never change.
 *		The "local" and "in" registers of the corresponding 
 *		register window	are saved in the stack frame pointed
 *		to by sp -> %o6.
 *
 *	sparc_thread_state_fpu
 *		This is the structure that is exported
 *      to user threads for use in set/get FPU register 
 *		status calls.
 */

#define	SPARC_THREAD_STATE_REGS	1

struct sparc_thread_state_regs {
	struct regs regs;
};

#define	SPARC_THREAD_STATE_REGS_COUNT \
			(sizeof(struct sparc_thread_state_regs) / sizeof(int))

/*
 *	Floating point unit registers
 */

#define SPARC_THREAD_STATE_FPU	2


struct sparc_thread_state_fpu {
	struct fpu fpu;	/* floating point registers/status */
};

#define	SPARC_THREAD_STATE_FPU_COUNT \
			(sizeof(struct sparc_thread_state_fpu) / sizeof(int))

#define	SPARC_THREAD_STATE_FLAVOR_COUNT  2

#define SPARC_THREAD_STATE_FLAVOR_LIST_COUNT         \
	( SPARC_THREAD_STATE_FLAVOR_COUNT *              \
		(sizeof (struct thread_state_flavor) / sizeof(int)))

#endif	_MACH_SPARC_THREAD_STATUS_H_
