/*
	NSSlider.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>

@interface NSSlider : NSControl

- (double)minValue;
- (void)setMinValue:(double)aDouble;
- (double)maxValue;
- (void)setMaxValue:(double)aDouble;
- (void)setTitleCell:(NSCell *)aCell;
- (id)titleCell;
- (void)setTitleColor:(NSColor *)newColor;
- (NSColor *)titleColor;
- (void)setTitleFont:(NSFont *)fontObj;
- (NSFont *)titleFont;
- (NSString *)title;
- (void)setTitle:(NSString *)aString;
- (void)setKnobThickness:(float)aFloat;
- (float)knobThickness;
- (void)setImage:(NSImage *)backgroundImage;
- (NSImage *)image;
- (int)isVertical;
- (BOOL)acceptsFirstMouse:(NSEvent *)theEvent;

@end
