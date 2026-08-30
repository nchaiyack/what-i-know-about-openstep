/*
	NSTextField.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>

@interface NSTextField : NSControl
{
    id	_delegate;
    SEL	_errorAction;
}

- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;
- (void)setDrawsBackground:(BOOL)flag;
- (BOOL)drawsBackground;
- (void)setTextColor:(NSColor *)color;
- (NSColor *)textColor;
- (BOOL)isBordered;
- (void)setBordered:(BOOL)flag;
- (BOOL)isBezeled;
- (void)setBezeled:(BOOL)flag;
- (BOOL)isEditable;
- (void)setEditable:(BOOL)flag;
- (BOOL)isSelectable;
- (void)setSelectable:(BOOL)flag;
- (void)setPreviousText:(id)anObject;
- (id)previousText;
- (void)setNextText:(id)anObject;
- (id)nextText;
- (SEL)errorAction;
- (void)setErrorAction:(SEL)aSelector;
- (void)selectText:(id)sender;
- (id)delegate;
- (void)setDelegate:(id)anObject;
- (BOOL)textShouldBeginEditing:(NSText *)textObject;
- (BOOL)textShouldEndEditing:(NSText *)textObject;
- (void)textDidBeginEditing:(NSNotification *)notification;
- (void)textDidEndEditing:(NSNotification *)notification;
- (void)textDidChange:(NSNotification *)notification;
- (BOOL)acceptsFirstResponder;
@end

#ifndef STRICT_OPENSTEP
@interface NSTextField(NSKeyboardUI)
- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand;
@end
#endif


#ifndef STRICT_OPENSTEP

@interface NSTextField(NSTextFieldAttributedStringMethods)
- (BOOL)allowsEditingTextAttributes;
- (void)setAllowsEditingTextAttributes:(BOOL)flag;
- (BOOL)importsGraphics;
- (void)setImportsGraphics:(BOOL)flag;
@end

#endif
