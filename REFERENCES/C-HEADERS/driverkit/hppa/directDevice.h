/*
 * Copyright (c) 1993 NeXT Computer, Inc.
 *
 * HPPA direct device interface.
 *
 * HISTORY
 *
 */
#import <driverkit/IODevice.h>
#import <driverkit/IODirectDevice.h>
#import <driverkit/IODeviceDescription.h>
#import <driverkit/hppa/IOHPPADeviceDescription.h>
#import <driverkit/hppa/driverTypes.h>


void IOSendInterrupt(void *identity, void *state, unsigned int msgId);

@interface IODirectDevice(IOHPPADirectDevice)

@end
