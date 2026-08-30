/*
 * Copyright (c) 1993 NeXT Computer, Inc.
 *
 * sparc-specific driverkit types.
 *
 */

// Got this interupt handler prototype from busconf.c (aspitab()).
// It seems bogus (no args). Maybe we'll find a better one.
typedef void 		(*IOSPARCInterruptHandler)();
