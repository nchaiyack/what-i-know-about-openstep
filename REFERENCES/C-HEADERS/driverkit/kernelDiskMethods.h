/* 	Copyright (c) 1991 NeXT Computer, Inc.  All rights reserved. 
 *
 * kernelDiskMethods.h - Kernel devsw glue for IODisk class.
 *
 * HISTORY
 * 02-May-91    Doug Mitchell at NeXT
 *      Created. 
 */

#import <driverkit/return.h>
#import <driverkit/IODisk.h>
#import <kernserv/prototypes.h>
#import <bsd/sys/disktab.h>

#define	IO_DISK_UNIT(dev)	(minor(dev) >> 3)
#define	IO_DISK_PART(dev)	(minor(dev) & 0x7)	

@interface IODisk(kernelDiskMethods)

/*
 * Async I/O complete function. The void * argument is actually 
 * a struct buf *, but the rest of the code in IODisk (or its subclasses)
 * doesn't need to know that.
 */
- (void)completeTransfer		: (void *)iobuf 
			     withStatus : (IOReturn)status
			   actualLength : (unsigned)actualLength;

/*
 * Get/set IODevAndIdInfo pointer.
 */
- (IODevAndIdInfo *)devAndIdInfo;
- (void)setDevAndIdInfo			: (IODevAndIdInfo *)devAndIdInfo;

/*
 * Obtain dev_t associated with this instance.
 */
- (dev_t)blockDev;
- (dev_t)rawDev;

@end

