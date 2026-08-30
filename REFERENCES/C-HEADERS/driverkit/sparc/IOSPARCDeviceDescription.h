/*
 * Copyright (c) 1993 NeXT Computer, Inc.
 *
 * SPARC device description class.
 *
 * HISTORY
 * 09-06-94: Created for sparc from hppa (AR)
 *
 */
#import <driverkit/IODeviceDescription.h>
#import <driverkit/driverTypes.h>


@interface IOSPARCDeviceDescription : IODeviceDescription
{
@private
	void	*_sparc_private;
	id 		_device_info;
}

- (unsigned int) interrupt;
- (unsigned int *) interruptList;
- (unsigned int) numInterrupts;

- (unsigned int *) channelList;
- (unsigned int) numChannels;

- (IORange *) memoryRangeList;
- (unsigned int) numMemoryRanges;

- (IOReturn)setInterruptList:(unsigned int *)list 
	num:(unsigned int) numInterrupts;
- (IOReturn)setMemoryRangeList:(IORange *)list
	num:(unsigned int) numRanges;
- (unsigned int)getDeviceInfo;
- setDeviceInfo:(unsigned int)devinfo;

@end
