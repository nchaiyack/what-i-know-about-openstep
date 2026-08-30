/*
 *  NTMediaController.h
 * 	Copyright 1994, NeXT Computer, Inc.
 *	
 *	A set of protocols defining expected API in components used to
 *	control hardware or digital media.
 *
 *	8 March 1994 mpaque Created.
 */
#import <Foundation/NSObject.h>
#import <Foundation/NSDictionary.h>
#import "NTMovie.h"
#import "NTProgressMonitor.h"


/*
 * The following optional API may be implemented by objects complying with
 * media control APIs specified in this file, for support of video input.
 */
@protocol NTVideoInputMediaControl <NSObject>
- (BOOL)canRecord;		/* Returns YES if recording can be started */
- (void)record;			/* The stop method terminates this. */

- (BOOL)canMonitorVideo; /* Returns YES if video can be monitored in NTView */
- (void)monitorVideo;		/* The stop method terminates this. */
@end

/*
 * The following optional API may be implemented by objects complying with
 * media control APIs specified in this file, for support of audio IO.
 */
@protocol NTAudioMediaControl <NSObject>
- (void)setSoundFocus:(BOOL)focus;/* tell controller that it has snd focus */
- (BOOL)soundFocus;		/* Current sound focus */
- (void)setMute:(BOOL)mute;	/* Mute, or audio enable/disable */
- (BOOL)isMuted;		/* Current audio state. */
@end

/*
 * The following optional API may be implemented by objects complying with
 * media control APIs which support cut and paste data operations.
 */
@protocol NTEditableMediaControl <NSObject>
- (NSData *) cutFromTime:(double)time duration:(double)dur;
- (void) deleteFromTime:(double)time duration:(double)dur;
- (NSData *) copyFromTime:(double)time duration:(double)dur;
- (void) pasteMovie:(NSData *)movieData atTime:(double)time;
- (void) undo;	/* undo/redo toggle */
@end

/*
 * Basic Media Control API, suitable for use by any sort of media player or
 * monitor.  For example, this API could be used to control one channel of a
 * simple video switcher to enable or disable a video feed.
 */
@protocol NTSimpleMediaControl <NSObject>
- (BOOL)setConfiguration:(bycopy NSDictionary *)configuration;
  /* Set a configuration.  The contents of the configuration dictionary
   * depend on the nature of the component. Returns NO if setup fails. */
- (bycopy NSDictionary *) configuration;
  /* report the current configuration.  This may not match the initial
   * configuration passed in through setConfiguration. */
- (void)run;		/* Start media playback */
- (BOOL)isRunning;	/* Media playback is in progress */
- (void)stop;		/* Stop, generating a still image if possible */
@end

/*
 * Seekable Media Control API, suitable for use by any sort of stored media
 * player.  This API could be used to control a simple laser disk or video tape
 * player, or an unindexed digital stored media such as an MPEG stream from
 * disk.
 */
@protocol NTSeekableMediaControl <NTSimpleMediaControl>
- (void)rewind;		/* Seek to beginning of media, displaying a still */
			/* frame (poster frame) if possible. */
- (void)stepForward;	/* Jog to the next displayable frame */
- (void)stepReverse;	/* Jog to the previous displayable frame */
- (void)fastForward;	/* Quickly forward through frames. Stop using stop */
- (void)fastReverse;	/* Quickly forward through frames. Stop using stop */
@end



/*
 * Precise Media Control API, suitable for use by a stored media player with
 * precise control over media position.  This API could be used to control a
 * high end laser disk or video tape deck, an ABEKAS video storage device, or
 * indexed digital stored media such as NEXTIME movies.
 */
typedef enum
{
	NTTimePosition,
	NTFramePosition
} NTPosition;

@protocol NTPreciseMediaControl <NTSeekableMediaControl>
- (void)seekToPosition:(double)pos ofType:(NTPosition)type;
  /* Select a position in the media by time or frame, and display image */
- (void)runToPosition:(double)pos ofType:(NTPosition)type;
  /* Run from the current position until the specified position */
- (double)currentPositionOfType:(NTPosition)type;
  /* Report current position by time in seconds or frame number */
- (NTSampleFlags)currentFrameFlags;
  /* Report the sample flags for the current video frame */
- (double)duration;	/* Duration of media in seconds, or -1.0 if unknown */
- (double)startTime;	/* Starting time media in seconds, -1.0 if unknown */
- (BOOL)canSeekContinuously;
  /* YES if we can seek through the media and display frames continuously */
@end

/*
 * A controller for samples stored in a file has additional capabilities.
 * Since the controller is embedded in the NEXTSTEP environment, it may be
 * able to take advantage of knowing when it has the user's focus to
 * optimize it's  behavior.
 * It can vend the NEXTIME representation of the movie, for use
 * in digital editing programs.
 * The NTEditableMediaControl API should be present, to support cut/paste
 * editing operations.
 * It should be able to provide digital sample recording services.
 * The NEXTSTEP environment's audio features are also available.
 * Since progress through a disk file is easy to monitor, we also
 * mandate support for progress monitors.
 */
@protocol NTFileBasedMediaControl	<NTPreciseMediaControl,
					NTEditableMediaControl,
					NTVideoInputMediaControl,
					NTAudioMediaControl,
					NTProgressController>
- (bycopy NSDictionary *)currentMovieParameters;
  /* Return a dictionary describing the filename, file type, and media encoding
   * found in the currently open file.  Returns nil if no file is currently
   * open.
   */
- (BOOL)openFileWithParameters:(bycopy NSDictionary *)param;
  /* Open an existing file/type as a movie.  The NTFilename and NTFileType
   * keys in param are used to specify the file to be opened.
   * Any old movie object in the controller is freed on success.
   * Returns NO on failure.
   */
- (BOOL)newFileWithParameters:(bycopy NSDictionary *)param;
  /* Creates a new movie file of type 'type'. The NTFilename and NTFileType
   * keys in param are used to specify the file to be opened.  Media keys may
   * also be supplied, indicating media to be configured in the new movie.
   * Any existing file may be destroyed.
   * Any old movie object in the controller is freed on success.
   * Returns NO on failure.
   */
- (BOOL)saveAndFlatten:(BOOL)squashItLikeABug;
- (BOOL)saveWithParameters:(bycopy NSDictionary *)parameters
	 andFlatten:(BOOL)squashItLikeABug;
  /* Save the file to disk, optionally flattening the file by resolving
   * external data references and removing unused samples and tracks.
   * The file name and type may be specified in parameters using the
   * NTFilename and NTFileType keys.
   */
- (id <NTMovie>)movie;
  /* Returns an NTMovie compliant object, or nil if the controller is not */
  /* associated with a digitally stored movie. */


/* Notification methods used to alert the controller when it has user focus. */
- (void)controllerDidBecomeKey;
- (void)controllerDidResignKey;

@end

