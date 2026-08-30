/*
	NSInputServer.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#ifndef STRICT_OPENSTEP

#import <Foundation/NSString.h>
#import <AppKit/NSEvent.h>

@interface NSInputServer : NSObject {
@protected
    NSString *_name;
    id _connection;
    NSMutableDictionary *_connDict;
    id _delegate;
    int _reservedInputServer1;
    int _reservedInputServer2;
}

- initWithDelegate:(id)aDelegate name:(NSString *)name;

@end

/* These methods must be implemented by the delegate.
*/
@interface NSInputServer(NSInputServerDelegateMethods)

/* the "flag" indicates the "active/inactive" state of the sender.  This message is sent on both activation and de-activation, with different "flag".
*/
- (void) setActivated:(BOOL)flag sender:(id)sender;

- (void) insertText:(NSString *)aString sender:(id)sender conversation:(long)conv;
- (void) doCommandBySelector:(SEL)aSelector sender:(id)sender conversation:(long)conv;
- (void) markedTextWillBeAbandoned:(id)sender conversation:(long)conv;
- (void) markedTextSelectionChanged:(NSRange)newSel sender:(id)sender conversation:(long)conv;
- (void) cancelInput:(id)sender conversation:(long)conv;
- (void) terminate:(id)sender;

/* Normally canBeDisabled returns YES and is implemented that way in the abstract NSInputServer class.
*/
- (BOOL) canBeDisabled;

/* Many existing input servers have built-in key bindings that affect what happens within the marked region.  If such an input server wants to handle ALL key events through insertText:sender:conversation: and never receive doCommandBySelector:sender:conversation:, then it should respond (consistently) YES to this method.  The default is NO.  The processing of incoming events looks at this flag as reflected in the corresponding NSInputManager, before deciding how to deal with events.  A module which responds YES to this method must be prepared to deal with arbitrary strings of Unicode characters under all circumstances whenever it is active.
*/
- (BOOL)wantsToInterpretAllKeystrokes;

#ifndef STRICT_40
/* These methods are sent by current input manager when the application changes state so that the server can update its concept of who's current.  The actually "active" sender is the last one to have sent a senderDidBecomeActive: message.  They may not arrive in the expected order.
*/
- (void) senderDidBecomeActive:(id)sender;
- (void) senderDidResignActive:(id)sender;

/* This method is sent by input manager when the conversation within a particular sender changes.
*/
- (void) activeConversationWillChange:(id)sender oldConversation:(long)oldConversation newConversation:(long)newConversation;
#endif

@end

#endif
