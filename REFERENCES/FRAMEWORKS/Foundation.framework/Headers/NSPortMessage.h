/*      NSPortMessage.h
	A slightly abstract Foundation IPC communication unit
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/

#if !defined(STRICT_OPENSTEP)

#import <Foundation/NSObject.h>

@class NSPort, NSDate, NSArray, NSMutableArray;

@interface NSPortMessage : NSObject {
    @private
    NSPort 		*localPort;
    NSPort 		*remotePort;
    NSMutableArray 	*components;
    unsigned		msgid;
    unsigned		refCount;
    void		*reserved;
}

- (id)initWithSendPort:(NSPort *)sendPort receivePort:(NSPort *)replyPort components:(NSArray *)components;

- (NSArray *)components;
- (NSPort *)receivePort;
- (NSPort *)sendPort;
- (BOOL)sendBeforeDate:(NSDate *)date;

- (id)initWithMachMessage:(void *)buf;
- (unsigned)msgid;
- (void)setMsgid:(unsigned)msgid;
@end

#endif /* !STRICT_OPENSTEP */
