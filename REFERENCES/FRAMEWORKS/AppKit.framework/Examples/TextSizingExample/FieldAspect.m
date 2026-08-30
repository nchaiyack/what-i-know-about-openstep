/*
        FieldAspect.m
        TextSizingExample

        Author: Mike Ferris

	You may freely copy, distribute and reuse the code in this example.
	NeXT disclaims any warranty of any kind, expressed or implied,
	as to its fitness for any particular use.
*/

#import "FieldAspect.h"

#define DEFAULT_TEXT NSLocalizedString(@"Yellow Curls", @"Default text to initialize the fields in FieldApsect with.")

@implementation FieldAspect

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [leftAlignedTextView setDelegate:nil];
    [centerAlignedTextView setDelegate:nil];
    [rightAlignedTextView setDelegate:nil];
    [scrollingLeftAlignedTextView setDelegate:nil];
    [scrollingCenterAlignedTextView setDelegate:nil];
    [scrollingRightAlignedTextView setDelegate:nil];
    [super dealloc];
}

- (NSString *)aspectName {
    return NSLocalizedString(@"Field-like Text", @"Display name for FieldAspect.");
}

- (NSString *)aspectNibName {
    return @"FieldAspect";
}

- (NSTextView *)makeFieldTextWithAlignment:(NSTextAlignment)alignment inBox:(NSBox *)box knownFrameRect:(NSRect *)knownFrame {
    // Creates and returns a field editor-ish text view which has been added as a subview of the given box and is retained only by the box.
    
    NSRect frame;
    NSTextView *textView;
    NSTextContainer *textContainer;
    NSFont *fieldFont = [NSFont messageFontOfSize:12.0];

    // Create the view
    frame = [[box contentView] bounds];
    textView = [[NSTextView allocWithZone:[self zone]] initWithFrame:frame];
    textContainer = [textView textContainer];

    // Set up container
    [textContainer setContainerSize:NSMakeSize(LargeNumberForText, NSHeight([textView frame]))];
    [textContainer setWidthTracksTextView:NO];
    [textContainer setHeightTracksTextView:NO];

    // Set up text view
    [textView setHorizontallyResizable:YES];
    [textView setVerticallyResizable:NO];
    [textView setMinSize:NSMakeSize((2.0 * [textContainer lineFragmentPadding]), NSHeight(frame))];
    [textView setMaxSize:frame.size];
    if (alignment == NSCenterTextAlignment) {
        [textView setAutoresizingMask:(NSViewMinXMargin | NSViewMaxXMargin)];
    } else if (alignment == NSRightTextAlignment) {
        [textView setAutoresizingMask:NSViewMinXMargin];
    } else {
        // NSLeftTextAlignment
        [textView setAutoresizingMask:NSViewMaxXMargin];
    }

    [textView setSelectable:YES];
    [textView setEditable:YES];
    [textView setRichText:NO];
    [textView setImportsGraphics:NO];
    [textView setUsesFontPanel:NO];
    [textView setUsesRuler:NO];
    [textView setDrawsBackground:YES];
    [textView setBackgroundColor:[NSColor textBackgroundColor]];
    [textView setFont:fieldFont];
    [textView setAlignment:alignment];
    [textView setTextColor:[NSColor controlTextColor]];
    [textView setSelectedTextAttributes:[NSDictionary dictionaryWithObjectsAndKeys:[NSColor selectedControlTextColor], NSForegroundColorAttributeName, [NSColor selectedTextBackgroundColor], NSBackgroundColorAttributeName, nil]];
    [textView setFieldEditor:YES];

    // Add it to the box.
    [box addSubview:textView];
    [[box contentView] setAutoresizesSubviews:YES];
    [textView release];

    // Give the field a default value and force layout.
    [textView setString:DEFAULT_TEXT];
    [textView sizeToFit];

    // Set up initial state for the unfortunate book keeping we have to do for our resizing text views in order to cause proper display invalidation for their superviews when they shrink.
    *knownFrame = [textView frame];

    // Reposition the view if alignment requires it.
    if (alignment == NSCenterTextAlignment) {
        [textView setFrameOrigin:NSMakePoint((NSMidX(frame) - (NSWidth(*knownFrame) / 2.0)), NSMinY(frame))];
    } else if (alignment == NSRightTextAlignment) {
        [textView setFrameOrigin:NSMakePoint((NSMaxX(frame) - NSWidth(*knownFrame)), NSMinY(frame))];
    }

    // Register for frame changes.
    [textView setDelegate:self];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(textViewFrameChanged:) name:NSViewFrameDidChangeNotification object:textView];

    return textView;
}

