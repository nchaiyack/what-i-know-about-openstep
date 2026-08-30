/*
 *	NTTrack.h
 * 	Copyright 1993, NeXT Computer, Inc.
 *	
 *	01Mar93 mpaque Created.
 *	06Jan94	mpaque	Revised and merged with protocol defs.
 */
#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSData.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSDictionary.h>
#import "NTSampleBuffer.h"
#import "movies.h"
#import "status.h"
#import "NTMedia.h"
#import "NTClock.h"

/*
 * A protocol for messaging a track.  The track is composed of a media
 * and supplementary information. 
 *
 */
@protocol NTTrack <NSObject>
- (void)setUsage:(NTUsage) use;
- (NTUsage) usage;
- (void) setStatus:(NTStatusCode)value;
- (NTStatusCode) status;
- (void)setTrackID:(int)id;
- (int)trackID;
- (void)setEnabled:(BOOL)flag;
- (BOOL)isEnabled;
- (void)setMedia:(id <NTMedia>)media;
- (id <NTMedia>)media;
- (void)setMovie:(id)mov;
- (id)movie;
- (void)setLayer:(int)layer;
- (int) layer;
- (void) setMatrix:(NTMatrix)newMatrix;
- (void) getMatrix:(out NTMatrix *)matrixp;
- (void)setSize:(NSSize)newSize;
- (NSSize)size;
- (void) setVolume:(double) volume;
- (double) volume;
- (BOOL)setLanguage:(NSString *)language;
- (NSString *)language;
- (void)setDuration:(double)duration;
- (double)duration;
- (void)setOffset:(double) offset;
- (double)offset;
- (void)convertToMediaTime:(inout double *) time;
- (void)convertFromMediaTime:(inout double *) time;
- (void)addAlternate:(id <NTTrack>)alt;
- (void)removeAlternate:(id <NTTrack>)alt;
- (NSMutableArray *)alternateList;
- (int)dataSizeForTime:(double)time duration:(double)duration;
- (int)sampleCount;
- (void)setCreationDate:(NSDate *)date;
- (NSDate *)creationDate;
- (void)setModificationDate:(NSDate *)date;
- (NSDate *)modificationDate;
- (BOOL) hasNonSyncSamples;
- (bycopy NSDictionary *)userData;
- (void)setUserData:(bycopy NSDictionary *)data;

- (BOOL)getNextInterestingTime: (NTInterestingTimeFlags) flags
		startingFrom		:	(double)startTime
		inDirection		:	(NTTimeDirection)direction
		interestingTime		:	(out double *)itimep
		duration		:	(out double *) durationp;

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

- (BOOL) insertSegmentFrom:	(id <NTTrack>)srcTrack
			fromTime	:	(double)srcTime
			duration	:	(double)duration
			toTime		:	(double)dstTime;
- (BOOL) insertEmptySegmentAtTime:(double)time andDuration:(double)duration;
- (BOOL) deleteSegmentFromTime:	(double)trackTime
			duration	:	(double)dur;
- (BOOL) insertMediaFromTime:	(double)mediaTime
			duration	:	(double)mediaDuration
			toTime		:	(double)trackTime;
- (BOOL) adjustSegmentScale	:	(double)trackTime
			oldDuration		:	(double)oldDur
			newDuration		:	(double)newDur;
- (void)getScale:(out double *)scale atTime:(double)time;
- (void) copySettingsFrom:(id <NTTrack>)otherTrack;
- newEditState;
- (BOOL)setEditState: (id)state;

/*
 * Edit List API, used between the file I/O module and the track.
 * These methods are not intended for general use.  Invoking these methods
 * outside of archiving or unarchiving operations may result in fatal errors
 * and possible loss of data.
 */
- (void)clearEditList;		// Destroy the current edit list
/*
 * The following methods are used when archiving a movie to a file.
 * They may also be handy when initializing editing GUI. These are safe to
 * call at any time.
 */
- (int)currentEditCount;	// Number of edits currently in list
- (BOOL)getEditAtIndex	:	(int)index
	duration	:	(out double *)durp
	atMediaTime	:	(out double *)mTimep
	rate		:	(out double *)mRatep;

@end


/*
 * A class for representing a track.  The track is composed of a media
 * and supplementary information. 
 *
 */
@interface NTTrack: NSObject <NTTrack>
{
@private
	BOOL		isEnabled;
	
	int		layer;
	int		trackID;
	int		saveCnt;
	NTUsage		usage;
	NTStatusCode	status;
	NSString *	language;
	NSDate *	creationDate;
	NSDate *	modificationDate;
	NSZone *	hotZone;
	
	void		*editList;

	id		movie;
	id <NTMedia>	media;
	id		alternate;
	NSDictionary	*userData;

	NSSize		size;
	double		volume;
	NTMatrix	matrix;
}
- init;
- (void)dealloc;
@end

