/* 	Copyright (c) 1992 NeXT Computer, Inc.  All rights reserved. 
 *
 * BasicConsole.c - VGA based console definitions.
 *
 *
 * HISTORY
 * 15 Sep 92	Joe Pasqua
 *      Created. 
 */

#if defined(KERNEL_PRIVATE) || defined(DRIVER_PRIVATE)

// Notes:
// * This module is the interface to a console implementation that writes
//   to a [CEV]GA in character mode. See ConsoleSupport.h for details.
// * The km driver should be the only client of this interface. It will
//   allocate a VGAConsole object initially using this mechanism. It will
//   get console objects for the rest of the displays using a method
//   in the display's class.

#import	<mach/boolean.h>
#import	"ConsoleSupport.h"

extern IOConsoleInfo *BasicAllocateConsole();

#endif	/* KERNEL_PRIVATE || DRIVER_PRIVATE */
