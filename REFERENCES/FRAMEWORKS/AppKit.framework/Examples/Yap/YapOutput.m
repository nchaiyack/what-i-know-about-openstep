/*
 *  YapOutput.m
 *  Author: Ali Ozer
 *  Created: Mar 6, 1989
 *  Modified: Jun & Jul 1989 for 1.0. Exception handling for error detection.
 *  Modified: Aug 90 for 2.0. Added use of second context for robustness.
 *  Modified: Jan 92 for 3.0. Localized.
 *  Modified: Jan 96 for 4.0
 *
 *  This class is a subclass of view that manages the output in Yap. It
 *  provides a method to execute random PostScript code whose output
 *  is cached in an NSWindow for fast redraw response. (We use an NSWindow
 *  rather than an NSImage because we would like to have it displayed
 *  on screen as the PostScript is being executed.)                                                         
 *
 *  You may freely copy, distribute and reuse the code in this example.
 *  NeXT disclaims any warranty of any kind, expressed or implied,
 *  as to its fitness for any particular use.
 */

#import <AppKit/AppKit.h>
#import <AppKit/NSDPSServerContext.h>
#import "YapOutput.h"
#import "Controller.h"
#import "Preferences.h"
#import "YapWrap.h"

@implementation YapOutput

/* Lazily create the cache window... We make the window titled because we want it to come on screen (if the user has enabled the option).
*/
- (NSWindow *)cacheWindow {
    if (!cache) {
        cache = [[NSWindow allocWithZone:[self zone]] initWithContentRect:[self frame] styleMask:NSTitledWindowMask backing:NSBackingStoreRetained defer:NO];
        [cache setTitle:@"PostScript Execution Window"];
	[cache setBackgroundColor:[NSColor whiteColor]];
	[cache setMenu:nil];
        [cache setExcludedFromWindowsMenu:YES];
        [cache setReleasedWhenClosed:NO];
	[cache setBackgroundColor:[NSColor whiteColor]];
        [[cache contentView] allocateGState];	/* So that it has a gstate */
	[cache displayIfNeeded];	/* The background and title */
    }
    return cache;
}

- (void)updateSizeFromPreferences {
    NSSize currentSize = [self frame].size;
    NSSize newSize = {[[Preferences objectForKey:ViewWidth] floatValue], [[Preferences objectForKey:ViewHeight] floatValue]};
    if (!NSEqualSizes(currentSize, newSize)) {
        [self setFrameSize:newSize];
        if (cache) [cache setContentSize:newSize];
    }
}

- (void)drawRect:(NSRect)rect {
    PScomposite (rect.origin.x, rect.origin.y, rect.size.width, rect.size.height, [[[self cacheWindow] contentView] gState], rect.origin.x, rect.origin.y, NSCompositeCopy);
}

- (void)dealloc {
    if (cache) [cache release];
    [super dealloc];
}

/* SwitchContextsWithFocus() will make the specified context the current context and make it focus on the same area the old context was focused on.
*/
static void SwitchContextsWithFocus (NSDPSContext *newContext) {
    float c1x, c1y, c2x, c2y;
    float winCTM[6];
    int realWinNum;
    GetFocus (&c1x, &c1y, &c2x, &c2y, winCTM, &realWinNum);
    [NSDPSContext setCurrentContext:newContext];
    ReFocus (realWinNum, winCTM, c1x, c1y, c2x, c2y);
}

