/* 
 * Mach Operating System
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 **********************************************************************
 * HISTORY
 * 25-Apr-88  Karl Hauth (hauth) at Carnegie-Mellon University
 *	Created.
 *
 *
 **********************************************************************
 */ 

#ifndef	_MACH_EXCEPTION_
#define	_MACH_EXCEPTION_	1

#import <mach/kern_return.h>

char		*mach_exception_string(
/*
 *	Returns a string appropriate to the error argument given
 */
	int	exception
				);


void		mach_exception(
/*
 *	Prints an appropriate message on the standard error stream
 */
	const char	*str,
	int		exception
				);


char		*mach_NeXT_exception_string(
/*
 *	Returns a string appropriate to the error argument given
 */
	int	exception,
	int	code,
	int	subcode
				);


void		mach_NeXT_exception(
/*
 *	Prints an appropriate message on the standard error stream
 */
	const char	*str,
	int	exception,
	int		code,
	int			subcode
				);

#endif	_MACH_EXCEPTION_
