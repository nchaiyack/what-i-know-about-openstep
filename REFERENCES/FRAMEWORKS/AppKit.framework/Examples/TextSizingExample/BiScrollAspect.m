/*
        BiScrollAspect.m
        TextSizingExample

        Author: Mike Ferris

	You may freely copy, distribute and reuse the code in this example.
	NeXT disclaims any warranty of any kind, expressed or implied,
	as to its fitness for any particular use.
*/

#import "BiScrollAspect.h"
#import "Controller.h"

@implementation BiScrollAspect

- (void)dealloc {
    [[[self controller] textStorage] removeLayoutManager:_layoutManager];
    [_layoutManager release];
    [super dealloc];
}

- (NSString *)aspectName {
    return NSLocalizedString(@"Non-Wrapping Scrolling Text", @"Display name for BiScrollAspect.");
}

- (void)didLoadNib {
    NSTextStorage *textStorage = [[self controller] textStorage];
    NSView *aspectView = [self aspectView];
    NSRect frame;
    NSTextContainer *textContainer;
    NSTextView *textView;
    NSScrollView *scrollView;

    [super didLoadNib];

    // Create NSScrollView
    frame = NSInsetRect([aspectView bounds], 8.0, 8.0);
    scrollView = [[NSScrollView allocWithZone:[self zone]] initWithFrame:frame];
    [scrollView setBorderType:NSBezelBorder];
    [scrollView setHasVerticalScroller:YES];
    [scrollView setHasHorizontalScroller:YES];
    [scrollView setAutoresizingMask:(NSViewWidthSizable | NSViewHeightSizable)];
    [[scrollView contentView] setAutoresizesSubviews:YES];
    [aspectView addSubview:scrollView];
    [scrollView release];
    
    // Set frame for content area of scroll view
    frame.origin = NSMakePoint(0.0, 0.0);
    frame.size = [scrollView contentSize];
    
    // Create NSSLayoutManager
    _layoutManager = [[NSLayoutManager allocWithZone:[self zone]] init];
    [textStorage addLayoutManager:_layoutManager];

    // Create and configure NSTextContainer
    textContainer = [[NSTextContainer allocWithZone:[self zone]] initWithContainerSize:NSMakeSize(LargeNumberForText, LargeNumberForText)];
    [textContainer setWidthTracksTextView:NO];
    [textContainer setHeightTracksTextView:NO];
    [_layoutManager addTextContainer:textContainer];
    [textContainer release];

    // Create and configure NSTextView
    textView = [[NSTextView allocWithZone:[self zone]] initWithFrame:frame textContainer:textContainer];
    [textView setMinSize:frame.size];
    [textView setMaxSize:NSMakeSize(LargeNumberForText, LargeNumberForText)];
    [textView setHorizontallyResizable:YES];
    [textView setVerticallyResizable:YES];
    [textView setAutoresizingMask:NSViewNotSizable];
    [textView setSelectable:YES];
    [textView setEditable:YES];
    [textView setRichText:YES];
    [textView setImportsGraphics:YES];
    [textView setUsesFontPanel:YES];
    [textView setUsesRuler:YES];
    [scrollView setDocumentView:textView];
    [textView release];
}

- (void)didSwapIn {
    [[[self aspectView] window] makeFirstResponder:[_layoutManager firstTextView]];
}

@end
