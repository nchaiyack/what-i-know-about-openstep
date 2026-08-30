/*
 * Copyright (c) 1994 NeXT Computer, Inc.
 *
 * PCI device description class.
 *
 * HISTORY
 *
 * 19 Aug 1994 Dean Reece at NeXT
 *	Complete re-write.
 *
 * 19 Jul 1994 Curtis Galloway at NeXT
 *	Created.
 *
 */
#import <driverkit/i386/IOEISADeviceDescription.h>
#import <driverkit/driverTypes.h>


@interface IOPCIDeviceDescription : IOEISADeviceDescription
{
    void	*_pci_private;
}

/*
 * getPCIdevice is the whole purpose for this object.  This method allows
 * callers to get the PCI config address of the PCI device associated
 * with this device description.  If all goes well, the three params are
 * filled in and IO_R_SUCCESS is returned.  There are a variety of reasons
 * that the address couldn't be known, in which case an appropriate code is
 * returned and the parameters are left untouched.  It is acceptable for any
 * of the parameter pointers to be NULL.
 */
- (IOReturn) getPCIdevice: (unsigned char *) devNum
		 function: (unsigned char *) funNum
		      bus: (unsigned char *) busNum;

@end
