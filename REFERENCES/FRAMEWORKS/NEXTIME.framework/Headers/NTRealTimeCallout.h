/*
 *	NTRealTimeCallout.h
 * 	Copyright 1993, NeXT, Inc.
 *	
 *	21Dec93 mpaque Created.
 */

#import "NTThread.h"

// timer function pointer type
typedef void (*timerFunc)(void *arg, double now);

//
// NTScheduleCallback:
//
//	Schedule a callback to be performed at some absolute real time.
//	The callback is dequeued when that time arrives.
//
 void
NTScheduleCallback(	NTThreadPriority priority,
			timerFunc func,
			void *	arg,
			double	time );
//
// NTDescheduleCallback:
//
//	Remove a previously scheduled callback from a queue.
//
 void
NTDescheduleCallback(	NTThreadPriority priority,
			timerFunc func,
			void *	arg );

//
// NTDescheduleCallbackAtomically:
//	Sampe as above, except will wait for any pending callout to complete
//	Will deadlock if called from the callout routine itself.
//
 void
NTDescheduleCallbackAtomically(	NTThreadPriority priority,
					timerFunc func,
					void *	arg );

//
// NTCurrentRealTime:
//
//	Report the callout system's idea of the current real time.
//	The origin point for the time value is OS-dependent.  The
//	value is normally used only in measuring intervals.
double NTCurrentRealTime(void);

