/*
 *  NTThread.h
 * 	Copyright 1994, NeXT Computer, Inc.
 *	
 *	Category on NSThread to support scheduling controls for threads.
 *	NULL implementation on strict OPENSTEP platforms.
 *
 *	13 Oct 1994 mpaque Created.
 */

#import <Foundation/NSThread.h>


typedef enum {
	NTThreadPolicy_Timeshare,
	NTThreadPolicy_FixedPriority
} NTThreadPolicy;

typedef enum {
	NTThreadPriority_RealTime = 0,
	NTThreadPriority_UrgentIO = 1,
	NTThreadPriority_NormalIO = 2,
	NTThreadPriority_Housekeeping = 3
} NTThreadPriority;

/*
 * A class for representing a thread of execution within the NT server.
 *
 * NTThreads also hold generally useful thread dependent information.
 *
 */
@interface NSThread(NEXTIME_Extensions)

/* Scheduling goodies */
- (void) yield;
- (void) yieldToThread:(NSThread *)thread;
- (void) yieldForInterval:(double)interval;
- (void) yieldToThread:(NSThread *)thread forInterval:(double)interval;
- (void)wakeup;

/* Naming a thread */
- (void)setName:(NSString *)name;
- (NSString *)name;

/* Thread policy and priority controls */
- (void)setPolicy:(NTThreadPolicy)policy;
- (void)setPriority:(NTThreadPriority)priority;
- (NTThreadPolicy)policy;
- (NTThreadPriority)priority;

@end

