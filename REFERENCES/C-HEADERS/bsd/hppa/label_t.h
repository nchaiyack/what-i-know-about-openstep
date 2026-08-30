/*
 * Copyright (c) 1993 NeXT Computer, Inc.
 *
 * HPPA Family:	For setjmp/longjmp (kernel version).
 *
 * HISTORY
 *
 * 9 August 1993 Frank Rowand at NeXT
 *	Created.
 */
 
#ifndef _BSD_HPPA_LABEL_T_H_
#define _BSD_HPPA_LABEL_T_H_

typedef struct label_t {
	int	val[48];
} label_t;

#endif	_BSD_HPPA_LABEL_T_H_
