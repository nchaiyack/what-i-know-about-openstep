/*
        NSStringDrawing.h
        Copyright (c) 1994-1996 NeXT Software, Inc.  All rights reserved.

        Methods to deal with NSString drawing, measuring
   
*/

#ifndef STRICT_OPENSTEP

#import <Foundation/Foundation.h>
#import <AppKit/NSAttributedString.h>

@interface NSString(NSStringDrawing)

- (NSSize)sizeWithAttributes:(NSDictionary *)attrs;
- (void)drawAtPoint:(NSPoint)point withAttributes:(NSDictionary *)attrs;
- (void)drawInRect:(NSRect)rect withAttributes:(NSDictionary *)attrs;

@end

@interface NSAttributedString(NSStringDrawing)

- (NSSize)size;
- (void)drawAtPoint:(NSPoint)point;
- (void)drawInRect:(NSRect)rect;

@end

#endif
