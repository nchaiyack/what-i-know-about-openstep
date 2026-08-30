/* 	Copyright (c) 1993 NeXT Computer, Inc.  All rights reserved. 
 *
 * IODeviceDescription.h.
 *
 * HISTORY
 * 08-Jan-93    Doug Mitchell at NeXT
 *      Created. 
 */

#import <objc/Object.h>
#import <mach/port.h>
#import <driverkit/IOConfigTable.h>
#import <driverkit/driverTypes.h>

/*
 * IODeviceDescription object. This describes a
 * configured instance of a device.
 */
@interface IODeviceDescription : Object
{
@private
	port_t		_devicePort;
	id		_directDevice;
	id		_delegate;
	void		*_private;
	int		_IODeviceDescription_reserved[3];
}

- (port_t)devicePort;
- (void)setDevicePort 		: (port_t)devicePort;
- directDevice;
- (void)setDirectDevice 	: directDevice;
- (void)setConfigTable 		: (IOConfigTable *)configTable;
- (IOConfigTable *)configTable;

@end	/* IODeviceDescription */

@interface IODeviceDescription(IOInterrupt)
- (unsigned int) interrupt;
- (unsigned int *) interruptList;
- (unsigned int) numInterrupts;
- (IOReturn) setInterruptList	: (unsigned int *)list 
		    	    num : (unsigned int) numInterrupts;
@end

@interface IODeviceDescription(IOMemory)
- (IORange *) memoryRangeList;
- (unsigned int) numMemoryRanges;
- (IOReturn) setMemoryRangeList	: (IORange *)list
			    num : (unsigned int) numRanges;
@end
