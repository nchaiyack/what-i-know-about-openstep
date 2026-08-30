/*	Copyright (c) 1991 NeXT Computer, Inc.  All rights reserved. 
 *
 * devsw.h - Kernel-level functions to allow adding entries
 *		     to cdevsw, bdevsw, and vfssw.
 *
 * HISTORY
 * 20-Jan-93    Doug Mitchell at NeXT
 *      Created. 
 */
 
#import <sys/types.h>
#import <bsd/sys/conf.h>
#import <bsd/sys/vfs.h>
#import <objc/objc.h>		/* for BOOL */

typedef int (*IOSwitchFunc)();

/*
 * Add an entry to bdevsw. Returns the index into bdevsw at which the entry
 * was created, or -1 of no space can be found.
 */
extern int IOAddToBdevswAt(
	int major,
	IOSwitchFunc openFunc,
	IOSwitchFunc closeFunc,
	IOSwitchFunc strategyFunc,
	IOSwitchFunc dumpFunc,
	IOSwitchFunc psizeFunc,
	BOOL isTape);		// TRUE if device is a tape device
extern int IOAddToBdevsw(
	IOSwitchFunc openFunc,
	IOSwitchFunc closeFunc,
	IOSwitchFunc strategyFunc,
	IOSwitchFunc dumpFunc,
	IOSwitchFunc psizeFunc,
	BOOL isTape);		// TRUE if device is a tape device
	
/*
 * Remove an entry from bdevsw, replace it with a null entry.
 */
extern void IORemoveFromBdevsw(int bdevswNumber);

/*
 * Add an entry to cdevsw. Returns the index into cdevsw at which the entry
 * was created, or -1 of no space can be found.
 */
extern int IOAddToCdevswAt(
	int major,
	IOSwitchFunc openFunc,
	IOSwitchFunc closeFunc,
	IOSwitchFunc readFunc,
	IOSwitchFunc writeFunc,
	IOSwitchFunc ioctlFunc,
	IOSwitchFunc stopFunc,
	IOSwitchFunc resetFunc,
	IOSwitchFunc selectFunc,
	IOSwitchFunc mmapFunc,
	IOSwitchFunc getcFunc,
	IOSwitchFunc putcFunc);
extern int IOAddToCdevsw(
	IOSwitchFunc openFunc,
	IOSwitchFunc closeFunc,
	IOSwitchFunc readFunc,
	IOSwitchFunc writeFunc,
	IOSwitchFunc ioctlFunc,
	IOSwitchFunc stopFunc,
	IOSwitchFunc resetFunc,
	IOSwitchFunc selectFunc,
	IOSwitchFunc mmapFunc,
	IOSwitchFunc getcFunc,
	IOSwitchFunc putcFunc);
	
/*
 * Remove an entry from cdevsw, replace it with a null entry.
 */
extern void IORemoveFromCdevsw(int cdevswNumber);

/*
 * Add an entry to vfssw. Returns the index into vfssw at which the entry
 * was created, or -1 of no space can be found.
 */
extern int IOAddToVfsswAt(
	int index,
	const char *vfsswName,
	const struct vfsops *vfsswOps);
extern int IOAddToVfssw(
	const char *vfsswName,
	const struct vfsops *vfsswOps);
	
/*
 * Remove an entry from vfssw, replace it with a null entry.
 */
extern void IORemoveFromVfssw(int vfsswNumber);

	