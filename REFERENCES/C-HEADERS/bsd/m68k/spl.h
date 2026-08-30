/*
 *	File:	spl.h
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Define inline macros for spl routines.
 *	
 * HISTORY
 * 21-May-91  Gregg Kellogg (gk) at NeXT
 *	Moved public portion to exported directory.
 *
 * 14-May-90  Gregg Kellogg (gk) at NeXT
 *	Changed SPLCLOCK from 6 to 3, as much scheduling code expects
 *	splclock() == splsched().  Added splusclock().
 *
 * 19-Jun-89  Mike DeMoney (mike) at NeXT
 *	Modified to allow spl assertions in spl_measured.h
 */

#ifndef	_BSD_M88K_SPL_
#define	_BSD_M88K_SPL_

#ifdef	KERNEL_BUILD
#import <iplmeas.h>
#else	KERNEL_BUILD
#import <mach/features.h>
#endif	KERNEL_BUILD

#import <bsd/m68k/psl.h>

#if	NIPLMEAS && !defined(NO_IPLMEAS)
#import <machdep/m68k/spl_measured.h>
#endif	NIPLMEAS && !defined(NO_IPLMEAS)

#import <kernserv/m68k/spl.h>

#endif	_BSD_M88K_SPL_
