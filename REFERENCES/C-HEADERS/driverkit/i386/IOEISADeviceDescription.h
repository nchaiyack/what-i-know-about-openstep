/*
 * Copyright (c) 1993 NeXT Computer, Inc.
 *
 * ISA/EISA device description class.
 *
 * HISTORY
 *
 * 18Jan93 Brian Pinkerton at NeXT
 *	Created.
 *
 */
#import <driverkit/IODeviceDescription.h>
#import <driverkit/driverTypes.h>


@interface IOEISADeviceDescription : IODeviceDescription
{
@private
    void	*_eisa_private;
}

- (unsigned int) channel;

- (unsigned int *) channelList;
- (unsigned int) numChannels;
- (IORange *) portRangeList;
- (unsigned int) numPortRanges;

- (IOReturn) setChannelList    : (unsigned int *)list 
			   num : (unsigned int) numChannels;

- (IOReturn) setPortRangeList  : (IORange *)list 
			   num : (unsigned int) numRanges;

- (IOReturn) getEISASlotNumber : (unsigned int *) slotNum;
- (IOReturn) getEISASlotID     : (unsigned long *) slotID;

@end
