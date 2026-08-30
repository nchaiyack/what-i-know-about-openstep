/* Copyright (c) 1991 NeXT Computer, Inc.  All rights reserved.
 *
 *	File:	architecture/hppa/cframe.h
 *	Author:	Joshua Doenias, NeXT Computer, Inc.
 *
 *	This include file defines C calling sequence defines
 *	for NeXT hppa-based products.
 *
 * HISTORY
 * 22-Sep-93  Joshua Doenias (josh@next.com)
 *	Created.
 */

#ifndef	_ARCH_HPPA_CFRAME_H_
#define	_ARCH_HPPA_CFRAME_H_

#define	C_ARGSAVE_LEN		48	// at least 48 bytes of arg save
#define	C_STACK_ALIGN		64	// stack must be 64 byte aligned

#endif	_ARCH_HPPA_CFRAME_H_
