/*
 * LinesView.m, a small sample view for showing timer & userpaths.
 * Author: Ali T. Ozer, NeXT Computer, Inc.
 * Written March '89.
 * Updated for 2.0 Oct '90 by Jayson Adams to use UserPath.[hm].
 * Updated for 3.0 March '92 by Ali Ozer
 * Converted to OpenStep and updated for 4.2 Dec '96, Trey Matteson
 *
 * You may freely copy, distribute, and re-use the code in this example. NeXT
 * disclaims any warranty of any kind, expressed or implied, as to its fitness
 * for any particular purpose.
 *
 * LinesView draws a number of connected lines whose endpoints bounce around
 * randomly within the bounds of the view. The endpoints are stored in
 * an data array which is passed to PostScript as a user path. The
 * animation is performed by calling the "animate" method as often as
 * possible through a timer.
 */

#import <AppKit/AppKit.h>
#import <stdlib.h>                	// For rand(), srand().
#import "LinesView.h"

#define RANDINT(n) (rand() % (n+1))	// Return random integer 0..n
#define INITRAND   srand((unsigned)(fabs(fmod([NSDate timeIntervalSinceReferenceDate], (double)INT_MAX))))

#define XVEL corners[count].xVel  // Some slimy shortcuts, asuuming we're
#define YVEL corners[count].yVel  // using "count" as corner counter.
#define XLOC corners[count].xLoc
#define YLOC corners[count].yLoc

#define MAXVEL 12		// Maximum velocity of corners (pixels per frame)


@implementation LinesView

/* Create the view and related stuff...
*/
- (id)initWithFrame:(NSRect)rect {
    [super initWithFrame:rect];

    /* Allocating a gstate is an easy way to speed up lockFocus/unlockFocus, and, hence, drawing... */
    [self allocateGState];

    /* Initialize the random number generator... */
    INITRAND;

    /* Listen to interesting notifications */
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appWillHide:) name:NSApplicationWillHideNotification object:[NSApplication sharedApplication]];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowWillMiniaturize:) name:NSWindowWillMiniaturizeNotification object:nil];

    /* create a user path */
    userPath = [[UserPath allocWithZone:[self zone]] init];
    running = NO;

    return self;
}

- (void)dealloc {
    /* Stop the timer */
    if (running) {
	[linesTimer invalidate];
        [linesTimer release];
    }
    /* Remove self as observer */
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [userPath release];
    [super dealloc];
}

- (void)toggleRun:(id)sender {
    /* start or stop the timer (we're called by a two-state button) */
    if (running) {
        [linesTimer invalidate];
        [linesTimer release];
	running = NO;
    } else {
      /* Call the animation method as often as possible... */
	linesTimer = [[NSTimer scheduledTimerWithTimeInterval:0.0 target:self selector:@selector(animate:) userInfo:nil repeats:YES] retain];
	running = YES;
    } 
}

/* This method should be connected to a UI object capable of generating numbers. Note that to successfully detect the initial value of this slider as set through IB, we also declare an outlet named "numberOfCorners," and connect it to this UI object. Thus this method (setNumberOfCorners:) gets called when the .nib is being loaded, and we can detect the initial value of the slider.
*/
- (void)setNumberOfCorners:(id)sender {
    int	   count;
    int    oldNumCorners = numCorners;
    NSRect bounds = [self bounds];
    
    /* set the number of corners based on the "corners" slider */
    numCorners = MIN(MAXNUMCORNERS, MAX([sender intValue], MINNUMCORNERS));

    /* set the new corner starting positions & velocities */
    for (count = oldNumCorners; count < numCorners; count++) {
        XLOC = (int)(bounds.size.width / 4 + RANDINT((int)(bounds.size.width) / 2));
        YLOC = (int)(bounds.size.height / 4 + RANDINT((int)(bounds.size.height) / 2));
        XVEL = (RANDINT(1) ? 1 : -1) * (1 + RANDINT(MAXVEL/2));
        YVEL = (RANDINT(1) ? 1 : -1) * (1 + RANDINT(MAXVEL/2));
    }
    userPathNeedsUpdating = YES;
    [self setNeedsDisplay:YES]; 
}

