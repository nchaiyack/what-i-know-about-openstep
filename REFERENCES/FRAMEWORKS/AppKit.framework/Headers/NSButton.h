/*
	NSButton.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSButtonCell.h>

@interface NSButton : NSControl

- (NSString *)title;
- (void)setTitle:(NSString *)aString;
- (NSString *)alternateTitle;
- (void)setAlternateTitle:(NSString *)aString;
- (NSImage *)image;
- (void)setImage:(NSImage *)image;
- (NSImage *)alternateImage;
- (void)setAlternateImage:(NSImage *)image;
- (NSCellImagePosition)imagePosition;
- (void)setImagePosition:(NSCellImagePosition)aPosition;
- (void)setButtonType:(NSButtonType)aType;
- (int)state;
- (void)setState:(int)value;
- (BOOL)isBordered;
- (void)setBordered:(BOOL)flag;
- (BOOL)isTransparent;
- (void)setTransparent:(BOOL)flag;
- (void)setPeriodicDelay:(float)delay interval:(float)interval;
- (void)getPeriodicDelay:(float *)delay interval:(float *)interval;
- (NSString *)keyEquivalent;
- (void)setKeyEquivalent:(NSString *)charCode;
- (unsigned int)keyEquivalentModifierMask;
- (void)setKeyEquivalentModifierMask:(unsigned int)mask;
- (void)highlight:(BOOL)flag;
- (BOOL)performKeyEquivalent:(NSEvent *)key;
- (void)performClick:(id)sender;

@end

#ifndef STRICT_OPENSTEP
@interface NSButton(NSKeyboardUI)
- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand;
@end
#endif

#ifndef STRICT_OPENSTEP

@interface NSButton(NSButtonAttributedStringMethods)
- (NSAttributedString *)attributedTitle;
- (void)setAttributedTitle:(NSAttributedString *)aString;
- (NSAttributedString *)attributedAlternateTitle;
- (void)setAttributedAlternateTitle:(NSAttributedString *)obj;
@end

#endif
