/*
 * ProgressView.h
 * Copyright (c) 1997 NeXT Software, Inc.
 * All rights reserved.
 *
 * You may freely copy, distribute and reuse the code in this example.
 * NeXT disclaims any warranty of any kind, expressed or implied,
 * as to its fitness for any particular use.
 */

#import <AppKit/AppKit.h>

@interface ProgressView : NSView
{
    float	percentageIncrement;
    float	percentage;
}
- (float)percentageIncrement;
- (void)setPercentageIncrement:(float)percentageIncrement;
- (float)percentage;
- (void)setPercentage:(float)percentageComplete;
- (void)increment:(id)sender;	// Increment by `percentageIncrement'.
@end
