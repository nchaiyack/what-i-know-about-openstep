/* 	Copyright (c) 1991 NeXT Computer, Inc.  All rights reserved. 
 *
 * align.h - alignment macros.
 *
 * HISTORY
 * 25-Apr-91    Doug Mitchell at NeXT
 *      Created. 
 */

#define	IOAlign(type, addr, bufferSize)		\
	((type)(((unsigned)(addr)+(bufferSize)-1) &~((bufferSize)-1)))

#define	IOIsAligned(addr, bufferSize)		\
	(((unsigned)(addr)&((bufferSize)-1))==0)
