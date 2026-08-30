/*
 * ProgressView.m
 * Copyright (c) 1997 NeXT Software, Inc.
 * All rights reserved.
 *
 * You may freely copy, distribute and reuse the code in this example.
 * NeXT disclaims any warranty of any kind, expressed or implied,
 * as to its fitness for any particular use.
 */

#import "ProgressView.h"

#define DEFAULT_PERCENTAGE_INCREMENT 5
#define DEFAULT_PERCENTAGE 0

@implementation ProgressView

+ (void)initialize
{
    if (self == [ProgressView class]) {
        [self setVersion:1];
    }
}

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    percentageIncrement = DEFAULT_PERCENTAGE_INCREMENT;
    percentage = DEFAULT_PERCENTAGE;
    return self;
}

- (void)drawRect:(NSRect)rect
{
    NSRect	bounds;
    NSRect	r;

    [[NSColor controlColor] set];
    NSRectFill(rect);
    
    bounds = [self bounds];
    if (percentage > 0) {
	r = bounds;
        r.size.width = NSWidth(r) * percentage / 100;
	r = NSIntersectionRect(r, rect);
	if (!NSIsEmptyRect(r)) {
	    [[NSColor controlShadowColor] set];
	    NSRectFill(r);
	}
    }

    [[NSColor controlDarkShadowColor] set];
    NSFrameRect(bounds);
}

- (float)percentageIncrement
{
    return percentageIncrement;
}

- (void)setPercentageIncrement:(float)newPercentageIncrement
{
    percentageIncrement = newPercentageIncrement;
}

- (float)percentage
{
    return percentage;
}

- (void)setPercentage:(float)newPercentage
{
    if (newPercentage > 100) {
	newPercentage = 100;
    } else if (newPercentage < 0) {
	newPercentage = 0;
    }
    if (percentage != newPercentage) {
        percentage = newPercentage;
        [self setNeedsDisplay:YES];
    }
}

- (void)increment:(id)sender
{
    /* Let the above method do bounds checking & redisplay for us. */
    [self setPercentage:(percentage + percentageIncrement)];
}

- (id)initWithCoder:(NSCoder *)decoder
{
    int		version;

    self = [super initWithCoder:decoder];

    version = [decoder versionForClassName:@"ProgressView"];
    switch (version) {
    case 1:
	[decoder decodeValueOfObjCType:@encode(float) at:&percentageIncrement];
	[decoder decodeValueOfObjCType:@encode(float) at:&percentage];
	break;
    default:
	percentageIncrement = DEFAULT_PERCENTAGE_INCREMENT;
	percentage = DEFAULT_PERCENTAGE;
	break;
    }
    return self;
}

- (void)encodeWithCoder:(NSCoder *)coder
{
    [super encodeWithCoder:coder];

    // Version == 1
    [coder encodeValueOfObjCType:@encode(float) at:&percentageIncrement];
    [coder encodeValueOfObjCType:@encode(float) at:&percentage];
}

@end
