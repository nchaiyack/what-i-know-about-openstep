/*
	NSScroller.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>

typedef enum _NSScrollArrowPosition {
    NSScrollerArrowsMaxEnd		= 0,
    NSScrollerArrowsMinEnd		= 1,
    NSScrollerArrowsNone		= 2
} NSScrollArrowPosition;

typedef enum _NSUsableScrollerParts {
    NSNoScrollerParts			= 0,
    NSOnlyScrollerArrows		= 1,
    NSAllScrollerParts			= 2
} NSUsableScrollerParts;

typedef enum _NSScrollerPart {
    NSScrollerNoPart			= 0,
    NSScrollerDecrementPage		= 1,
    NSScrollerKnob			= 2,
    NSScrollerIncrementPage		= 3,
    NSScrollerDecrementLine    		= 4,
    NSScrollerIncrementLine	 	= 5,
    NSScrollerKnobSlot			= 6
} NSScrollerPart;

typedef enum _NSScrollerArrow {
    NSScrollerIncrementArrow		= 0,
    NSScrollerDecrementArrow		= 1
} NSScrollerArrow;

@interface NSScroller : NSControl
{
    float               _curValue;
    float               _percent;
    float		_knobSize;
    int                 _hitPart;
    id                  _target;
    SEL                 _action;
    struct _sFlags {
	unsigned int		isHoriz:1;
        NSScrollArrowPosition	arrowsLoc:2;
        NSUsableScrollerParts	partsUsable:2;
	unsigned int		fine:1;
	unsigned int		needsEnableFlush:1;
	unsigned int		thumbing:1;
	unsigned int		slotDrawn:1;
	unsigned int		knobDrawn:1;
        unsigned int            lit:1;
        unsigned int		RESERVED:21;
    } sFlags;
}

+ (float)scrollerWidth;

- (void)drawParts;
- (NSRect)rectForPart:(NSScrollerPart)partCode;
- (void)checkSpaceForParts;
- (NSUsableScrollerParts)usableParts;
- (void)setArrowsPosition:(NSScrollArrowPosition)where;
- (NSScrollArrowPosition)arrowsPosition;
- (void)drawArrow:(NSScrollerArrow)whichArrow highlight:(BOOL)flag;
- (void)drawKnob;
- (void)highlight:(BOOL)flag;
- (NSScrollerPart)testPart:(NSPoint)thePoint;
- (void)trackKnob:(NSEvent *)theEvent;
- (void)trackScrollButtons:(NSEvent *)theEvent;
- (NSScrollerPart)hitPart;
- (void)setFloatValue:(float)aFloat knobProportion:(float)percent;
- (float)knobProportion;

@end
