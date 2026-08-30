/*
 * Copyright (c) 1994 NeXT Computer, Inc.
 *
 * PCMCIA device description class.
 *
 * HISTORY
 *
 * 12 Aug 1994 Curtis Galloway at NeXT
 *	Created.
 *
 */
#import <driverkit/i386/IOEISADeviceDescription.h>
#import <driverkit/driverTypes.h>

@interface IOPCMCIADeviceDescription : IOEISADeviceDescription
{
    void	*_pcmcia_private;
}

- (unsigned) numTuples;
- (id *) tupleList;

@end
