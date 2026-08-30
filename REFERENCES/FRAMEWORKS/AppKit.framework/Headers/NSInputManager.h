/*
	NSInputManager.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
 */

#ifndef STRICT_OPENSTEP

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <AppKit/NSEvent.h>

@protocol NSTextInput

- (void) insertText:(NSString *)aString; // instead of keyDown:
- (void) doCommandBySelector:(SEL)aSelector;
	// setMarkedText: cannot take nil
- (void) setMarkedText:(NSString *)aString selectedRange:(NSRange)selRange;
	// getMarkedText: will never return nil
- (void) getMarkedText:(out NSString **)aString selectedRange:(out NSRange *)aRange;
- (void) unmarkText;
- (BOOL) hasMarkedText;
- (long) conversationIdentifier;

@end

@interface NSInputManager : NSObject <NSTextInput> {
@private
    id _lastClient;
    id _server;			// an NSInputServer obj, usually
    id _bundleObj;		// principal obj instance of bundle, if any
    id _keybindings;		// optional extra bindings, if any
    NSString *_trueName;	// name passed to "init"
    NSString *_connectionName;	// the connection banner
    NSString *_hostName;	// host to run on or nil if own host
    NSString *_procToExec;	// process path, if any
    NSString *_visibleName;	// localized user-visible name
    NSString *_bundleName;	// path to bundle, if any
    unsigned int _flags;
    NSString *_keyBindingsName;	// path to the default bindings, if any
    int _reservedInputManager2;
}

/* The "current input manager" is the one that is receiving input events at the time this method is called.  It may change out from under you, so don't cache the return value.
*/
+ (NSInputManager *) currentInputManager;

- (NSInputManager *) initWithName:(NSString *)inputServerName host:(NSString *)hostName;

- (NSString *) localizedInputManagerName;

/* These messages are sent by Views that conform to the NSTextInput protocol TO the Current Input Manager when things happen via user or programmatic action.  E.g., when the mouse moves outside the marked range, send markedTextWillBeAbandoned:.  If the user selects some new text or moves the mouse within the marked region, send markedTextSelectionChanged:.  Not all input manager/server combinations will allow all changes, but abandoning of the marked region cannot be aborted.
*/ 

- (void) markedTextWillBeAbandoned:(id)cli; /* send before abandoning */
- (void) markedTextSelectionChanged:(NSRange)newSel client:(id)cli; /* send after changing */

/* This corresponds to a server method for input managers that demand to do their own interepretation of command keys as long as they're active.  This will typically be called by a key binder to find out whether it shouldn't just pass along strings.
*/
- (BOOL) wantsToInterpretAllKeystrokes;

@end

#endif
