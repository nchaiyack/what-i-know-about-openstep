/*
 * Copyright (c) 1993 NeXT Computer, Inc.
 *
 * SPARC direct device interface.
 *
 * HISTORY
 *  09-06-94: Created for Sparc from hppa (AR)
 */
#import <driverkit/IODevice.h>
#import <driverkit/IODirectDevice.h>
#import <driverkit/IODeviceDescription.h>
#import <driverkit/sparc/IOSPARCDeviceDescription.h>
#import <driverkit/sparc/driverTypes.h>


void IOSendInterrupt(void *identity, void *state, unsigned int msgId);

@interface IODirectDevice(IOSPARCDirectDevice)

@end
