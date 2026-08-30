/* Copyright (c) 1991 NeXT Computer, Inc.  All rights reserved.
 *
 *	File:	m68k/label_t.h
 *	Author:	Mike DeMoney, NeXT Computer, Inc.
 *
 *	This assembly code file contains "label_t" definitions
 *	for NeXT 68K-based products.
 *
 * HISTORY
 * 10-Sept-91  Mike DeMoney (mike@next.com)
 *	Created.
 */

#ifndef	_M68K_LABEL_T_H_
#define	_M68K_LABEL_T_H_

typedef struct label_t {
	int	val[13];
} label_t;

#endif	_M68K_LABEL_T_H_
