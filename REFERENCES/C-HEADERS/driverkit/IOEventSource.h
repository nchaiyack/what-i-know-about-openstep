/* 	Copyright (c) 1992 NeXT Computer, Inc.  All rights reserved. 
 *
 * IOEventSource.h - Common Event Source object class.
 *
 * HISTORY
 * 22 May 1992    Mike Paquette at NeXT
 *      Created. 
 * 4  Aug 1993	  Erik Kay at NeXT
 *	API cleanup
 * 5  Aug 1993	  Erik Kay at NeXT
 *	added ivar space for future expansion
 */

#import <driverkit/IODevice.h>
#import <driverkit/eventProtocols.h>
#import <machkit/NXLock.h>

@interface IOEventSource : IODevice <IOEventSourceExported>
{
@private
	id		_owner;
	id		_desiredOwner;
	NXLock *	_ownerLock;		// NXLock; protects _owner and
						//   desiredOwner
	int		_reserved[4];		// reserved for future expansion
}

+ registerEventSource:source; // register as an event source

- init;			// Called by subclass's init to set up ownership glue
- free;
/*
 * Methods used only by subclass.
 */
- owner;
- (NXLock *)ownerLock;

@end

