/*
	NSSliderCell.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#import <AppKit/NSActionCell.h>

@interface NSSliderCell : NSActionCell
{
    NSImage	*_knobImage;
    float	_knobThickness;
    NSImage	*_backImage;
    id		_textCell;
    double	_altIncValue;
    double	_value;
    double	_maxValue;
    double	_minValue;
    NSRect	_trackRect;
    struct __sliderCellFlags {
        unsigned int weAreVertical:1;
        unsigned int weAreVerticalSet:1;
        unsigned int backImageWasResized:1;
        unsigned int reservedSliderCell:29;
    } _scFlags;
}


+ (BOOL)prefersTrackingUntilMouseUp;


- (double)minValue;
- (void)setMinValue:(double)aDouble;
- (double)maxValue;
- (void)setMaxValue:(double)aDouble;
- (void)setAltIncrementValue:(double)incValue;
- (double)altIncrementValue;
- (int)isVertical;
- (void)setTitleColor:(NSColor *)newColor;
- (NSColor *)titleColor;
- (void)setTitleFont:(NSFont *)fontObj;
- (NSFont *)titleFont;
- (NSString *)title;
- (void)setTitle:(NSString *)aString;
- (void)setTitleCell:(NSCell *)aCell;
- (id)titleCell;
- (void)setKnobThickness:(float)aFloat;
- (float)knobThickness;
- (NSRect)knobRectFlipped:(BOOL)flipped;
- (void)drawKnob:(NSRect)knobRect;
- (void)drawKnob;
- (void)drawBarInside:(NSRect)aRect flipped:(BOOL)flipped;
- (NSRect)trackRect;	// Only valid while tracking the mouse!

@end
