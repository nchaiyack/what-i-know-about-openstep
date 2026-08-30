/* 
 * Copyright (c) 1992 NeXT, Inc.  All rights reserved.
 *
 * c_utils.h -- Helpful C macros
 */

#define	ROUND_UP(addr, align)	\
	( ( (unsigned)(addr) + (align) - 1) & ~((align) - 1) )

#define	TRUNC_DOWN(addr, align)	\
	( (unsigned)(addr) & ~((align) - 1) )

/*
 * FIXME: For some reason the compiler miscalculates the alignment of
 * struct uthread as 0, so this forces all structs to have an alignof of
 * 16.
 */
#define	COMPILER_BUG	1

#ifdef	COMPILER_BUG
#define	ROUND_PTR(type, addr)	\
	(type *)( ( (unsigned)(addr) + 16 - 1) \
		  & ~(16 - 1) )

#define	TRUNC_PTR(type, addr)	\
	(type *)( (unsigned)(addr) & ~(16 - 1) )
#else	COMPILER_BUG
#define	ROUND_PTR(type, addr)	\
	(type *)( ( (unsigned)(addr) + __alignof__(type) - 1) \
		  & ~(__alignof__(type) - 1) )

#define	TRUNC_PTR(type, addr)	\
	(type *)( (unsigned)(addr) & ~(__alignof__(type) - 1) )
#endif	COMPILER_BUG

#define	ARRAY_ELEM(x)		(sizeof(x)/sizeof(x[0]))
