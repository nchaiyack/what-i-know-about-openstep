/*
        FixedSizeAspect.m
        TextSizingExample

        Author: Mike Ferris

	You may freely copy, distribute and reuse the code in this example.
	NeXT disclaims any warranty of any kind, expressed or implied,
	as to its fitness for any particular use.
*/

#import "FixedSizeAspect.h"
#import "Controller.h"

@implementation FixedSizeAspect

- (void)dealloc {
    [[[self controller] textStorage] removeLayoutManager:_layoutManager];
    [_layoutManager release];
    [super dealloc];
}

- (NSString *)aspectName {
    return NSLocalizedString(@"Non-scrolling Text", @"Display name for FixedSizeAspect.");
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

    // Create and configure NSTextContainer
    textContainer = [[NSTextContainer allocWithZone:[self zone]] initWithContainerSize:frame.size];
    [textContainer setWidthTracksTextView:YES];
    [textContainer setHeightTracksTextView:YES];
    [_layoutManager addTextContainer:textContainer];
    [textContainer release];

    // Create and configure NSTextView
    textView = [[NSTextView allocWithZone:[self zone]] initWithFrame:frame textContainer:textContainer];
    [textView setMinSize:frame.size];
    [textView setMaxSize:frame.size];
    [textView setHorizontallyResizable:NO];
    [textView setVerticallyResizable:NO];
    [textView setAutoresizingMask:(NSViewWidthSizable | NSViewHeightSizable)];
    [textView setSelectable:YES];
    [textView setEditable:YES];
    [textView setRichText:YES];
    [textView setImportsGraphics:YES];
    [textView setUsesFontPanel:YES];
    [textView setUsesRuler:YES];
    [aspectView addSubview:textView];
    [textView release];
}

- (void)didSwapIn {
    [[[self aspectView] window] makeFirstResponder:[_layoutManager firstTextView]];
}

@end
