/*
 *  Controller.m
 *  Author: Ali Ozer
 *  Created: Mar 89 for 0.9 (YapApp.m)
 *  Modified: Jul & Aug 89 for 1.0
 *  Modified: Aug 90 for 2.0
 *  Modified: Apr & Jun 91 for 3.0. Localized Jan 92.
 *  Modified: Jan 96 for 4.0
 *
 *  Controller is the central controller class for Yap. It coordinates
 *  the output and document windows, opens documents, responds to external requests, ...
 *
 *  You may freely copy, distribute and reuse the code in this example.
 *  NeXT disclaims any warranty of any kind, expressed or implied,
 *  as to its fitness for any particular use.
 */

#import <AppKit/AppKit.h>
#import "Controller.h"
#import "YapDocument.h"
#import "Preferences.h"
#import "YapOutput.h"

@implementation Controller

/* Make sure all documents are saved before actually terminating the app...
*/
- (BOOL)applicationShouldTerminate:(NSApplication *)app {
    if (![YapDocument closeAllDocuments]) return NO;
    [Preferences saveDefaults];
    return YES;
}

/* Set up some initial state for the output window.
*/
- (void)applicationWillFinishLaunching:(NSNotification *)notification {
    [[self outputView] updateSizeFromPreferences];
    [[[self outputView] window] setFrameAutosaveName:@"Output Window"];
    [[[self outputView] window] setMenu:nil];
    [[[self outputView] window] setExcludedFromWindowsMenu:YES];
}

- (BOOL)application:(NSApplication *)sender openFile:(NSString *)filename {
    YapDocument *document = [YapDocument newWithPath:filename];
    if (document) [document setOutputView:[self outputView]];
    return document ? YES : NO;
}

- (BOOL)application:(NSApplication *)sender openTempFile:(NSString *)filename {
    return [self application:sender openFile:filename];
}

- (BOOL)applicationOpenUntitledFile:(NSApplication *)sender {
    YapDocument *newDocument = [YapDocument newUntitled];
    if (newDocument) [newDocument setOutputView:[self outputView]];
    return newDocument ? YES : NO;
}

- (void)createNew:(id)sender {
    YapDocument *newDocument = [YapDocument newUntitled];
    if (newDocument) [newDocument setOutputView:[self outputView]];
}

- (void)open:(id)sender {
    NSArray *documents = [YapDocument documentsFromOpenPanel];
    if (documents) [documents makeObjectsPerform:@selector(setOutputView:) withObject:[self outputView]];
}

- (void)saveAll:(id)sender {
    (void)[YapDocument saveAllDocuments];
}

/**** PostScript output ****/

- (YapOutput *)outputView {
    return outputView;
}

/* A dummy outlet (without an actual instance variable).
*/   
- (void)setScrollView:(id)anObject {
#ifdef WIN32
    [anObject setBorderType:NSBezelBorder];
#endif
}

/**** Info Panel related stuff ****/

- (void)showInfoPanel:(id)sender {
    if (!infoPanel) {
        if (![NSBundle loadNibNamed:@"Info" owner:self])  {
            NSLog(@"Failed to load Info.nib");
            NSBeep();
            return;
        }
        [infoPanel center];
    }
    [infoPanel makeKeyAndOrderFront:nil];
}

/* Another dummy outlet (without an actual instance variable).
*/   
- (void)setVersionField:(id)versionField {
    extern char Yap_VERS_NUM[];
    if (strlen(Yap_VERS_NUM) > 0) {
        NSString *versionString = [NSString stringWithFormat:NSLocalizedString(@"Release 4 (v%s)", @"Version string.  %s is replaced by the version number."), Yap_VERS_NUM];
        [versionField setStringValue:versionString];
    }
}

@end
