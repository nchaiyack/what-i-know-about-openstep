/*
 *	NTMovie.h
 * 	Copyright 1993, NeXT Computer, Inc.
 *	
 *	01Mar93 mpaque Created.
 *	06Jan94	mpaque	Revised and merged with protocol defs.
 */
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSData.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSArray.h>
#import "NTSampleBuffer.h"
#import "NTClock.h"
#import "movies.h"
#import "status.h"

/*
 * A protocol for messaging a movie.  The movie is composed of a number
 * of tracks and supplementary information. 
 *
 */
@protocol NTMovie <NSObject>
- (NSString *)movieFile;
- (void)setMovieFile:(NSString *)filename;
- (void)setModified:(BOOL)value;
- (BOOL)modified;
- (void)setPosterTime:(double)time;
- (double)posterTime;
- (void)setPreviewMode:(BOOL)preview;
- (BOOL)previewMode;
- (void)setPreviewTime:(double)time duration:(double)duration;
- (void)getPreviewTime:(out double*)time duration:(out double*)duration;
- (void) setStatus:(NTStatusCode)value;
- (NTStatusCode) status;
- (void) setPreferredRate:(double) rate;
- (double) preferredRate;
- (void) setPreferredVolume:(double) volume;
- (double) preferredVolume;
- (void)setActiveSegment:(double)time duration:(double)duration;
- (void)getActiveSegment:(out double *)time duration:(out double *)duration;
- (void) setPlayHints:(NTPlayHintFlags)hints;
- (NTPlayHintFlags)playHints;
- (void)setActive:(BOOL)value;
- (BOOL) active;
- (id) newTrack;
- (NSArray *)trackList;
- (void)setProgressDelegate:(id)delegate;
- (id)progressDelegate;
- (void)setCreationDate:(NSDate *)date;
- (NSDate *)creationDate;
- (void)setModificationDate:(NSDate *)date;
- (NSDate *)modificationDate;
- (BOOL) hasNonSyncSamples;
- (bycopy NSDictionary *)userData;
- (void)setUserData:(bycopy NSDictionary *)userData;
- (BOOL)getNextInterestingTime: (NTInterestingTimeFlags) flags
		startingFrom		:	(double)startTime
		inDirection		:	(NTTimeDirection)direction
		interestingTime		:	(out double *)itime
		duration		:	(out double *)duration;
- (int)nextTrackID;
- (void)setNextTrackID:(int)id;

/* Editing API */
- (id <NTMovie>) copyFromTime	:	(double)time
		duration	:	(double)duration
		activeTracksOnly:	(BOOL)activeOnly;

// Insert srcMovie tracks into existing tracks
- (BOOL) insertSegmentFrom:	(id <NTMovie>)srcMovie
			fromTime	:	(double)srcTime
			duration	:	(double)duration
			toTime		:	(double)dstTime;
// Add srcMovie tracks to movie, creating new tracks
- (BOOL) addSegmentFrom:	(id <NTMovie>)srcMovie
			fromTime	:	(double)srcTime
			duration	:	(double)duration
			toTime		:	(double)dstTime;
- (BOOL) insertEmptySegmentAtTime:(double)time andDuration:(double)duration;
- (BOOL) deleteSegmentFromTime:	(double)time
			duration	:	(double)dur;
- newEditState;
- (BOOL)setEditState: (id)state;

/* Pasteboard level editing API */
- (NSData *) cutFromTime:(double)time duration:(double)dur;
- (void) deleteFromTime:(double)time duration:(double)dur;
- (NSData *) copyFromTime:(double)time duration:(double)dur;
- (void) pasteMovie:(NSData *)movieData atTime:(double)time;
- (void) addMovie:(NSData *)movieData atTime:(double)time;
- (void) undo;	/* undo/redo toggle */
@end


/*
 * A class for representing a movie.  The movie is composed of a number
 * of tracks and supplementary information. 
 *
 */
@interface NTMovie: NSObject <NTMovie>
{
@private
	BOOL		modified;
	BOOL		active;
	BOOL		previewMode;
	int		playHints;
	int		status;
	int		nextTrackID;
	NSDate *	creationDate;
	NSDate *	modificationDate;
	NSMutableArray		*trackList;
	id		progressDelegate;
	id		lastEditState;
	NSMutableDictionary	*userData;
	NSString *	movieFile;
	double		posterTime;
	double		previewTime;
	double		previewDuration;
	double		preferredRate;
	double		preferredVolume;
	double		activeSegmentTime;
	double		activeSegmentDuration;
}

@end

