/*	NSLock.h
	Support for locks
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSDate;
	
@protocol NSLocking

- (void)lock;
- (void)unlock;

@end

@interface NSLock : NSObject <NSLocking> {
    void *_priv;
}

- (BOOL)tryLock;

#if !defined(STRICT_OPENSTEP)

- (BOOL)lockBeforeDate:(NSDate *)limit;

#endif /* !STRICT_OPENSTEP */

@end

@interface NSConditionLock : NSObject <NSLocking> {
    void *_priv;
}

- (id)initWithCondition:(int)condition;

- (int)condition;
- (void)lockWhenCondition:(int)condition;
- (BOOL)tryLock;
- (BOOL)tryLockWhenCondition:(int)condition;
- (void)unlockWithCondition:(int)condition;

#if !defined(STRICT_OPENSTEP)

- (BOOL)lockBeforeDate:(NSDate *)limit;
- (BOOL)lockWhenCondition:(int)condition beforeDate:(NSDate *)limit;

#endif /* !STRICT_OPENSTEP */

@end

@interface NSRecursiveLock : NSObject <NSLocking> {
    void *_priv;
}

- (BOOL)tryLock;

#if !defined(STRICT_OPENSTEP)

- (BOOL)lockBeforeDate:(NSDate *)limit;

#endif /* !STRICT_OPENSTEP */

@end
