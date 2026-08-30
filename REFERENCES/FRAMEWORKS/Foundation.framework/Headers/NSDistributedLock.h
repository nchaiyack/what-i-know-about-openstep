/*	NSDistributedLock.h
	Basic file-system-based lock
	Copyright 1995-1996, NeXT Software, Inc.  All rights reserved.
*/

#if !defined(STRICT_OPENSTEP)

#import <Foundation/NSObject.h>

@class NSDate;

@interface NSDistributedLock : NSObject {
    void *_priv;
}

+ (NSDistributedLock *)lockWithPath:(NSString *)path;  

- (id)initWithPath:(NSString *)path;

- (BOOL)tryLock;
- (void)unlock;
- (void)breakLock;
- (NSDate *)lockDate;

@end

#endif /* !STRICT_OPENSTEP */
