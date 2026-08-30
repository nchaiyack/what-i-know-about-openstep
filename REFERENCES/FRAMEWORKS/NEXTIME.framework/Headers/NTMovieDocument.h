/*
 *  NTMovieDocument.h
 * 	Copyright 1995, NeXT Computer, Inc.
 *	
 *
 *	A class to manage a media document and the associated NEXTIME Server
 *	connection.
 *
 *	21 April 1995 mpaque Created.
 */
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <AppKit/NSPasteboard.h>
#import "NTMovie.h"
#import "NTMediaController.h"

/* NSNotification names */
extern NSString *NTMovieDocumentWillStartPlaybackNotification;
extern NSString *NTMovieDocumentDidStopPlaybackNotification;
extern NSString *NTMovieDocumentDidPausePlaybackNotification;
extern NSString *NTMovieDocumentDidSetPositionNotification;
extern NSString *NTMovieDocumentDidOpenMovieNotification;
extern NSString *NTMovieDocumentDidRenameMovieNotification;
extern NSString *NTMovieDocumentDidCloseMovieNotification;
extern NSString *NTMovieDocumentDidMakeSelectionNotification;
extern NSString *NTMovieDocumentDidShowPosterFrameNotification;
extern NSString *NTMovieDocumentWillStartFastForwardNotification;
extern NSString *NTMovieDocumentWillStartFastReverseNotification;
extern NSString *NTMovieDocumentDidEditMovieNotification;
extern NSString *NTMovieDocumentWillDrawNotification;
extern NSString *NTMovieDocumentDidDrawNotification;
extern NSString *NTMovieDocumentDidEncounterErrorNotification;

/* Pasteboard types */
extern NSString *NTMoviePboardType;

typedef enum
{
	NTMovieStateStopped,
	NTMovieStatePaused,
	NTMovieStatePlaying,
	NTMovieStateFastForward,
	NTMovieStateFastReverse
} NTMovieState;

/*
 * Protocols to be implemented by a media document object.
 */
@protocol NTMovieDocument <NSObject>
- (double)currentPosition;
- (double)maxPosition;
- (void)setCurrentPosition:(double)position;
- (double)minPosition;
- (BOOL)pause:(id)sender;
- (BOOL)play:(id)sender;
- (BOOL)playLooped:(id)sender;
- (BOOL)reset:(id)sender;
@end
 
@protocol NTExtendedMovieDocument <NTMovieDocument>
- (BOOL)stepForward:(id)sender;
- (BOOL)stepReverse:(id)sender;
- (BOOL)fastForward:(id)sender;
- (BOOL)fastReverse:(id)sender;
@end

/*
 * A movie document which will be displayed in an OPENSTEP window
 * must also implement the following:
 */
@protocol NTMovieDrawing
- (BOOL)isDrawingSuspended;
- (void)suspendDrawing;
- (void)resumeDrawing;
- (void)display;
- (void)setViewID:(int)_viewID;
@end

 
@interface NTMovieDocument:NSObject <NTExtendedMovieDocument, NTMovieDrawing, NTProgressMonitor, NSCoding>
{
@private
	unsigned long			retainCount;
	NSString *			fileName;
	NSString *			fileType;
	id <NTFileBasedMediaControl>	controller;
	id <NTMovie>			movie;
	NSMutableDictionary *		userInfo;
	NTMovieState			state;
	int				viewID;
	double				currentPosition;
	double				maxPosition;
	double				minPosition;
	double				selectionStartPosition;
	double				selectionEndPosition;
	BOOL				isSuspended;
	BOOL				showPosterFrame;
	BOOL				nullSelection;
	BOOL				isTemporaryFile;
	BOOL				playLoopedMode;
	void *				_private;
}

+ (BOOL)canInitWithPasteboard:(NSPasteboard *)pasteboard;
/* Returns YES if the receiver can create a representation from pasteboard; otherwise, returns NO. */

+ (NSArray *)readableMovieFileTypes;
/* Returns an array of supported media data file types which can be read. */

+ (NSArray *)writableMovieFileTypes;
/* Returns an array of supported  media data file types which can be written. */

+ (NSArray *)moviePasteboardTypes;
/* Returns an array of supported pasteboard types. */


