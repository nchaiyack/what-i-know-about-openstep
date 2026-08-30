/*	NSProxy.h
	Class to subclass for easily defining proxies
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSMethodSignature, NSInvocation;

@interface NSProxy <NSObject> {
    Class	isa;
}

+ (id)allocWithZone:(NSZone *)zone;

+ (id)alloc;

+ (Class)class;

+ (void)load;

#if !defined(STRICT_OPENSTEP)

+ (BOOL)respondsToSelector:(SEL)aSelector;

#endif

- (void)forwardInvocation:(NSInvocation *)invocation;

- (NSMethodSignature *)methodSignatureForSelector:(SEL)sel;

- (void)dealloc;

- (NSString *)description;

@end

