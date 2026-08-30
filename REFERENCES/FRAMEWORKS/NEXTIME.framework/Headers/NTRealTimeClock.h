/*
 *	NTClock.m
 * 	Copyright 1991, NeXT Computer, Inc.
 *	
 *	25Sept91 mpaque Created.
 *	21Dec93	mpaque	Revised to meet NEXTIME requirements.
 */
#import "NTClock.h"
#import "NTRealTimeCallout.h"



@interface NTRealTimeClock : NTClock
{
	// Internal state used to drive alarm scheduling
	BOOL				inAlarmEvent;
	BOOL				timerPending;
	int				suppressAlarmQueue;
	// Delayed perform callback priority
	NTThreadPriority		priority;
	double				alarmLeadTime;
	double				alarmRealTime;
}
- init;
- (void)dealloc;
- (void)setPriority:(NTThreadPriority)priority;
- (NTThreadPriority)priority;

@end