- (NSTextView *)makeScrollingFieldTextWithAlignment:(NSTextAlignment)alignment inBox:(NSBox *)box {
    // Creates and returns a field editor-ish text view which has been added as a subview of the given box and is retained only by the box.

    NSRect frame;
    NSClipView *clipView;
    NSTextView *textView;
    NSFont *fieldFont = [NSFont messageFontOfSize:12.0];
    NSTextContainer *textContainer;

    // Create the clip view and add it to the box
    frame = [[box contentView] bounds];
    clipView = [[NSClipView allocWithZone:[self zone]] initWithFrame:frame];
    [clipView setAutoresizingMask:(NSViewWidthSizable | NSViewHeightSizable)];
    [clipView setBackgroundColor:[NSColor textBackgroundColor]];
    [box addSubview:clipView];
    [[box contentView] setAutoresizesSubviews:YES];
    [clipView release];

    // Create the text view
    textView = [[NSTextView allocWithZone:[self zone]] initWithFrame:frame];
    textContainer = [textView textContainer];

    // Set up container
    [textContainer setContainerSize:NSMakeSize(LargeNumberForText, NSHeight([textView frame]))];
    [textContainer setWidthTracksTextView:NO];
    [textContainer setHeightTracksTextView:NO];

    // Set up text view
    [textView setHorizontallyResizable:YES];
    [textView setVerticallyResizable:NO];
    [textView setMinSize:frame.size];
    [textView setMaxSize:NSMakeSize(LargeNumberForText, NSHeight(frame))];
    [textView setAutoresizingMask:NSViewNotSizable];

    [textView setSelectable:YES];
    [textView setEditable:YES];
    [textView setRichText:NO];
    [textView setImportsGraphics:NO];
    [textView setUsesFontPanel:NO];
    [textView setUsesRuler:NO];
    [textView setDrawsBackground:YES];
    [textView setBackgroundColor:[NSColor textBackgroundColor]];
    [textView setFont:fieldFont];
    [textView setAlignment:alignment];
    [textView setTextColor:[NSColor controlTextColor]];
    [textView setSelectedTextAttributes:[NSDictionary dictionaryWithObjectsAndKeys:[NSColor selectedControlTextColor], NSForegroundColorAttributeName, [NSColor selectedTextBackgroundColor], NSBackgroundColorAttributeName, nil]];
    [textView setFieldEditor:YES];

    // Add text view to the clipView.
    [clipView setDocumentView:textView];
    [clipView setAutoresizesSubviews:NO];
    [textView release];

    // Give the field a default value and force layout.
    [textView setString:DEFAULT_TEXT];
    [textView sizeToFit];

    // We need to be the delegate.
    [textView setDelegate:self];

    return textView;
}

- (void)didLoadNib {
    // Make all the fields.
    leftAlignedTextView = [self makeFieldTextWithAlignment:NSLeftTextAlignment inBox:leftAlignedBox knownFrameRect:&leftTVKnownFrame];
    centerAlignedTextView = [self makeFieldTextWithAlignment:NSCenterTextAlignment inBox:centerAlignedBox knownFrameRect:&centerTVKnownFrame];
    rightAlignedTextView = [self makeFieldTextWithAlignment:NSRightTextAlignment inBox:rightAlignedBox knownFrameRect:&rightTVKnownFrame];
    scrollingLeftAlignedTextView = [self makeScrollingFieldTextWithAlignment:NSLeftTextAlignment inBox:scrollingLeftAlignedBox];
    scrollingCenterAlignedTextView = [self makeScrollingFieldTextWithAlignment:NSCenterTextAlignment inBox:scrollingCenterAlignedBox];
    scrollingRightAlignedTextView = [self makeScrollingFieldTextWithAlignment:NSRightTextAlignment inBox:scrollingRightAlignedBox];

    // Set up a tab order (which we will have to handle ourselves in the textDidEndEditing: notification).
    [leftAlignedTextView setNextKeyView:centerAlignedTextView];
    [centerAlignedTextView setNextKeyView:rightAlignedTextView];
    [rightAlignedTextView setNextKeyView:scrollingLeftAlignedTextView];
    [scrollingLeftAlignedTextView setNextKeyView:scrollingCenterAlignedTextView];
    [scrollingCenterAlignedTextView setNextKeyView:scrollingRightAlignedTextView];
    [scrollingRightAlignedTextView setNextKeyView:leftAlignedTextView];
}

