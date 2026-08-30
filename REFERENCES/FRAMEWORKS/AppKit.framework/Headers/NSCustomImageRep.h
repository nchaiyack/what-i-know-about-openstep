/*
	NSCustomImageRep.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#import <AppKit/NSImageRep.h>

@interface NSCustomImageRep : NSImageRep {
    SEL _drawMethod;
    id _drawObject;
    unsigned int _reserved;
}

- (id)initWithDrawSelector:(SEL)aMethod delegate:(id)anObject;
- (SEL)drawSelector;
- (id)delegate;

@end

