/*
 *  NTSampleFIFO.h
 * 	Copyright 1993, NeXT Computer, Inc.
 *	
 *
 *
 *	23 Nov 1993 mpaque Created.
 */
#import <Foundation/NSObject.h>
#import "NTSampleBuffer.h"
#import "NTSampleProcessor.h"

@class NSLock;

@interface NTSampleFIFO: NSObject  <NTSampleConsumer>
{
@private
	id <NTSampleBuffer> *	fifo;
	int			head;
	int			tail;
	int			capacity;
	
	id <NTSampleBuffer>	pushBack;

	NSLock *		lock;		// (optional) lock
	double			FIFODepth;	// in seconds
	double			headTime;	// in seconds
	double			tailTime;	// in seconds
	
	BOOL			atEndOfData;	// FIFO source is exhausted
}

+ (void)initialize;
+ (void)useLockForFIFOAccess:(BOOL)useLock;

- init;
- (void)dealloc;

/* Control API */
- (void)setFIFODepth:(double)seconds;
- (double)FIFODepth;
- (void)reset;

/* Write to FIFO API */
- (void)writeSample:(id <NTSampleBuffer>)sample;
- (void)markEndOfData;
- (double)timeTilNextAppend;			// Negative if FIFO is below
						// set depth in seconds.

/* Read from FIFO API */
- (id <NTSampleBuffer>)nextSample;		// Returns nil if FIFO is empty
- (void) requeueSample:(id <NTSampleBuffer>)sample; // Push a sample back onto
						// the FIFO.  One level of
						// pushback is supported.
- (double)nextSampleTime;			// Returns -1.0 if empty
- (BOOL)atEndOfData;				// Returns YES if empty
						// and writer has issued
						// markEndOfData.

@end