- (id)initByReferencingFile:(NSString *)filename;
/* Initializes the new NTMediaDocument from the data in filename. The file is assumed to persist and will be reread later during operations on the media.  Returns nil if the file cannot be opened. */

- (id)initWithPasteboard:(NSPasteboard *)pasteboard;
/* Initializes the new NTMediaDocument with the data in pasteboard.  Returns nil if the pasteboard data is corrupt or of an inappropriate type.  A temporary media file name is automatically created. */

- (id)init;
/* Initializes the new empty NTMediaDocument. A temporary media file name is automatically created. */

- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;
/* Writes the media contents of the receiver to filename. If useAuxiliaryFile is YES, the data is written to a backup file and then, assuming no errors occur, the backup file is renamed to the intended file name.   The suffix of path is used to determine the proper file format, and should be a suffix found in the NSArray returned by the writableMediaFileTypes class method.  Returns NO if the file cannot be saved, or the suffix of path is invalid.
	
If path matches the current filename and useAuxiliaryFile is NO, then the current file is quickly updated.  If path does not match the current media file, or useAuxiliaryFile is YES, then a more expensive save and flatten operation is performed.  Once the write operation is completed, the name of the current media file as returned by the filename method is updated to path. */


- (void)display;
/* Displays or redraws the current video frame.  The video display cell associated with the current NEXTIME display context must be configured.  This message is typically sent from the cell's drawInteriorWithFrame:inView: method. */

- (BOOL)isDrawingSuspended;
/* Returns a boolean indicating if drawing is currently suspended. */

- (void)suspendDrawing;
/* Temporarily suspends video output, until a resumeDrawing message is received.  This method is typically used when resizing or scrolling of the video display cell is about to occur. */

- (void)resumeDrawing;
/* Resumes video output if appropriate.  This method is typically used on completion of resizing or scrolling of the video display cell. */

- (void)setViewID:(int)viewID;
/* Set the view ID used to register the NTVideoCell with the NEXTIME server.  The value used must be non-zero and unique for each video cell within the application, and is typically the address of the object cast as an integer.  This message should be sent to the NTMediaDocument as soon as the NTVideoCell is connected to the NEXTIME display context. */

- (int)viewID;
/* Return the view ID used to register the NTVideoCell with the NEXTIME server.*/

- (double)currentPosition;
/* Returns the current position of the document within the media. */

- (double)maxPosition;
/* Returns the maximum possible position of the document within the media. */

- (void)setCurrentPosition:(double)position;
/* Tells the NTMediaDocument that the user has adjusted the position slider.  If playing, playback is stopped, and a NTMediaDocumentStopPlaybackNotification is posted.   After updating the position, a NTMediaDocumentSetPositionNotification is posted to update observers with the current position. */

- (double)minPosition;
/* Returns the minimum possible position of the document within the media. */

- (BOOL)pause:(id)sender;
/* Notify the NTMediaDocument that the pause button has been pressed.  A return value of NO tells the sender to disregard the press of the pause button.   If playing, a NTMediaDocumentStopPlaybackNotification is posted.   (Software playback systems do not discriminate between a stopped and paused state.  Hardware systems, on the other hand, treat these very differently, and may move from a paused to a stopped state without external intervention after a few minutes.  Software media control systems should be aware of this behavior if they intend to control either software or hardware players.  A hardware media controller should post a NTMediaDocumentStopPlaybackNotification when the hardware actually moves to a stopped state.) */

- (BOOL)play:(id)sender;
/* Notify the NTMediaDocument that the play button has been pressed.  A return value of NO tells the sender to disregard the press of the play button.  If playing in fast forward or reverse, playback is stopped, and a NTMediaDocumentStopPlaybackNotification is posted.  Posts a NTMediaDocumentStartPlaybackNotification before beginning playback.  While playing, a NTMediaDocumentSetPositionNotification is posted periodically to indicate the current position in the movie.  Observers may use this to update their state and position displays. */

- (BOOL)reset:(id)sender;
/* Notify the NTMediaDocument that the reset/stop button has been pressed.  A return value of NO tells the sender to disregard the press of the reset/stop button.  If playing, playback is stopped and a NTMediaDocumentStopPlaybackNotification is posted.  The media position is reset to the start of the media, and a  NTMediaDocumentSetPositionNotification is posted.  Finally, the media poster frame is displayed, and a NTMediaDocumentShowPosterFrameNotification is posted. */


