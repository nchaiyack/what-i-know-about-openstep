/*
 *	NTMedia.h
 * 	Copyright 1993, NeXT Computer, Inc.
 *	
 *	01Mar93 mpaque Created.
 *	06Jan94	mpaque	Revised and merged with protocol defs.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSDictionary.h>
#import	"movies.h"
#import	"status.h"
#import "NTValueDictionary.h"
#import "NTDictionaryKeys.h"
#import "NTSampleBuffer.h"
#import "NTFileIO.h"
#import "NTSampleProcessorProtocol.h"
#import "NTClock.h"

/*
 * A protocol for messaging a media.  Media hold sample and timing information.
 *
 */
@protocol NTMedia	<NTSampleConsumer>
- (void) setStatus:(NTStatusCode)value;
- (NTStatusCode) status;
- (NSString *)type;
- (void)setType:(NSString *)typeName;
- (void) setPlayHints:(NTPlayHintFlags)hints;
- (NTPlayHintFlags)playHints;
- (void)setShadowSyncSample:(int)shadow forSample:(int)sample;
- (int)shadowSyncSample:(int)sample;
- (double)duration;
- (double) tolerance;
- (void)setTrack:(id)track;
- (id)track;
- (void)setQuality:(int)quality;
- (int)quality;
- (BOOL)setDefaultDataReference:(NSString *)filename;
- (NSString *)defaultDataReference;
- (void)setCreationDate:(NSDate *)date;
- (NSDate *)creationDate;
- (void)setModificationDate:(NSDate *)date;
- (NSDate *)modificationDate;
- (int)dataSizeForTime:(double)time duration:(double)duration;
- (unsigned)sampleCount;
- (BOOL)hasNonSyncSamples;
- (BOOL)hasFixedSampleSize;
- (unsigned) sampleDescriptionCount;
- (void) addSampleDescription:	(bycopy NSDictionary *)desc;
- (bycopy NSDictionary *) sampleDescriptionAtIndex:(int)index;
- (void)setSampleDescription:(bycopy NSDictionary *)desc atIndex:(int)index;
- (void) convertTime		:	(double)time
	toSampleNumber		:	(out int *)samp
	startingTime		:	(out double *)stime
	duration		:	(out double *)duration;

- (void) convertSampleNumber	:	(int )sample
		toStartingTime	:	(out double *)stime
		duration	:	(out double *)duration;
- (bycopy NSDictionary *)userData;
- (void)setUserData:(bycopy NSDictionary *)userData;
- (BOOL)getNextInterestingTime: (NTInterestingTimeFlags) flags
		startingFrom		:	(double)startTime
		inDirection		:	(NTTimeDirection)direction
		interestingTime		:	(out double *)itime
		duration		:	(out double *) duration;

/*
 * Editing stuff
 */
- (BOOL)beginEdits;
- (void)endEdits;
- (void)writeSample:(NTSampleBuffer *)sample;
- (NTSampleBuffer *)inputBuffer;

- (BOOL)addSample		:	(bycopy in NTSampleBuffer *)sample
		startingTime:	(out double *)time;
- (BOOL)addSampleReference	:	(int)offset
	    sampleSize		:	(int)len
	    sampleDuration	:	(double)duration
	    sampleDescription	:	(bycopy in NSDictionary *)description
	    sampleCount		:	(int)nsamples
	    sampleFlags		:	(NTSampleFlags)flags
	    startingTime:	(out double *)time;
- (bycopy NTSampleBuffer *)sampleAtTime:(double)time;
- (bycopy NTSampleBuffer *)sampleAtTime:(double)time
		withMaxDuration	:(double)duration;
- (BOOL)getSampleReference	:	(out int *)offset
	    maxLength		:	(inout int *)len
	    durationPerSample	:	(out double *)duration
	    sampleDescription	:	(bycopy out NSDictionary**)description
	    maxSampleCount	:	(int *)nsamples
	    sampleFlags		:	(out NTSampleFlags *)flags
	    atTime		:	(double)time;

// Add a block of sample references from another media
- (BOOL)addSampleReferencesFromMedia:(id <NTMedia>)media
	    startingTime	:	(double)time
	    duration		:	(double)duration;
@end



/*
 * A class for representing a media.  Media hold sample and timing information.
 *
 */
@interface NTMedia: NSObject <NTMedia>
{
@private
	NTStatusCode	status;
	NSString *	type;		// Type of media
	int		playHints;
	int		quality;
	id <NTFileIO>	dataFile;
	NSDate *	creationDate;
	NSDate *	modificationDate;
	unsigned	sampleCount;
	
	void *		sampleList;

	NSMutableArray *dataReferenceList;
	NSMutableArray *sampleDescriptionList;
	NSDictionary *	userData;
	id		track;
	int		trackID;
	NSZone *	hotZone;
	
	double		tolerance;
	BOOL		hasNonSyncSamples;
}

@end

