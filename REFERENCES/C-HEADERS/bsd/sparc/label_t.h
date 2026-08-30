/*
 * Copyright (c) 1994 NeXT Computer, Inc.
 *
 * SPARC Family:	For setjmp/longjmp (kernel version).
 *
 * HISTORY
 *
 * 21-Apr-1994 Mac Gillon at NeXT
 *	Created.
 */
 
#ifndef _BSD_SPARC_LABEL_T_H_
#define _BSD_SPARC_LABEL_T_H_

typedef struct label_t {
	int	val[2];
} label_t;

#define	l_pc	val[0]
#define	l_sp	val[1]

#endif	_BSD_SPARC_LABEL_T_H_
