/*
** IOAddressRanger - Input validation for a range of addresses.
**
** Copyright 1992 by NeXT Computer, Inc.  All Rights Reserved.
*/

#import <appkit/appkit.h>
#import "IODeviceInspector.h"

@interface Object (IORangerDelegate)
- rangeDidChange:sender;
@end

@interface IOAddressRanger:Object
{
@private
    id	rangeText;
    id	delegate;
    id  statusButton;	/* On for conflict */
    id  sizeText;	/* Shows size of range */
    
    unsigned long  lowAddr, highAddr;
    unsigned long  rangeLength, rangeStart;
    int	   	   conflictState;
    BOOL	   continuous;
}

- setAddressLimits:(unsigned long)low :(unsigned long)high;

- setRangeLength:(unsigned long)rlen;
- (unsigned long) rangeLength;

- setStartAddress:(unsigned long)addr;
- (unsigned long) startAddress;

- setDelegate:anObj;
- delegate;

- checkText:sender;
- minus:sender;
- plus:sender;

/* YES if conflicts found */

- (BOOL) checkRangesForConflicts:(IOAddressRange *)regs num:(unsigned)nregs;

@end
