/*
        Controller.m
        TextSizingExample

        Author: Mike Ferris

	You may freely copy, distribute and reuse the code in this example.
	NeXT disclaims any warranty of any kind, expressed or implied,
	as to its fitness for any particular use.
*/

#import "Controller.h"

#import "Aspect.h"
#import "VertScrollAspect.h"
#import "BiScrollAspect.h"
#import "FixedSizeAspect.h"
#import "TwoColumnsAspect.h"
#import "FieldAspect.h"


@implementation Controller

- (id)init {
    self = [super init];
    if (self) {
        _currentAspectIndex = -1;
    }
    return self;
}

- (void)dealloc {
    [self swapInAspectAtIndex:-1];
    [_aspects release];
    [_openPanelPath release];
    [_textStorage release];
    [[swapView window] autorelease];
    [super dealloc];
}

- (NSArray *)aspects {
    if (!_aspects) {
        _aspects = [[NSMutableArray allocWithZone:[self zone]] init];

        [_aspects addObject:[VertScrollAspect aspectWithController:self]];
        [_aspects addObject:[BiScrollAspect aspectWithController:self]];
        [_aspects addObject:[FixedSizeAspect aspectWithController:self]];
        [_aspects addObject:[TwoColumnsAspect aspectWithController:self]];
        [_aspects addObject:[FieldAspect aspectWithController:self]];
    }
    return _aspects;
}

- (Aspect *)currentAspect {
    if (_currentAspectIndex >= 0) {
        return [[self aspects] objectAtIndex:_currentAspectIndex];
    } else {
        return nil;
    }
}

- (void)swapInAspectAtIndex:(int)newIndex {
    if (newIndex != _currentAspectIndex) {
        NSArray *aspects = [self aspects];
        if (_currentAspectIndex >= 0) {
            // Swap out current aspect.
            [[[aspects objectAtIndex:_currentAspectIndex] aspectView] removeFromSuperview];
        }
        _currentAspectIndex = newIndex;
        if (_currentAspectIndex >= 0) {
            // Size and swap in new aspect.
            NSSize frameSize = [swapView frame].size;
            NSView *aspectView = [[aspects objectAtIndex:_currentAspectIndex] aspectView];
            [aspectView setFrame:NSMakeRect(0.0, 0.0, frameSize.width, frameSize.height)];
            [swapView addSubview:aspectView];
            // Notify the aspect it was just installed.
            [[aspects objectAtIndex:_currentAspectIndex] didSwapIn];
        }
    }
}

- (void)awakeFromNib {
    NSArray *aspects = [self aspects];
    unsigned i, c = [aspects count];
    
    NSString *path;
    NSData *rtfData = nil;

    // Create the NSTextStorage and load the default text file
    path = [[NSBundle bundleForClass:[self class]] pathForResource:@"README" ofType:@"rtf"];
    rtfData = [NSData dataWithContentsOfFile:path];
    _textStorage = [[NSTextStorage allocWithZone:[self zone]] initWithRTF:rtfData documentAttributes:NULL];
    
    // Load the popup.
    [aspectPopUpButton removeAllItems];
    for (i=0; i<c; i++) {
        [aspectPopUpButton addItemWithTitle:[[aspects objectAtIndex:i] aspectName]];
    }

    // Set up an initial aspect to view
    if (c > 0) {
        [self swapInAspectAtIndex:0];
    } else {
        // No aspects!
        [aspectPopUpButton addItemWithTitle:NSLocalizedString(@"No Aspect", @"Item title for aspect popup if no aspects exist.")];
    }
}

- (NSTextStorage *)textStorage {
    return _textStorage;
}

- (void)aspectPopUpAction:(id)sender {
    int selectedIndex = [sender indexOfSelectedItem];
    NSArray *aspects = [self aspects];
    if ((selectedIndex >= 0) && (selectedIndex < [aspects count])) {
        [self swapInAspectAtIndex:selectedIndex];
    }
}

- (void)loadDocumentAction:(id)sender {
    NSOpenPanel *openPanel = [NSOpenPanel openPanel];
    int runModalResult;

    // Configure the OpenPanel
    [openPanel setTitle:NSLocalizedString(@"Load", @"Title for open panel for load document action.")];
    [openPanel setTreatsFilePackagesAsDirectories:NO];
    [openPanel setAllowsMultipleSelection:NO];
    [openPanel setCanChooseDirectories:NO];
    [openPanel setCanChooseFiles:YES];
    [openPanel setDirectory:(_openPanelPath ? _openPanelPath : NSHomeDirectory())];

    // RUn the panel
    runModalResult = [openPanel runModal];
    if (runModalResult == NSOKButton) {
        NSString *path = [openPanel filename];
        NSString *extension = [path pathExtension];
        NSAttributedString *attrString;

        if ([extension isEqualToString:@"rtfd"] || [extension isEqualToString:@"rtf"]) {
            // Rich text.
            attrString = [[NSAttributedString allocWithZone:[self zone]] initWithPath:path documentAttributes:NULL];
        } else {
            // Plain text.
            attrString = [[NSAttributedString allocWithZone:[self zone]] initWithString:[NSString stringWithContentsOfFile:path]];
        }

        [_textStorage replaceCharactersInRange:NSMakeRange(0, [_textStorage length]) withAttributedString:attrString];
        [attrString release];
    }
    [_openPanelPath release];
    _openPanelPath = [[openPanel directory] copyWithZone:[self zone]];
}

- (void)infoAction:(id)sender {
    if (!infoPanel) {
        if (![NSBundle loadNibNamed:@"Info" owner:self]) {
            NSLog(@"Failed to load Info.nib.");
        }
    }
    [infoPanel makeKeyAndOrderFront:self];
}

@end
