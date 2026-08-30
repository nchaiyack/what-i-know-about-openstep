/*
 * Copyright (c) 1992 NeXT Computer, Inc.
 *
 * i386-specific driverkit types.
 *
 * HISTORY
 *
 * 29 September 1992 David E. Bohman at NeXT
 *	Created.
 */

typedef unsigned short 	IOEISAPortAddress;
typedef void 		*IOEISADMABuffer;
typedef void 		(*IOEISAInterruptHandler)(void *identity, 
				void *state, 
				unsigned int arg);
