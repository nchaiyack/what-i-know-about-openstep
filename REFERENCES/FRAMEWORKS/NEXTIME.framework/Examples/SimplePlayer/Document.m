
#import "Document.h"
#import <AppKit/NSApplication.h>

@implementation Document

- initByReferencingFile:(NSString *)file
{
	NSRect content = {{0., 0.}, {320., 240.}};
        NSRect frame;
	
	self = [super init];
	if ( self == nil )
		return nil;
		
	// Create a window and DocumentView, set the window's contentView
	// to be our document view, set the title and delegate.
	docView = [[DocumentView alloc] initWithFrame:content];
	if ( [docView setMovieFile:file] == NO )
	{
		[docView release];
		[self dealloc];
		return nil;
	}
	myWindow = [[NSWindow alloc] initWithContentRect:[docView frame]
			styleMask: NSResizableWindowMask
				| NSClosableWindowMask
				| NSMiniaturizableWindowMask
			backing:NSBackingStoreBuffered
			defer:	YES];
			
	[myWindow setContentView:docView];

        // Window is now set up to display a movie frame at 'normal' size.
        // Set this to also be the minimum size, so the user doesn't get
        // exposed to weird clipping effects if the window is resized too
        // small, and to provide an obvious way to restore a movie back to
        // 'normal' size and scale.
        frame = [myWindow frame];
        [myWindow setMinSize:frame.size];

        // Allow our content view to be fully resizable
	[docView setAutoresizingMask:
			(NSViewWidthSizable | NSViewHeightSizable)];

        // We will act as the delegate for the document
	[myWindow setDelegate:self];

        // Title based on the file name
	[myWindow setTitleWithRepresentedFilename:file];
	return self;
}

- (void) dealloc
{
	[docView release];
	[super dealloc];
}

- (void)show
{
	NSPoint position;
	NSWindow *mainWin;
	
	// Cascade from current window, if any.
	mainWin = [[NSApplication sharedApplication] mainWindow];
	if ( mainWin == nil )
	{
		position.x = position.y = 80.0;
	}
	else
	{
		position.x = position.y = 0.0;
		position = [mainWin cascadeTopLeftFromPoint:position];
	}
	[myWindow cascadeTopLeftFromPoint:position];
	[myWindow makeKeyAndOrderFront:self];
}

/* Window delegate methods */
- (void)windowWillClose:(NSNotification *)note
{
	[myWindow setDelegate:nil];
        // Our window is closing. Time for us to go, too.
	[self release];
}

@end
