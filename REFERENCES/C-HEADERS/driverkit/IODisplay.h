/* 	Copyright (c) 1992 NeXT Computer, Inc.  All rights reserved. 
 *
 * IODisplay.h - Abstract superclass for all IODisplay objects.
 *
 *
 * HISTORY
 * 01 Sep 92	Joe Pasqua
 *      Created. 
 * 24 Jun 93	Derek B Clegg
 *	Moved to driverkit; minor cleanup.
 * 4  Aug 1993	  Erik Kay at NeXT
 *	minor API cleanup
 */

#ifndef __IODISPLAY_H__
#define __IODISPLAY_H__

#import <driverkit/IODevice.h>
#import <driverkit/IODirectDevice.h>
#import	<driverkit/displayDefs.h>
#import	<driverkit/eventProtocols.h>

@interface IODisplay: IODirectDevice <IOScreenEvents>
{
@private
    IODisplayInfo _display;	/* Parameters describing the display. */
    int _token;			/* Token. */

    /* Reserved for future expansion. */
    unsigned int _IODisplay_reserved[18];
}

// Returns a pointer to an IODisplayInfo describing the display.
- (IODisplayInfo *)displayInfo;

// Handles NeXT-internal parameters specific to IODisplays; forwards
// the handling of all other parameters to `super'.
- (IOReturn)getIntValues		: (unsigned *)parameterArray
			   forParameter : (IOParameterName)parameterName
			          count : (unsigned *)count;

// Returns the registration token for this display.
- (int)token;

// Sets the registration token for this display.
- (void)setToken:(int)token;

// `IOScreenEvents' protocol methods reimplemented by this class.
- (port_t)devicePort;

@end

#endif	/* __IODISPLAY_H__ */
