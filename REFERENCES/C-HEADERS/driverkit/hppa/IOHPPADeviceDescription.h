/*
 * Copyright (c) 1993 NeXT Computer, Inc.
 *
 * HPPA device description class.
 *
 */
#import <driverkit/IODeviceDescription.h>
#import <driverkit/driverTypes.h>


@interface IOHPPADeviceDescription : IODeviceDescription
{
@private
	void	*_hppa_private;
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

@end
