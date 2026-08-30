/*
 * ProgressViewInspector.h
 * Copyright (c) 1997 NeXT Software, Inc.
 * All rights reserved.
 * Written by James DiPalma.
 *
 * You may freely copy, distribute and reuse the code in this example.
 * NeXT disclaims any warranty of any kind, expressed or implied,
 * as to its fitness for any particular use.
 */

#import <InterfaceBuilder/InterfaceBuilder.h>

@interface ProgressViewInspector : IBInspector
{
    IBOutlet NSSlider		*slider;
    IBOutlet NSTextField	*textField;
}
@end
