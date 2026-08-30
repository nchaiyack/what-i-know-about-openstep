/*
        TwoColumnsAspect.m
        TextSizingExample

        Author: Mike Ferris

	You may freely copy, distribute and reuse the code in this example.
	NeXT disclaims any warranty of any kind, expressed or implied,
	as to its fitness for any particular use.
*/

#import "TwoColumnsAspect.h"
#import "Controller.h"

@implementation TwoColumnsAspect

- (void)dealloc {
    [[[self controller] textStorage] removeLayoutManager:_layoutManager];
    [_layoutManager release];
    [super dealloc];
}

- (NSString *)aspectName {
    return NSLocalizedString(@"Two Column Text", @"Display name for TwoColumnAspect.");
}

- (void)didLoadNib {
    NSTextStorage *textStorage = [[self controller] textStorage];
    NSView *aspectView = [self aspectView];
    NSRect frame;
    NSTextContainer *textContainer;
    NSTextView *textView;

    [super didLoadNib];

    // Figure frame for NSTextView (and NSTextContainer size)
    frame = NSInsetRect([aspectView bounds], 8.0, 8.0);
    
    // Create NSSLayoutManager
    _layoutManager = [[NSLayoutManager allocWithZone:[self zone]] init];
    [textStorage addLayoutManager:_layoutManager];

    // Create and configure first NSTextContainer
    textContainer = [[NSTextContainer allocWithZone:[self zone]] initWithContainerSize:NSMakeSize(200.0, frame.size.height)];
    [textContainer setWidthTracksTextView:YES];
    [textContainer setHeightTracksTextView:YES];
    [_layoutManager addTextContainer:textContainer];
    [textContainer release];

    // Create and configure first NSTextView
    textView = [[NSTextView allocWithZone:[self zone]] initWithFrame:NSMakeRect(frame.origin.x, frame.origin.y, 200.0, frame.size.height) textContainer:textContainer];
    [textView setMinSize:NSMakeSize(200.0, frame.size.height)];
    [textView setMaxSize:NSMakeSize(200.0, frame.size.height)];
    [textView setHorizontallyResizable:NO];
    [textView setVerticallyResizable:NO];
    [textView setAutoresizingMask:(NSViewMaxXMargin | NSViewHeightSizable)];
    [textView setSelectable:YES];
    [textView setEditable:YES];
    [textView setRichText:YES];
    [textView setImportsGraphics:YES];
    [textView setUsesFontPanel:YES];
    [textView setUsesRuler:YES];
    [aspectView addSubview:textView];
    [textView release];

    // Create and configure second NSTextContainer
    textContainer = [[NSTextContainer allocWithZone:[self zone]] initWithContainerSize:NSMakeSize(frame.size.width - 200.0 - 8.0, frame.size.height)];
    [textContainer setWidthTracksTextView:YES];
    [textContainer setHeightTracksTextView:YES];
    [_layoutManager addTextContainer:textContainer];
    [textContainer release];

    // Create and configure second NSTextView
    textView = [[NSTextView allocWithZone:[self zone]] initWithFrame:NSMakeRect(frame.origin.x + 200.0 + 8.0, frame.origin.y, frame.size.width - 200.0 - 8.0, frame.size.height) textContainer:textContainer];
    [textView setMinSize:NSMakeSize(frame.size.width - 200.0 - 8.0, frame.size.height)];
    [textView setMaxSize:NSMakeSize(frame.size.width - 200.0 - 8.0, frame.size.height)];
    [textView setHorizontallyResizable:NO];
    [textView setVerticallyResizable:NO];
    [textView setAutoresizingMask:(NSViewWidthSizable | NSViewHeightSizable)];
    // Don't bother configuring the shared attributes of the text view since we already did it for the first one.
    [aspectView addSubview:textView];
    [textView release];
}

- (void)didSwapIn {
    [[[self aspectView] window] makeFirstResponder:[_layoutManager firstTextView]];
}

@end
