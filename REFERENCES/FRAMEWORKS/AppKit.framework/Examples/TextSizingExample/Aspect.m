/*
        Aspect.m
        TextSizingExample

        Author: Mike Ferris

	You may freely copy, distribute and reuse the code in this example.
	NeXT disclaims any warranty of any kind, expressed or implied,
	as to its fitness for any particular use.
*/

#import "Aspect.h"
#import "Controller.h"

const float LargeNumberForText = 1.0e7;

@implementation Aspect

- (id)initWithController:(Controller *)controller {
    self = [super init];
    if (self) {
        _controller = controller;
    }
    return self;
}

+ (id)aspectWithController:(Controller *)controller {
    Aspect *aspect = [[self alloc] initWithController:controller];
    return [aspect autorelease];
}

- (id)init {
    return [self initWithController:nil];
}

- (void)dealloc {
    if ([_controller currentAspect] == self) {
        [_controller swapInAspectAtIndex:-1];
    }
    [view release];
    [super dealloc];
}

- (Controller *)controller {
    return _controller;
}

- (NSString *)aspectName {
    return NSLocalizedString(@"Aspect", @"Default aspect name.");
}

- (NSString *)aspectNibName {
    // Aspects that only need the box and create the rest of their stuff programmatically, can just use the default nib.  Aspects with their own nibs should override.
    return @"Aspect";
}

- (void)loadNibIfNeeded {
    if (!_nibLoaded) {
        if ([NSBundle loadNibNamed:[self aspectNibName] owner:self]) {
            // We don't want the window, only the view.  So we retain the view and remove it from the window.  Then we can release the window.
            _nibLoaded = YES;
            [view retain];
            [view removeFromSuperview];
            [view setAutoresizesSubviews:YES];
            [view setAutoresizingMask:(NSViewWidthSizable | NSViewHeightSizable)];
            [view setFrameOrigin:NSMakePoint(0.0, 0.0)];
            [window release];
            window = nil;
            [self didLoadNib];
        } else {
            NSLog(@"Failed to load aspect nib %@.nib for class %@.", [self aspectName], [self class]);
        }
    }
}

- (NSView *)aspectView {
    [self loadNibIfNeeded];
    return view;
}

- (void)didLoadNib {
    // For subclassers
}

- (void)didSwapIn {
    // For subclassers
}

@end
