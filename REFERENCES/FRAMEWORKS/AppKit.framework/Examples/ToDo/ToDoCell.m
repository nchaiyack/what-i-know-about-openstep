#import "ToDoCell.h"

@interface ToDoCell (PrivateMethods)
- (void)_setImage:(ToDoButtonState)aState;
@end

@implementation ToDoCell

- (id)init
{
    NSString *path;
    [super initTextCell:@""];

    triState = notDone;
    [self setButtonType:NSToggleButton];
    [self setImagePosition:NSImageLeft];
    [self setBezeled:YES];
    [self setFont:[NSFont userFontOfSize:12]];
    [self setAlignment:NSRightTextAlignment];
    path = [[NSBundle mainBundle] pathForImageResource:@"X.tiff"];
    doneImage = [[NSImage alloc] initByReferencingFile:path];
    path = [[NSBundle mainBundle] pathForImageResource:@"checkMark.tiff"];
    deferredImage = [[NSImage alloc] initByReferencingFile:path];

    return self;
}

- (void)dealloc
{
    [doneImage release];
    [deferredImage release];
    if (timeDue) [timeDue release];

    [super dealloc];
}
   
- (BOOL)startTrackingAt:(NSPoint)startPoint inView:(NSView *)controlView
{
    return YES;
}

- (void)stopTracking:(NSPoint)lastPoint at:(NSPoint)stopPoint inView:(NSView *)controlView mouseIsUp:(BOOL)flag
{
    if (flag == YES) {
        [self setTriState:([self triState]+1)];
    }
}

- (void)setTriState:(ToDoButtonState)newState
{
    if (newState == deferred+1)
        triState = notDone;
    else
        triState = newState;
    [self _setImage:triState];
 }


- (void)_setImage:(ToDoButtonState)aState
{
    switch(aState) {
       case notDone: {
           [self setImage:nil];
           break;
       }
       case done: {
           [self setImage:doneImage];
           break;
       }
       case deferred: {
           [self setImage:deferredImage];
           break;
       }
     }
     [(NSControl *)[self controlView] updateCell:self];
}

- (ToDoButtonState)triState {return triState;}

- (void)setState:(int)val
{
}


- (int)state
{
    if (triState == deferred)
        return done;
    else
        return (int)triState;
}

- (void)setTimeDue:(NSDate *)newTime
{
    if (timeDue)
        [timeDue autorelease];
    if (newTime) {
        timeDue = [newTime copy];
        [self setTitle:[timeDue descriptionWithCalendarFormat:@"%I:%M%p" timeZone:[NSTimeZone localTimeZone] locale:nil]];
    } else {
        timeDue = nil;
        [self setTitle:@"-->"];
    }
}

- (NSDate *)timeDue {return timeDue;}
   
@end
