/*
 * Copyright (c) 1994 NeXT Computer, Inc.
 *
 * PCI direct device interface.
 *
 * HISTORY
 *
 * 19 Aug 1994  Dean Reece at NeXT
 *	Added class methods.
 *
 * 13 May 1994	Dean Reece at NeXT
 *	Created.
 */

#import <driverkit/IODirectDevice.h>
#import <driverkit/i386/PCI.h>		/* IOPCIConfigSpace defined */

@interface IODirectDevice (IOPCIDirectDevice)

/*
 * Returns YES if PCI Bus support is enabled.  Returns NO otherwise.
 */
+ (BOOL)isPCIPresent;
- (BOOL)isPCIPresent;

/*
 * Reads the device's entire configuration space.  Returns IO_R_SUCCESS if
 * successful.  If this method fails, the driver should make no assumptions
 * about the state of the data returned in the IOPCIConfigSpace struct.
 */
+ (IOReturn)getPCIConfigSpace: (IOPCIConfigSpace *) configSpace
	withDeviceDescription: descr;

- (IOReturn)getPCIConfigSpace: (IOPCIConfigSpace *) configSpace;

/*
 * Writes the device's entire configuration space.  Returns IO_R_SUCCESS if
 * successful.  If this method fails, the driver should make no assumptions
 * about the state of the device's configuration space.
 */
+ (IOReturn)setPCIConfigSpace: (IOPCIConfigSpace *) configSpace
	withDeviceDescription: descr;

- (IOReturn)setPCIConfigSpace: (IOPCIConfigSpace *) configSpace;

/*
 * Reads from the device's configuration space.  All access are 32 bits wide
 * and the address must be aligned as such.
 */
+ (IOReturn)getPCIConfigData: (unsigned long *) data
		  atRegister: (unsigned char) address
       withDeviceDescription: descr;

- (IOReturn)getPCIConfigData: (unsigned long *) data
		  atRegister: (unsigned char) address;

/*
 * Writes to the device's configuration space.  All access are 32 bits wide
 * and the address must be aligned as such.
 */
+ (IOReturn)setPCIConfigData: (unsigned long) data
		  atRegister: (unsigned char) address
       withDeviceDescription: descr;

- (IOReturn)setPCIConfigData: (unsigned long) data
		  atRegister: (unsigned char) address;
@end
