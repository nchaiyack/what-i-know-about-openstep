/*      NSDistantObject.h
	Class for remote proxies
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/

#import <Foundation/NSProxy.h>

@class Protocol, NSConnection, NSCoder;

@interface NSDistantObject : NSProxy <NSCoding> {
    @private
    id			name;
    unsigned		wire:2;
    unsigned		unused:6;
    unsigned		refCount:24;
    NSConnection	*conn;
    unsigned		wireCount;
    void		*knownSelectors;
    void		*_reserved;
}

+ (NSDistantObject *)proxyWithTarget:(id)target connection:(NSConnection *)connection;
- (id)initWithTarget:(id)target connection:(NSConnection *)connection;

+ (NSDistantObject *)proxyWithLocal:(id)target connection:(NSConnection *)connection;
- (id)initWithLocal:(id)target connection:(NSConnection *)connection;

- (void)setProtocolForProxy:(Protocol *)proto;

- (NSConnection *)connectionForProxy;

@end

