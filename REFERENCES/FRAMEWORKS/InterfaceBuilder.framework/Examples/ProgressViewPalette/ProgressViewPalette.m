/*
 * ProgressViewPalette.m
 * Copyright (c) 1997 NeXT Software, Inc.
 * All rights reserved.
 * Written by James DiPalma.
 *
 * You may freely copy, distribute and reuse the code in this example.
 * NeXT disclaims any warranty of any kind, expressed or implied,
 * as to its fitness for any particular use.
 */

#import "ProgressViewPalette.h"

@implementation ProgressViewPalette

- (void)finishInstantiate
{
    /* `finishInstantiate' can be used to associate non-view objects with
     * a view in the palette's nib.  For example:
     *   [self associateObject:aNonUIObject ofType:IBObjectPboardType
     *                withView:aView];
     */
}

@end

@implementation ProgressView (ProgressViewPaletteInspector)

- (NSString *)inspectorClassName
{
    return @"ProgressViewInspector";
}

@end
