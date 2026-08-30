/*
 * Copyright (c) 1994 NeXT Computer, Inc.
 *
 * PCMCIA direct device interface.
 *
 * HISTORY
 *
 * 17 May 1994 Curtis Galloway at NeXT
 *	Created.
 *
 */

#import <driverkit/IODirectDevice.h>

@interface IODirectDevice(IOPCMCIADirectDevice)

- (IOReturn) mapAttributeMemoryTo:(vm_address_t *) destAddr
			findSpace:(BOOL) findSpace;

- (void) unmapAttributeMemory;

@end
