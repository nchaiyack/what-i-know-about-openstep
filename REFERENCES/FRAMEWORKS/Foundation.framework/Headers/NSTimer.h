/*	NSTimer.h
	
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/
 
#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

@interface NSTimer : NSObject

+ (NSTimer *)timerWithTimeInterval:(NSTimeInterval)ti invocation:(NSInvocation *)invocation repeats:(BOOL)yesOrNo;
+ (NSTimer *)scheduledTimerWithTimeInterval:(NSTimeInterval)ti invocation:(NSInvocation *)invocation repeats:(BOOL)yesOrNo;

+ (NSTimer *)timerWithTimeInterval:(NSTimeInterval)ti target:(id)aTarget selector:(SEL)aSelector userInfo:(id)userInfo repeats:(BOOL)yesOrNo;
+ (NSTimer *)scheduledTimerWithTimeInterval:(NSTimeInterval)ti target:(id)aTarget selector:(SEL)aSelector userInfo:(id)userInfo repeats:(BOOL)yesOrNo;

- (void)fire;

- (NSDate *)fireDate;

#if !defined(STRICT_OPENSTEP)
- (NSTimeInterval)timeInterval;
#endif /* !STRICT_OPENSTEP */

- (void)invalidate;
- (BOOL)isValid;

- (id)userInfo;

@end

