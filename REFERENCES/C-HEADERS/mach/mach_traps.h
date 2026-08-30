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
 * $Log:	mach_traps.h,v $
 * 23-Apr-90  Morris Meyer (mmeyer) at NeXT
 *	Converted all macros to conform to the ANSI standard.
 *	Cannot have nested ifdef's inside of defined macros in ANSI C.
 *
 * Revision 2.6  89/10/11  14:38:46  dlb
 * 	Add host traps.
 * 	[89/01/25            dlb]
 * 
 * Revision 2.5  89/03/09  20:20:46  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  18:37:15  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  89/02/19  12:57:44  rpd
 * 	Moved from kern/ to mach/.
 * 
 * Revision 2.2  89/01/15  16:24:46  rpd
 * 	Updated includes for the new mach/ directory.
 * 	[89/01/15  15:03:03  rpd]
 * 
 * 18-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	Add thread_reply.  Leave in task_data as an alternate name -
 *	they are functionally indistinguishable.
 *
 * 15-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Include ../kern/mach_types.h instead of <kern/mach_types.h> when
 *	building for the kernel.
 *
 *  1-Sep-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Created, mostly to help build the lint library.
 *	Should eventually include this in "syscall_sw.c".
 *
 */
/*
 *	Definitions of general Mach system traps.
 *
 *	IPC traps are defined in <mach/message.h>.
 *	Kernel RPC functions are defined in <mach/mach_interface.h>.
 */

#ifndef	_MACH_MACH_TRAPS_H_
#define _MACH_MACH_TRAPS_H_

#import <mach/mach_types.h>

mach_port_t	mach_reply_port();
mach_port_t	mach_thread_self();
mach_port_t	mach_task_self();
mach_port_t	mach_host_self();
port_t		(task_self)();
port_t		task_notify();
port_t		thread_self();
port_t		thread_reply();
host_t		host_self();
boolean_t	swtch();
boolean_t	swtch_pri();
kern_return_t	thread_switch();
kern_return_t	map_fd();


#endif	_MACH_MACH_TRAPS_H_
