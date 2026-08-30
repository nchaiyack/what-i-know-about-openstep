/*	NSRunLoop.h
	An input manager.
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/
 
#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSMapTable.h>

@class NSTimer;

#if !defined(STRICT_OPENSTEP)

@class NSPort;

#endif /* !STRICT_OPENSTEP */

@interface NSRunLoop : NSObject {
    void	*_modes;
    id		_currentMode;
    id		_callout;
    void	*_callouts;
    void	*_timers;
    id		_condition;
    void	*_currentSet;
    char	*_msg;
    void	*_performers;
    id		_wakeupPort;
    id          _winMessagePort;
}

+ (NSRunLoop *)currentRunLoop;
- (NSString *)currentMode;

- (void)addTimer:(NSTimer *)timer forMode:(NSString *)mode;

#if !defined(STRICT_OPENSTEP)

- (void)addPort:(NSPort *)aPort forMode:(NSString *)mode;
- (void)removePort:(NSPort *)aPort forMode:(NSString *)mode;

#endif /* !STRICT_OPENSTEP */

- (NSDate *)limitDateForMode:(NSString *)mode;
- (void)acceptInputForMode:(NSString *)mode beforeDate:(NSDate *)limitDate;

@end

FOUNDATION_EXPORT NSString *NSDefaultRunLoopMode;

@interface NSRunLoop (NSRunLoopConveniences)

- (void)run; 
- (void)runUntilDate:(NSDate *)limitDate;
- (BOOL)runMode:(NSString *)mode beforeDate:(NSDate *)limitDate;

#if !defined(STRICT_OPENSTEP) && !defined(STRICT_41) && !defined(STRICT_40)
- (void)configureAsServer;
#endif

@end

/**************** 	Delayed perform	 ******************/

@interface NSObject (NSDelayedPerforming)

#if !defined(STRICT_OPENSTEP)
- (void)performSelector:(SEL)aSelector withObject:(id)anArgument afterDelay:(NSTimeInterval)delay inModes:(NSArray *)modes;
#endif !defined(STRICT_OPENSTEP)
- (void)performSelector:(SEL)aSelector withObject:(id)anArgument afterDelay:(NSTimeInterval)delay;
+ (void)cancelPreviousPerformRequestsWithTarget:(id)aTarget selector:(SEL)aSelector object:(id)anArgument;

@end

#if !defined(STRICT_OPENSTEP)

@interface NSRunLoop (NSOrderedPerform)
- (void)performSelector:(SEL)aSelector target:(id)target argument:(id)arg order:(unsigned)order modes:(NSArray *)modes;
- (void)cancelPerformSelector:(SEL)aSelector target:(id)target argument:(id)arg;
@end

#endif !defined(STRIC_OPENSTEP)

#if !defined(STRICT_OPENSTEP)

/**************** 	Delegate methods	 ******************/

@interface NSObject (NSRunLoopPortDelegateMethods)

- (NSDate *)limitDateForMode:(NSString *)mode;

@end

#endif /* !STRICT_OPENSTEP */
