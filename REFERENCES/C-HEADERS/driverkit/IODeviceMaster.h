/* 	Copyright (c) 1993 NeXT Computer, Inc.  All rights reserved. 
 *
 * IODeviceMaster class description.
 *
 * HISTORY
 * 08-Jan-93    Doug Mitchell at NeXT
 *      Created. 
 */

#ifndef	KERNEL

#import <objc/Object.h>
#import <driverkit/driverTypes.h>
#import <mach/port.h>

/*
 * IODeviceMaster class. Used in user space only, to do Get/Set parameter
 * type operations. 
 *
 * General return values for all methods in this class which return an 
 * IOReturn:
 *
 * IO_R_NO_DEVICE - IOObjectNumber out of range of known device objects.
 * IO_R_OFFLINE   - invalid IOObjectNumber, but not out of range. There
 *		    can be 'holes' in the IOObjectNumber space; IO_R_OFFLINE
 *		    indicates an IOObjectNumber assicated with such a 
 *		    non-existent device object.
 *
 * All other return codes are device-specific.
 */

@interface IODeviceMaster : Object
{
@private
	port_t	_deviceMasterPort;
	int	_IODeviceMaster_reserved[4];
}

/*
 * Obtain an instance of IODeviceMaster.
 */
+ new;

/*
 * Free an instance of IODeviceMaster.
 */
- free;

/*
 * Get device type and device name for specified IOObjectNumber.
 */
- (IOReturn)lookUpByObjectNumber	: (IOObjectNumber)objectNumber
			     deviceKind : (IOString *)deviceKind
			     deviceName : (IOString *)deviceName;
				   

/*
 * Get IOObjectNumber and device type for specified deviceName.
 */
- (IOReturn)lookUpByDeviceName		: (IOString)deviceName
			   objectNumber : (IOObjectNumber *)objectNumber
			     deviceKind : (IOString *)deviceKind;
			     
/*
 * Get/set parameter methods used at user level to communicate with
 * kernel-level drivers.
 */
- (IOReturn)getIntValues		: (unsigned *)parameterArray
			   forParameter : (IOParameterName)parameterName
			   objectNumber : (IOObjectNumber)objectNumber
			          count : (unsigned *)count;	// in/out

- (IOReturn)getCharValues		: (unsigned char *)parameterArray
			   forParameter : (IOParameterName)parameterName
			   objectNumber : (IOObjectNumber)objectNumber
			          count : (unsigned *)count;	// in/out
	
- (IOReturn)setIntValues		: (unsigned *)parameterArray
			   forParameter : (IOParameterName)parameterName
			   objectNumber : (IOObjectNumber)objectNumber
			          count : (unsigned)count;

- (IOReturn)setCharValues		: (unsigned char *)parameterArray
			   forParameter : (IOParameterName)parameterName
			   objectNumber : (IOObjectNumber)objectNumber
			          count : (unsigned)count;

@end	/* IODeviceMaster */

#endif	KERNEL

