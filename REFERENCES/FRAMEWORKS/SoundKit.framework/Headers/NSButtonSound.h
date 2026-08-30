
/*
 * NSButtonSound.h
 *
 * Categories on NSButtonCell and NSButton for dragging a sound
 * onto a button.
 *
 * Copyright (c) 1995, NeXT Computer, Inc.  All rights reserved. 
 */

#import <AppKit.h>

@interface NSButtonCell (NSButtonCellSound)

- (void) setSound: aSound;
- sound;

@end


@interface NSButton (NSButtonSound)

- (void) setSound: aSound;
- sound;

@end
