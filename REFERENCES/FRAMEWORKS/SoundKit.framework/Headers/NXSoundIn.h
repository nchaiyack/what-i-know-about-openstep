/*
 * NXSoundIn.h
 *
 * Copyright (c) 1992, NeXT Computer, Inc.  All rights reserved. 
 */

#import "NXSoundDevice.h"

@interface NXSoundIn:NXSoundDevice
{
    int _reserved1;
}

// Obsolete.
+ (port_t)lookUpDevicePortOnHost:(NSString *)hostName;

@end
