/*
	obsoleteSpeaker.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/obsoleteListener.h>
#import <mach/message.h>
#import <mach/port.h>

@interface Speaker : NSObject <NSCoding>
{
    port_t              sendPort;
    port_t              replyPort;
    int                 sendTimeout;
    int                 replyTimeout;
    id                  delegate;
    int                 _reservedSpeaker1;
    int                 _reservedSpeaker2;
}



- (id)delegate;
- (void)setDelegate:(id)anObject;
- (port_t)sendPort;
- (void)setSendPort:(port_t)aPort;
- (port_t)replyPort;
- (void)setReplyPort:(port_t)aPort;
- (int)sendTimeout;
- (void)setSendTimeout:(int)ms;
- (int)replyTimeout;
- (void)setReplyTimeout:(int)ms;
- (int)performRemoteMethod:(NSString *)msgSelector;
- (int)performRemoteMethod:(NSString *)msgSelector with:(const char *)data length:(int)numBytes;
- (int)selectorRPC:(NSString *)msgSelector paramTypes:(char *)params, ...;



/* use [Application workspace] instead of these messages unless you need to send them to the port of a specific app */
- (int)sendOpenFileMsg:(NSString *)fullPath ok:(int *)flag andDeactivateSelf:(BOOL)doDeact;
- (int)sendOpenTempFileMsg:(NSString *)fullPath ok:(int *)flag andDeactivateSelf:(BOOL)doDeact;
- (int)openFile:(NSString *)fullPath ok:(int *)flag;
- (int)openTempFile:(NSString *)fullPath ok:(int *)flag;

- (int)msgQuit:(int *)flag;
- (int)msgCalc:(int *)flag;
- (int)msgDirectory:(char * const *)fullPath ok:(int *)flag;
- (int)msgVersion:(char * const *)aString ok:(int *)flag;
- (int)msgFile:(char * const *)fullPath ok:(int *)flag;
- (int)msgPrint:(const char *)fullPath ok:(int *)flag;
- (int)msgSelection:(char * const *)bytes length:(int *)len asType:(const char *)aType ok:(int *)flag;
- (int)msgSetPosition:(const char *)aString posType:(NSMsgPositionType)aPosition andSelect:(int)sflag ok:(int *)flag;
- (int)msgPosition:(char * const *)aString posType:(int *)anInt ok:(int *)flag;
- (int)msgCopyAsType:(const char *)aType ok:(int *)flag;
- (int)msgCutAsType:(const char *)aType ok:(int *)flag;
- (int)msgPaste:(int *)flag;

@end
