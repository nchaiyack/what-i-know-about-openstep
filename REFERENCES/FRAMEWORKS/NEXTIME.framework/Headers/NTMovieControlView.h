/*
 *  NTMovieController.h
 * 	Copyright 1995, NeXT Computer, Inc.
 *	
 *
 *	A class to provide a simple set of UI controls for media documents.
 *
 *	25 April 1995 mpaque Created.
 */
#import <AppKit/NSView.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import "NTMovieDocument.h"

extern NSString * NTMovieControlViewIllegalMovieDocumentException;

@class NSButton;
@class NSScroller;

@interface NTMovieControlView:NSView <NSCoding>
{
@private
	id <NTMovieDocument>		document;
	NSButton *			playButton;
	NSButton *			soundButton;
	id				positionScroller;
        double				minPosition;
        double				maxPosition;
	NTMovieState			state;
	void *				_private;
}

- (id)initWithFrame:(NSRect)frame;


- (id <NTMovieDocument>)movieDocument;
/* Returns the NTControlView's media document. */

- (void)setMovieDocument:(id <NTMovieDocument>)anObject;
/* Sets the NTControlView's media document to anObject. Raises NTControlViewIllegalMediaControllerException if the media document specified by anObject doesn't conform to the NTMediaDocument protocol.  When archived, NTControlView will conditionally archive anObject. Settings for the slider range and the current GUI state are picked up from anObject. */


- (double)currentPosition;
/* Returns the current slider position. */

- (double)maxPosition;
/* Returns the maximum permitted slider position. */

- (double)minPosition;
/* Returns the minimum permitted slider position. */

- (void)setCurrentPosition:(double)position;
/* Set the current slider position.  The position is clipped to be between the minimum and maximum positions.  If a media document is associated with the NTControlView, a setPosition: message is sent to the media document. */


- (void)setState:(NTMovieState)state;
/* Set the current state of the NTControlView.  The unsupported NTMediaStateFastForward and NTMediaStateFastReverse are mapped into NTMediaStatePlaying.  State changes made through this method propagate to the media document through the document's play:, pause:, and reset: methods.  The user interface is updated to reflect the new state. */

- (NTMovieState)state;
/* Report the current state of the NTControlView. */

@end
