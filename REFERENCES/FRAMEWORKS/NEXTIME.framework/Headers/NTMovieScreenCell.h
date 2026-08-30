/*
 * NTMovieScreenCell - subclass of NSActionCell that displays movies
 * 	target/action messages are sent and usually used to start/stop
 *		playback.  The state of a NTVideoCell indicates its playback
 *		state: 0 - not playing (stopped, paused), 1 - playing
 */

#import <AppKit/NSActionCell.h>
#import <AppKit/NSTextAttachment.h>

/* XXX: probably doesn't have to inherit from NSActionCell but something broke
 * with the controlView setting when it was a NSCell.
 */

typedef enum _NTVideoCellSizing
{
	NTMovieScreenCellNormalSizing = 0,				/* no resizing */
	NTMovieScreenCellPowerOfTwoSizing,			/* double or halve to fit (preserves aspect) */
	NTMovieScreenCellContinuousSizing, 				/* size to fit (does not preserve aspect) */
	NTMovieScreenCellMaintainAspectRatioSizing 	/* largest size that maintains aspect ratio */
} NTMovieScreenCellSizing;

@class NSWindow;
@class NSScreen;

@interface NTMovieScreenCell : NSActionCell <NSTextAttachmentCell>
{
@private
	id _attachment;
	NSRect _frame;		/* cached frame and clip frame used to keep the server in sync */
	NSRect _clippedFrame;
	NSRect _displayRect;		/* the actual rect we're displaying in (window coords) */
	NSSize _movieSize;		/* the "natural" size of the movie */
	id _displayContext;
	NTMovieScreenCellSizing _resizeMode; 	/* how do we resize */
	int _backingStoreType;		/* Window backing store type */
	NSWindow * _window;	/* cached window and screen used only to keep the server in sync */
	NSScreen * _screen;
	BOOL _gstateIsInvalid;
	void *	_private;
}
/*
 * Designated initializer.  This class overrides initImageCell: and
 * initTextCell: and invokes our init method.
 */
- (id)init;
/*
 * Set our type to NSNullCellType
 */

- (NTMovieScreenCellSizing)resizeMode;
- (void)setResizeMode:(NTMovieScreenCellSizing)mode;


- (void)setRepresentedObject:(id)anObject;
/*
 * Used to associate the reciever with an instance of the NTMediaDocument class.
 * The receiver registers the method 'mediaControllerSaid:' for all notifications 
 * issued by "anObject", retrieves the natural size of the movie represented by
 * "anObject" and sends the message 'suspendDrawing' to "anObject".
 */

/*** drawing changes ***/

- (void)updateFrame:(NSRect)frame;
/*
 * Check to see if 'frame' is the same as the frame
 * we last sent to the NTMediaController.  If it isn't
 * transmit the new information.  Override this to implement
 * hardware driven display updates, such as refreshing a display from
 * an MPEG card.
 */

- (void)setNewView:(NSView *)aView;
/*
 * Called when we are asked to draw in a new NSView.
 * Transmit the change to our NTSimpleMediaControl and
 * Register to receive gState invalidations for the new view.
 * Passing aView of nil decouples the cell from any view, suspending
 * video display.
 */

/*** event processing methods ***/

- (BOOL)wantsToTrackMouse;
/*
 * Returns 'YES'
 */

- (BOOL)trackMouse:(NSEvent *)theEvent inRect:(NSRect)cellFrame
	ofView:(NSView *)controlView untilMouseUp:(BOOL)flag;

/*** text attachment support ***/

- (void)setAttachment:(NSTextAttachment *)anObject;
- (NSTextAttachment *)attachment;

@end