/* executePostScriptData: treats the contents of the NSData it is given as a PostScript program and executes it.  

For protection against errors, the PostScript code is interpreted in a context separate from the NSApplication's own context (which is created in the -init method of NSApplication).  We first focus on the cache, note the various parameters (global window number, the transformation matrix, and the clip path), and then switch to the alternate context and reapply the parameters to establish a focus on the same area.

Protection against PostScript errors is provided through the use of NS_DURING/NS_HANDLER.   If an error occurs, we immediately blast the second context and report the first error encountered.  If no errors occur during the execution, then we hang on to the context as it can be reused.

Note that the NSXEPSImageRep class provides a similar (but more powerful) sort of functionality for EPS files.  Use that class rather than the code here if you wish to make use of EPS files in your application.  This code here is meant for unstructured, short pieces of PostScript code,  exactly the kind that Yap encounters...
*/
- (void)executePostScriptData:(NSData *)data {
    int utime; /* Time taken to execute the code */
    NSString *statusString = @"";
    BOOL showCache = [[Preferences objectForKey:ShowCache] boolValue];
    BOOL clearCache = [[Preferences objectForKey:ClearCache] boolValue];
    BOOL showGridLines = [[Preferences objectForKey:ShowGridLines] boolValue];
    static NSDPSServerContext *yapContext = nil;	/* The second context */
    NSDPSContext *curContext;
    NSSize boundsSize = [self bounds].size;
    NSString *startString = [NSString stringWithFormat:@"/yaptime usertime def /yapsave save def /yapwidth %f def /yapheight %f def /showpage {} def\n", boundsSize.width, boundsSize.height];
    NSString *endString = @"\nyapsave restore /yaptime usertime yaptime sub def\n";

    /* Create the second context if it needs to be created. */

    if (yapContext == nil) {
	NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
	NSString *hostName = [userDefaults stringForKey:@"NSHost"];
	NSString *serverName = [userDefaults stringForKey:@"NSPSName"];
        NSTimeInterval timeout = [userDefaults floatForKey:@"NSNetTimeout"];
	yapContext = [[NSDPSServerContext allocWithZone:[self zone]] initWithHostName:hostName ? hostName : @"" serverName:serverName ? serverName : @"" textProc:NULL errorProc:NULL timeout:(timeout == 0.0) ? 60.0 : timeout secure:NO encapsulated:NO];
	if (yapContext == nil) {
            [[self window] setTitle:NSLocalizedString(@"Could not connect to window server.", @"Shown if a connection cannot be created with the window server")];
	}
    }

    [[self window] setTitle:NSLocalizedString(@"BUSY", @"String shown when PostScript is being executed")];
    [[self window] displayIfNeeded];	/* To get the title out */
    [[self window] orderFront:nil];

    /* If the user changed the size of the view, update. */
    [self updateSizeFromPreferences];

    /* Lock focus on the cache. If user wishes to see the cache, bring it up. */
    [[[self cacheWindow] contentView] lockFocus];
    if (clearCache) {
        NSEraseRect ([self bounds]);
    }
    if (showCache) {
        [[self cacheWindow] center];
        [[self cacheWindow] orderFront:nil];
    }
    if (showGridLines) {
	   NSSize size = [self bounds].size;
        DrawGrid(size.width, size.height, 72.0);
    }

    curContext = [NSDPSContext currentContext];

    NS_DURING {
        /* Focus the second context to whatever the first context is focused on. */
        SwitchContextsWithFocus (yapContext);
        [yapContext writePostScriptWithLanguageEncodingConversion:[startString dataUsingEncoding:NSASCIIStringEncoding]];
        [yapContext writePostScriptWithLanguageEncodingConversion:data];
        [yapContext writePostScriptWithLanguageEncodingConversion:[endString dataUsingEncoding:NSASCIIStringEncoding]];
        [yapContext wait]; /* This does not return until the execution is done. If there were any errors, we jump to the handler. */
        GetUserTime (&utime);
        statusString = [NSString stringWithFormat:NSLocalizedString(@"Postscript Output (Execution Time %d ms)", @"Shown when PostScript has executed successfully"), utime];
        [NSDPSContext setCurrentContext:curContext];       /* Restore the PS context */
    } NS_HANDLER {
        [NSDPSContext setCurrentContext:curContext];       /* Restore the PS context */
        [yapContext release];						/* Get rid of the questionable context */
        yapContext = nil;
        if (![[localException name] isEqualToString:DPSPostscriptErrorException]) {
            [localException raise];
        } else {
            statusString = [NSDPSContext stringForDPSError:(const DPSBinObjSeqRec *)[[[localException userInfo] objectForKey:@"DPSArg1ExceptionUserInfo"] pointerValue]];
        }
    } NS_ENDHANDLER

    if (showCache) [[self cacheWindow] orderOut:nil];
    [[[self cacheWindow] contentView] unlockFocus];
    [self setNeedsDisplay:YES];
    [[self window] setTitle:statusString];
}

@end