/*
	NSEPSImageRep.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#import <AppKit/NSImageRep.h>

@interface NSEPSImageRep : NSImageRep {
    NSPoint _bBoxOrigin;
    NSData *_epsData;
    unsigned int _reserved;
}

+ (id)imageRepWithData:(NSData *)epsData;	/* Convenience of initWithData: */
- (id)initWithData:(NSData *)epsData;

- (void)prepareGState;

- (NSData *)EPSRepresentation;

- (NSRect)boundingBox;

@end

