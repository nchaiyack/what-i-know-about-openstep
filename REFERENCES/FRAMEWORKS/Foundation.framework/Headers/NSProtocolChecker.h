/*	NSProtocolChecker.h
	Message filtering
	Copyright 1995-1996, NeXT Software, Inc.  All rights reserved.
*/

#if !defined(STRICT_OPENSTEP)

#import <Foundation/NSProxy.h>
#import <Foundation/NSObject.h>

@interface NSProtocolChecker : NSProxy

- (Protocol *)protocol;
- (NSObject *)target;

@end

@interface NSProtocolChecker (NSProtocolCheckerCreation)

+ (id)protocolCheckerWithTarget:(NSObject *)anObject protocol:(Protocol *)aProtocol;
- (id)initWithTarget:(NSObject *)anObject protocol:(Protocol *)aProtocol;

@end

#endif /* !STRICT_OPENSTEP */