- (void)textViewFrameChanged:(NSNotification *)notification {
    NSTextView *textView = [notification object];
    NSRect *knownFrame = NULL;
    NSRect newFrame = [textView frame];
    
    if (textView == leftAlignedTextView) {
        knownFrame = &leftTVKnownFrame;
    } else if (textView == centerAlignedTextView) {
        NSRect contentBounds = [[centerAlignedBox contentView] bounds];
        NSRect textViewFrame = [textView frame];

        [textView setFrameOrigin:NSMakePoint((NSMidX(contentBounds) - (NSWidth(textViewFrame) / 2.0)), NSMinY(textViewFrame))];
        knownFrame = &centerTVKnownFrame;
    } else if (textView == rightAlignedTextView) {
        NSRect contentBounds = [[rightAlignedBox contentView] bounds];
        NSRect textViewFrame = [textView frame];

        [textView setFrameOrigin:NSMakePoint((NSMaxX(contentBounds) - NSWidth(textViewFrame)), NSMinY(textViewFrame))];
        knownFrame = &rightTVKnownFrame;
    }

    // Check to see if we shrunk.  If we did, our superview will need some redrawing.  NSView should do this itself, but it doesn't in 4.0.
    if (knownFrame) {
        if (NSWidth(*knownFrame) > NSWidth(newFrame)) {
            // This isn't exactly general code for invalidating the areas we've exposed, but since we know something about the way it happens, we can make a few assumptions.  We know that only the width is changing.  We also know, based on the alignment exactly how the origin is moving based on the size differences.  In other applications these assumptions might not hold.
            float widthChange = NSWidth(*knownFrame) - NSWidth(newFrame);
            switch ([textView alignment]) {
                case NSCenterTextAlignment:
                    [[textView superview] setNeedsDisplayInRect:NSMakeRect(NSMinX(newFrame) - (widthChange / 2.0), NSMinY(newFrame), widthChange / 2.0, NSHeight(newFrame))];
                    [[textView superview] setNeedsDisplayInRect:NSMakeRect(NSMaxX(newFrame), NSMinY(newFrame), widthChange / 2.0, NSHeight(newFrame))];
                    break;
                case NSRightTextAlignment:
                    [[textView superview] setNeedsDisplayInRect:NSMakeRect(NSMinX(newFrame) - widthChange, NSMinY(newFrame), widthChange, NSHeight(newFrame))];
                    break;
                case NSLeftTextAlignment:
                default:
                    [[textView superview] setNeedsDisplayInRect:NSMakeRect(NSMaxX(newFrame), NSMinY(newFrame), widthChange, NSHeight(newFrame))];
                    break;
            }
        }
        // Remember the frame for next time.
        *knownFrame = newFrame;
    }
}

- (void)textDidEndEditing:(NSNotification *)notification {
    NSTextView *text = [notification object];
    unsigned whyEnd = [[[notification userInfo] objectForKey:@"NSTextMovement"] unsignedIntValue];
    NSTextView *newKeyView = text;

    // Unscroll the previous text.
    [text scrollRangeToVisible:NSMakeRange(0, 0)];
    
    if (whyEnd == NSTabTextMovement) {
        newKeyView = (NSTextView *)[text nextKeyView];
    } else if (whyEnd == NSBacktabTextMovement) {
        newKeyView = (NSTextView *)[text previousKeyView];
    }

    // Set the new key view and select its whole contents. 
    [[text window] makeFirstResponder:newKeyView];
    [newKeyView setSelectedRange:NSMakeRange(0, [[newKeyView textStorage] length])];
}

- (void)didSwapIn {
    [[leftAlignedTextView window] makeFirstResponder:leftAlignedTextView];
    [leftAlignedTextView setSelectedRange:NSMakeRange(0, [[leftAlignedTextView textStorage] length])];
}

@end
