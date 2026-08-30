/*
	NSTextFieldCell.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#import <AppKit/NSActionCell.h>
#import <AppKit/NSColor.h>

@interface NSTextFieldCell : NSActionCell  {
    NSColor *_backgroundColor;
    NSColor *_textColor;
    struct __tfFlags {
	unsigned int drawsBackground:1;
	unsigned int reservedTextFieldCell:31;
    } _tfFlags;
}


- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;
- (void)setDrawsBackground:(BOOL)flag;
- (BOOL)drawsBackground;
- (void)setTextColor:(NSColor *)color;
- (NSColor *)textColor;
- (NSText *)setUpFieldEditorAttributes:(NSText *)textObj;

@end

