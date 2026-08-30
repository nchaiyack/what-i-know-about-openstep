/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * 11-Jul-91  Gregg Kellogg (gk) at NeXT
 *	Initial version.
 */
/*
 *	File:	kernserv/lock.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Exported locking primitives definitions
 *
 */


#ifndef	_KERN_LOCK_H_
#define _KERN_LOCK_H_

#import <mach/boolean.h>

/*
 *	A simple spin lock.
 */

#import	<mach/machine/simple_lock.h>

typedef void	*lock_t;

/* Sleep locks must work even if no multiprocessing */

extern lock_t		lock_alloc();
extern void		lock_free();
extern void		lock_init();
extern void		lock_sleepable();
extern void		lock_write();
extern void		lock_read();
extern void		lock_done();
extern boolean_t	lock_read_to_write();
extern void		lock_write_to_read();
extern boolean_t	lock_try_write();
extern boolean_t	lock_try_read();
extern boolean_t	lock_try_read_to_write();

#define lock_read_done(l)	lock_done(l)
#define lock_write_done(l)	lock_done(l)

extern void		lock_set_recursive();
extern void		lock_clear_recursive();

#endif	_KERN_LOCK_H_

