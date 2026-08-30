/*
 * ProgressViewInspector.m
 * Copyright (c) 1997 NeXT Software, Inc.
 * All rights reserved.
 * Written by James DiPalma.
 *
 * You may freely copy, distribute and reuse the code in this example.
 * NeXT disclaims any warranty of any kind, expressed or implied,
 * as to its fitness for any particular use.
 */

#import "ProgressViewInspector.h"
#import "ProgressView.h"

@implementation ProgressViewInspector

- (id)init
{
    self = [super init];
    [NSBundle loadNibNamed:@"ProgressViewInspector" owner:self];
    return self;
}

- (void)ok:(id)sender
{
    if (sender == slider) {
        [[self object] setPercentageIncrement:[slider intValue]];
        [textField setIntValue:[slider intValue]];
    } else if (sender == textField) {
        [[self object] setPercentageIncrement:[textField floatValue]];
        [slider setFloatValue:[textField floatValue]];
    }
    [super ok:sender];
}

- (void)revert:(id)sender
{
    float	percentageIncrement;
    percentageIncrement = [[self object] percentageIncrement];
    [slider setFloatValue:percentageIncrement];
    [textField setFloatValue:percentageIncrement];
    [super revert:sender];
}

- (BOOL)wantsButtons
{
    return NO;
}

@end
