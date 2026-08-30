/*
 *	NTClock.h
 * 	Copyright 1991, NeXT Computer, Inc.
 *	
 *	25Sept91 mpaque Created.
 *	20Dec93	mpaque	Revised to meet NEXTIME requirements.
 */
#import <Foundation/NSObject.h>

typedef enum
{
	NTTimeDirectionReverse = -1,
	NTTimeDirectionForward = 1
}
NTTimeDirection;

@protocol NTClock <NSObject>
//
// The alarm function schedules a callback.  The method to be called
// should be declared in the form:
//
//	method: (id) sender: (double)time;
//
// The perform: method returns nil if the argument selector or objects
// are invalid.  The method must be implemented in a subclass.
//
- (void)performSelector:(SEL)aSelector object:anObject atTime:(double)time;
- (void)cancelPerform;		// Cancel delayed perform
- (void)disablePerform;		// Inhibit delayed perform
- (void)enablePerform;		// Re-enable inhibited delayed perform

- (BOOL)isReversable;		// Can clock direction be reversed?
- (BOOL)scalesWhenResized;		// Can the clock be scaled out of realtime?
- (BOOL)isSettable;		// Can the clock be set?
- (BOOL)isStoppable;		// Can the clock be stopped?

//
// These set operations return NO if the operation is not permitted
//
- (NTTimeDirection) timeDirection;
- (BOOL)setTimeScale: (double) scale;
- (double) timeScale;
- (BOOL)setTimeOffset: (double) offset;
- (double) timeOffset;
- (BOOL)setCurrentTime: (double) seconds;
- (double) currentTime;
- (BOOL)stop;
- (BOOL)isStopped;		// Returns YES if clock is stopped
- (void)run;

// Forward and inverse transforms of time values
- (double)baseTimeFromClockTime:(double)time;
- (double)clockTimeFromBaseTime:(double)time;
- (double)baseIntervalFromClockInterval:(double)interval;
- (double)clockIntervalFromBaseInterval:(double)interval;

// clock delegate interface
- (void)setDelegate:(id)delegate;
- delegate;

// Slaving a clock to a master clock
- (void)setMasterClock:(id <NTClock>)master;
- (id <NTClock>)masterClock;

// The setMasterClock: method causes a slaved clock to generate the following
// messages to the old and new master clocks:
- (void)removeSlaveClock:(id <NTClock>)slave;
- (void)addSlaveClock:(id <NTClock>)slave;

// Messages sent to slaved clocks
// The 'sender' is the (id <NTClock>) object generating the message.
- (void)masterDidSetCurrentTime: sender;
- (void)masterDidChangeDirection: sender;
- (void)masterDidStop: sender;
- (void)masterWillStart: sender;
- (void)masterDidStart: sender;
@end

//
// FIXME: Perhaps I need a 'clockIsRunning:' callout to indicate that the
// clock is actually running?  Then again, this can be done by scheduling an
// alarm for the currentTime value.
//
@protocol NTClockDelegate <NSObject>
// All clock delegates should conform to this protocol
// The 'sender' is the (id <NTClock>) object generating the message.
- (void)clockDidSetCurrentTime: sender;
- (void)clockDidChangeDirection: sender;
- (void)clockDidStop: sender;
- (void)clockWillStart: sender;
- (void)clockDidStart: sender;
@end

//
// Prototype for callback func.  We call the address of the user's method
// implementation directly, so we can properly pass the (double)
// currentTime value.  The perform:: mechanism won't pass anything
// wider than an (id).  The alarmMethod should be a selector for a 
// method declared in the form:
//
//	- alarmMethod:(id)sender: (double)currentTime;
//
// where 'sender' is the clock instance generating the alarm callback,
// and currentTime is the current time in the sending clock's frame
// of reference.
//
typedef id (*NTIMPalarm)(id, SEL, id, double);

@class NSMutableArray;

@interface NTClock : NSObject <NTClock>
{
	// Capabilities flags
	BOOL			isReversable;
	BOOL			isScalable;
	BOOL			isSettable;
	BOOL			isStoppable;

	BOOL			isStopped;

	// Current alarm event information
	BOOL			alarmSet;	// True if set, not delivered
	double			alarmTime;
	id			alarmInstance;
	SEL			alarmMethod;
	NTIMPalarm		alarmFunc;

	// current direction, NTTimeDirectionForward or
	// NTTimeDirectionReverse, set by sign of timeScale and
	// master clock direction, if a master clock is set.
	NTTimeDirection		timeDirection;

	// Time scaling factor.  The sign sets direction
	double			timeScale;
	double			timeOffset;
	// The clock's idea of the current time
	double			currentTime;
		
	NSMutableArray *	slaveClocks;
	id <NTClock>		masterClock;
	id			delegate;
}

/* Class methods */
+ (void)initialize;			// Class setup

/* Instance methods */
- init;				// Initialize instance

@end

