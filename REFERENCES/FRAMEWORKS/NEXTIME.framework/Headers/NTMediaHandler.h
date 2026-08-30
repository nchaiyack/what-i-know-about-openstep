/*
 *  NTMediaHandler.h
 * 	Copyright 1994, NeXT Computer, Inc.
 *	
 *	A set of protocols defining expected API in components used to
 *	manage media sample streams.
 *
 *	27 Jan 1994 mpaque Created.
 */
#import <Foundation/NSObject.h>
#import "NTSampleProcessor.h"
#import "NTMediaController.h"
#import "NTTrack.h"
#import "NTMovie.h"
#import "NTClock.h"

/*
 * A generic media handler provides the interface between stored samples
 * and a serialized stream of timestamped samples .
 * The sample store, or track, is explicitly specified.
 * The source or destination is established as part of the configuration
 * process.
 */
@protocol NTMediaHandler <NTConfiguration>
- (void)setTrack:(id <NTTrack>)track;
- (id <NTTrack>)track;
- (void)setMasterClock:(id <NTClock>)clock;
- (id <NTClock>)masterClock;
- (void)writeSample: (NTSampleBuffer *) sample; 
@end

/*
 * A playback media handler is driven by clock events to fetch samples from the
 * track store and pass them into the sample processing pipeline.  It receives
 * clock events as a delegate of it's clock, which is in turn slaved to the
 * session master clock.
 *
 * Some basic behavior of a NTPlaybackMediaHandler is defined for any media
 * type.  All media handlers will start playing samples on a
 * 'clockWillStart:' message, and stop on a 'clockDidStop:' message.
 * A 'clockDidSetCurrentTime:' or 'clockDidChangeDirection:'
 * message should be treated as indicating a discontinuity, and the
 * handler should discard prerolled or buffered data from the old time value.
 *
 * Handlers which process imaging samples (video, PS, RIB, etc.) must also
 * correctly update the display on receipt of 'clockDidSetCurrentTime:', even
 * if the clock is stopped.  This is done to provide visual feedback to the
 * user when the "current time" slider is manipulated.
 * 
 * Preroll, or cueing, is done in the 'clockWillStart:' method.
 * 'clockWillStart:' is sent before the timer is initialized.
 * The timer won't start running until all 'clockWillStart:'
 * messages have been delivered and returned by all slaves of
 * the master clock.
 *
 * The playback media handler can run asynchronously.  Rather than relying
 * on the clockDidStop: message to halt it cleanly at the end of a performance,
 * we provide API to set the stopping time explicitly.  This way, delays in
 * propagating clockDidStop: on completion of a performance will not affect
 * the actual stopping time of individual handlers.  clockDidStop: is still
 * needed to support stopping from the GUI.
 */
@protocol NTPlaybackMediaHandler <NTMediaHandler, NTClockDelegate>
- (void)setStopTime:(double)stop;
- (double)stopTime;
@end
/*
 * The Video Playback Media Handler has one additional piece of API, used
 * to display still frames independent of the current clock time.  This is
 * used by the NTPlaybackSession to display poster frames.
 */
@protocol NTVideoPlaybackMediaHandler <NTPlaybackMediaHandler>
- (void)showFrameForTime: (double) aTime;
@end

/*
 * The Sound Playback Media Handler has additional  API, used
 * to control the sound focus, mute, and set volume.
 */
@protocol NTSoundPlaybackMediaHandler <NTPlaybackMediaHandler,
					NTAudioMediaControl>
@end

/*
 * The NTPlaybackMovieHandler is a specialized component that fans out control
 * messages and movie samples to playback media handlers.  It reads all samples
 * due at a particular time from the movie file, and sends the samples to the
 * media handlers for further processing.
 * 
 * This object creates and owns the media handler objects.
 */
@protocol NTPlaybackMovieHandler <NTConfiguration, NTAudioMediaControl>
- (void)setMovie:(id <NTMovie>)movie;
- (id <NTMovie>)movie;
- (void)movieDidChange:sender;		// Notify that the movie was modified
- (void)setMasterClock:(id <NTClock>)clock;
- (id <NTClock>)masterClock;
- (void)setStopTime:(double)stop;
- (double)stopTime;
- (void)showFrameForTime: (double) aTime;
- (void)setPrerollDuration:(double)preroll;
- (double)prerollDuration;
@end