/* drawRect: is supposed to regenerate the image of the whole view (or at least the specified rect); it does this by clearing the background then redrawing the lines on top...
*/
- (void)drawRect:(NSRect)rects {
    /* fill with the background color */
    [[self backgroundColor] set];
    NSRectFill ([self bounds]);
    /* draw the lines */
    [self drawUserPath:[self lineColor]];
}

/* Draws the lines by sending the user path down... If the user path is out of date, updates it by reloading all the endpoints in.
*/
- (void)drawUserPath:(NSColor *)color {
    /* Load all the endpoints into the user path object... */
    if (userPathNeedsUpdating) {
        unsigned count;
        /* "plot" the points */
        [userPath beginUserPath:NO];
        for (count = 0; count < numCorners; count++) {
            if (count) {
                [userPath lineto:XLOC :YLOC];
            } else {
                [userPath moveto:XLOC :YLOC];
            }
        }
        [userPath closepath];
        [userPath endUserPath:dps_ustroke];
        userPathNeedsUpdating = NO;
    }
    /* Draw the user path */
    [color set];
    PSsetlinewidth(0.0);
    [userPath sendUserPath];
}

/* Lines is an unusual animation program in that it runs untimed; that is, it runs as fast as the CPU will allow, and it doesn't care that on faster CPUs the animation will run faster. An animation or game application will usually want to limit to frame rate to a value (for instance, 30 frames a second), and on hardware not capable of that rate, end up doing the best it can. Such an application would also look at the time that actually passed between frames and increment the animation or game play accordingly.

Lines accomplishes its goal of running as fast as possible by creating a timer with a 0.0 second period. This means that the timer will fire and this method (animate) will be called as soon as possible.

Lines uses a buffered output window as a means to fake double-buffered animation. The current frame is drawn directly into the window. However, because the window is buffered, the drawing goes to the backing store, and not the screen.  Only when the frame is complete does Lines flush the window contents to the screen; this process is fast and provides a flicker-free update.  The next frame is then drawn into the backing store, and the cycle continues.

Note that this method does its own lock/unlockFocus, and flushWindow. Again, this is done for efficiency, and apps often don't need to go to those lengths to draw. This method could have called setNeedsDisplay:YES, but that would have caused drawRect: to be eventually called. drawRect: does more complete drawing (including erasing the background), and we don't really need that in this case. We know what to erase from the previous frame, so we do the erase and redraw ourselves with an explicit lock/unlockFocus.
*/
- (void)animate:(NSTimer *)timer {
    int count;
    NSRect bounds = [self bounds];
    
    [self lockFocus];

    /* Clear the previous frame from the backing store. Note that in some cases it might
       make more sense to just clear the whole view with an NSRectFill(). */
    [self drawUserPath:[self backgroundColor]];

    /* Move all the corners... */
    for (count = 0; count < numCorners; count++) {
        XLOC += XVEL;
        YLOC += YVEL;

	/* Detect collision with sides; if we collide, bounce back in some random fashion. */
        if (XLOC >= bounds.size.width) {
            XLOC = bounds.size.width-1;
            XVEL = -1-RANDINT(MAXVEL);
        } else if (XLOC < bounds.origin.x) {
            XLOC = bounds.origin.x;
            XVEL = 1+RANDINT(MAXVEL);
        }
        if (YLOC >= bounds.size.height) {
            YLOC = bounds.size.height-1;
            YVEL = -1-RANDINT(MAXVEL);
        } else if (YLOC < bounds.origin.y) {
            YLOC = bounds.origin.y;
            YVEL = 1+RANDINT(MAXVEL);
        }
    }
    userPathNeedsUpdating = YES;

    /* Draw the new frame */
    [self drawUserPath:[self lineColor]];

    /* And flush the backing store to the window */
    [[self window] flushWindow];
    [self unlockFocus]; 
}

- (NSColor *)lineColor {
    return [NSColor blackColor];
}

- (NSColor *)backgroundColor {
    return [NSColor whiteColor];
}

- (void)windowWillMiniaturize:(NSNotification *)notification {
    if (running && ([notification object] == [self window])) {
	[self toggleRun:nil];
    }
}

- (void)appWillHide:(NSNotification *)notification {
    if (running) {
	[self toggleRun:nil];
    }
}

@end
