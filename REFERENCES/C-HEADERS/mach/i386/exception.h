/*
 * Copyright (c) 1992 NeXT Computer, Inc.
 *
 * Intel386 Family:	Machine dependent exception codes.
 *
 * HISTORY
 *
 * 13 April 1992 David E. Bohman at NeXT
 *	Created.
 */
 
/*
 * EXC_BAD_ACCESS
 */
#define EXC_I386_PAGE_FAULT		14

/*
 * EXC_BAD_INSTRUCTION
 */
#define EXC_I386_INVALID_OPCODE		6
#define EXC_I386_SEGMENT_NOTPRESENT	11
#define EXC_I386_STACK_EXCEPTION	12
#define EXC_I386_GENERAL_PROTECTION	13

/*
 * EXC_ARITHMETIC
 */
#define EXC_I386_ZERO_DIVIDE		0
#define EXC_I386_EXTENSION_FAULT	16

/*
 * EXC_EMULATION
 */
#define EXC_I386_NOEXTENSION		7

/*
 * EXC_SOFTWARE
 */
#define EXC_I386_OVERFLOW		4
#define EXC_I386_BOUNDS_CHECK		5
#define EXC_I386_ALIGNMENT_CHECK	17

/*
 * EXC_BREAKPOINT
 */
#define EXC_I386_DEBUG			1
#define EXC_I386_BREAKPOINT		3