- (BOOL)stepForward:(id)sender;
/* Tells the NTMediaDocument to step forward to display the next video frame.  May return NO, indicating a failure, typically due to already being positioned at the last video frame.   If playing, playback is stopped, and a NTMediaDocumentStopPlaybackNotification is posted.   After updating the position, a NTMediaDocumentSetPositionNotification is posted. */

- (BOOL)stepReverse:(id)sender;
/* Tells the NTMediaDocument to step backward to display the previous video frame.  May return NO, indicating a failure, typically due to already being positioned at the first video frame.   If playing, playback is stopped, and a NTMediaDocumentStopPlaybackNotification is posted.   After updating the position, a NTMediaDocumentSetPositionNotification is posted. */

- (BOOL)fastForward:(id)sender;
/* Tells the NTMediaDocument to start fast forward playback.  May return NO, indicating a failure.  If performing normal playback, playback is stopped, and a NTMediaDocumentStopPlaybackNotification is posted.  A NTMediaDocumentStartFastForwardNotification is posted before beginning fast forward playback.  While playing in fast forward, a NTMediaDocumentSetPositionNotification is posted periodically to indicate the current position in the movie.  Observers may use this to update their state and position displays.  Sound is muted during fast forward operation. */

- (BOOL)fastReverse:(id)sender;
/* Tells the NTMediaDocument to start fast reverse playback.  May return NO, indicating a failure.  If performing normal playback, playback is stopped, and a NTMediaDocumentStopPlaybackNotification is posted.  A NTMediaDocumentStartFastReverseNotification is posted before beginning fast reverse playback.  While playing in fast reverse, a NTMediaDocumentSetPositionNotification is posted periodically to indicate the current position in the movie.  Observers may use this to update their state and position displays.  Sound is muted during fast reverse operation. */


- (void)selectNull;
/* Deselects the current selection.  A NTMediaDocumentMakeSelectionNotification is posted. */

- (void)setSelectionStartingPosition:(double)start endingPosition:(double)end;
/* Selects media from position start through end.  The selection will be adjusted to start at the first key frame at or prior to start.  Once the adjusted selection is determined, a NTMediaDocumentMakeSelectionNotification is posted. */

- (double)selectionStartingPosition;
/* Returns the current starting position of the selection within the media. */

- (double)selectionEndingPosition;
/* Returns the current ending position of the selection within the media. */

- (void)copy:(id)sender;
/* Copies the selected media to the pasteboard. */

- (void)cut:(id)sender;
/* Deletes the selected media and copies it to the pasteboard. This method posts the notification NTMediaDocumentMediaDidChangeNotification with the receiving object to the default notification center. */

- (void)delete:(id)sender;
/* Deletes the selected media. This method posts the notification NTMediaDocumentMediaDidChangeNotification with the receiving object to the default notification center. */

- (void)paste:(id)sender;
/* Replaces the selected media with the contents of the pasteboard.  This method posts the notification NTMediaDocumentMediaDidChangeNotification with the receiving object to the default notification center. */


- (NTMovieState)documentState;
/* Returns the current state of the NTMediaDocument. */

- (NSDictionary *)movieParameters;
/* Returns the dictionary containing descriptive information on the current movie. */

- (NSString *)filename;
/* Returns the name of the current media data file. */


- (id <NTFileBasedMediaControl>)controllerProxy;
/* Returns the proxy to the NTFileBasedMediaControl implementation in the NEXTIME server used by this NTMediaDocument instance. */

- (id <NTMovie>)movieProxy;
/* Returns the proxy to the NTMovie implementation in the NEXTIME server used by this NTMediaDocument instance. */

- (int)frameForPosition:(double)position;
/* Returns the video frame number for position seconds from the start of the movie, or -1 if there is no valid video frame for position.  The programmer should be aware that in NEXTIME, there is not a 1:1 mapping between time and frame numbers.  That is, the NEXTIME architecture does not assume a constant frame rate over time, nor does it assume that frames are ordered linearly over time. */

@end

