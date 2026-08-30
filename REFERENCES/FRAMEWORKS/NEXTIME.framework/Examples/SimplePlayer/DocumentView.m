/*
 *  DocumentView.m
 *	
 */
#import "DocumentView.h"
#import "Controller.h"
#import "SimplePlayer_Globals.h"
#import <NEXTIME/NTMovieScreenCell.h>

@implementation DocumentView

#define CONTROL_Y_MARGIN	(1.0)
#define CONTROL_Y_OFFSET	(0.0)

- initWithFrame:(NSRect)frameRect
{
	NSRect frame;
        
	self = [super initWithFrame:(NSRect)frameRect];
	if ( self == nil )
		return nil;

        
	// Get a NTControlView.  The control view will bump the height up to
	// the minimum it needs.
	frame.size.width = frameRect.size.width;
	frame.size.height = 0.0;	// Adjusted by control
	frame.origin.x = 0.0;
        frame.origin.y = CONTROL_Y_OFFSET;
	control = [[NTMovieControlView alloc] initWithFrame:frame];
	[control setAutoresizingMask:NSViewWidthSizable];
	[self addSubview:control];
	
	// Get a NTVideoWell, framed above the NTControlView.
	frame = [control frame];		// Get the control size.
	frame.origin.y += (frame.size.height + CONTROL_Y_MARGIN);
	frame.size.height = frameRect.size.height - frame.origin.y;
	if ( frame.size.height < 0.0 )
		frame.size.height = 0.0;
	frame.origin.x = 0.0;
	frame.size.width = frameRect.size.width;

        videoWell = [[NTMovieScreen alloc] initWithFrame:frame];
	[videoWell setAutoresizingMask:
			(NSViewWidthSizable | NSViewHeightSizable)];
        // Set sizing policy via defaults database
	[[videoWell cell] setResizeMode:[Controller sizingPolicy]];
	[[videoWell cell] setBezeled:NO];
	[[videoWell cell] setBordered:NO];
	[self addSubview:videoWell];

        // Listen for changes in the defaults database regarding sizing
        // policy.
        [[NSNotificationCenter defaultCenter]
		addObserver:self
        	selector:@selector(_resizePolicyChanged:)
        	name:NTResizePolicyChangeNotification
        	object:nil];
        
        return self;
}

- (void)dealloc
{
	[control release];
	[videoWell release];
	[super dealloc];
}

- (BOOL)setMovieFile:(NSString *)file
{
	NSRect frame;
	NSRect controlFrame;
        
	if ( [videoWell setMovieFile:file] == NO )
		return NO;

        // The videoWell cell is configured for the 'normal' size
        // of the movie.  Save this for use in resizing the movie.
        frame.origin.x = frame.origin.y = 0.0;
        frame.size = [[videoWell cell] cellSize];
        frame = [[videoWell cell] drawingRectForBounds:frame];
        movieSize = frame.size;
        
        // Hook our control to the new media document created by the
        // NTVideoWell and represented by the well's NTVideoCell.
        // This will raise if the represented object doesn't conform to
        // the NTMediaDocument protocol!
        [control setMovieDocument:[[videoWell cell] representedObject]];

        // Adjust the videoWell to just hold the movie at normal size.
	[videoWell sizeToFit];

        // Adjust the control to match the videoWell width
	frame = [videoWell frame];
	controlFrame = [control frame];
	controlFrame.size.width = frame.size.width;
	[control setFrameSize:controlFrame.size];

        // Set a frame size just big enough to hold the videoWell and
        // the control.
	frame.size.height += (controlFrame.size.height + CONTROL_Y_MARGIN);

        // Disable subview resize, and wrap this view
        // snugly about our subviews.
        [self setAutoresizesSubviews:NO];
	[self setFrameSize:frame.size];
        
        // Restore normal resize behavior for our view.
        [self setAutoresizesSubviews:YES];

	return YES;
}

- (id <NTMovieDocument>)document
{
	return [[videoWell cell] representedObject];
}

- (NTMovieControlView *)control
{
	return control;
}

- (NTMovieScreen *)videoWell
{
	return videoWell;
}

// Put a little black stripe over the NTControlView
- (void)drawRect:(NSRect)rect
{
	NSRect controlFrame;
	NSRect marginFrame;

        controlFrame = [control frame];
        marginFrame.origin.x = controlFrame.origin.x;
        marginFrame.size.width = controlFrame.size.width;
        marginFrame.origin.y =
        	controlFrame.origin.y + controlFrame.size.height;
        marginFrame.size.height = CONTROL_Y_MARGIN;

        // Fill in the gap above the NSControlView
	PSsetgray(NSBlack);
	NSRectFill(marginFrame);

        // And the gap below the NSControlView
        marginFrame.origin.y = 0.0;
        marginFrame.size.height = CONTROL_Y_OFFSET;
	NSRectFill(marginFrame);
}

// Change in resize policy.
- (void)_resizePolicyChanged:(NSNotification *)note
{
	[[videoWell cell] setResizeMode:[Controller sizingPolicy]];
}

- (NSSize)normalSize
{
	NSSize size;
	NSRect frame;
        NSRect controlFrame;

        frame.origin.x = frame.origin.y = 0.0;
        frame.size = movieSize;
        size = [[videoWell cell] cellSizeForBounds:frame];

        // Size is now appropriate for the videoWell.
        // Add in the controlView.
	controlFrame = [control frame];
	size.height +=	  CONTROL_Y_OFFSET
        		+ controlFrame.size.height
        		+ CONTROL_Y_MARGIN;
	return size;
}

- (NSSize)doubleSize
{
	NSSize size;
	NSRect frame;
        NSRect controlFrame;

        frame.origin.x = frame.origin.y = 0.0;
        frame.size = movieSize;
        frame.size.width *= 2.0;
        frame.size.height *= 2.0;
        size = [[videoWell cell] cellSizeForBounds:frame];

        // Size is now appropriate for the videoWell.
        // Add in the controlView.
	controlFrame = [control frame];
	size.height +=	  CONTROL_Y_OFFSET
        		+ controlFrame.size.height
        		+ CONTROL_Y_MARGIN;
	return size;
}

@end
