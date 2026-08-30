/*
 * LinesView.h, a small sample view demonstrating use of timers and userpaths.
 */

#import <AppKit/NSView.h>
#import "UserPath.h"

#define MINNUMCORNERS 2
#define MAXNUMCORNERS 20

@interface LinesView : NSView {
    BOOL running;			// Whether we are animating or not.
    BOOL userPathNeedsUpdating;		// Whether the userPath object has uptodate points
    NSTimer *linesTimer;
    struct cornerStruct {
	int xLoc, yLoc;
	int xVel, yVel;
    } corners[MAXNUMCORNERS];		// Corners and velocities for our polygon
    int numCorners;			// Number of corners we actually have
    UserPath *userPath;
}

- (id)initWithFrame:(NSRect)rect;
- (void)dealloc;
- (void)toggleRun:sender;
- (void)setNumberOfCorners:sender;
- (void)drawUserPath:(NSColor *)color;
- (NSColor *)lineColor;
- (NSColor *)backgroundColor;

@end
