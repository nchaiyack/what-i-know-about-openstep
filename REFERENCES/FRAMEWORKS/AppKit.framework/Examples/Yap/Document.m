/*
 *  Document.m
 *  Author: Ali Ozer
 *  Created: Jan 28, 1995 for TextEdit
 *  Modified: Apr 96
 *
 *  A generic text document class.
 *
 *  You may freely copy, distribute and reuse the code in this example.
 *  NeXT disclaims any warranty of any kind, expressed or implied,
 *  as to its fitness for any particular use.
 */

#import <AppKit/AppKit.h>
#import "Document.h"
#import "TextFinder.h"
#import "Preferences.h"

@implementation Document

/* Creates an untitled document. Doesn't bring the window up, but does position it correctly.
*/   
- (id)init {
    static NSPoint cascadePoint = {0.0, 0.0};

    if (!(self = [super init])) return nil;

    if (![NSBundle loadNibNamed:@"Document" owner:self])  {
        NSLog(@"Failed to load Document.nib");
        [self release];
        return nil;
    }

    if (NSEqualPoints(cascadePoint, NSZeroPoint)) {	/* First time through... */
        NSRect frame = [[self window] frame];
        cascadePoint = NSMakePoint(frame.origin.x, NSMaxY(frame));
    }
    cascadePoint = [[self window] cascadeTopLeftFromPoint:cascadePoint];
    [[self window] setDelegate:self];
    [[self textView] setDelegate:self];

    return self;
}

/* Creates a document from the specified path. Doesn't bring the window up, but does position it correctly.
*/   
- (id)initWithPath:(NSString *)filename {
    if (!(self = [self init])) return nil;
    if (filename && ![self loadFromPath:filename]) {
        [self release];
        return nil;
    }
    if (filename) {
	[[self class] setLastOpenSavePanelDirectory:[filename stringByDeletingLastPathComponent]];
    }
    [[self textView] setSelectedRange:NSMakeRange(0, 0)];
    [self setDocumentName:filename];
    return self;
}

/* Should create a new zone... 
*/
+ (Document *)newUntitled {
    Document *document = [[self alloc] initWithPath:nil];
    if (document) {     
        [[document window] makeKeyAndOrderFront:nil];
    }
    return document;
}

/* Should create a new zone...
*/
+ (Document *)newWithPath:(NSString *)filename {
    Document *document = [self documentForPath:filename];
    if (!document) {
        document =  [[self alloc] initWithPath:filename];
    }
    if (document) {     
        [[document window] makeKeyAndOrderFront:nil];
    }
    return document;
}
    
/* Clear the delegates of the text views and window, then release all resources and go away...
*/
- (void)dealloc {
    [[self textView] setDelegate:nil];
    [[self window] setDelegate:nil];
    [documentName release];
    
    [super dealloc];
}

/* A dummy outlet (without an actual instance variable)
*/   
- (void)setScrollView:(id)anObject {
#ifdef WIN32
    [anObject setBorderType:NSBezelBorder];
#endif
}

/* Close all documents, prompting the user if necessary. Returns NO if the user cancels the operation.
*/
+ (BOOL)closeAllDocuments {
   NSArray *windows = [[NSApplication sharedApplication] windows];
   unsigned count = [windows count];
   BOOL needsSaving = NO;

   // Determine if there are any unsaved documents...

   while (!needsSaving && count--) {
       NSWindow *window = [windows objectAtIndex:count];
       Document *document = [self documentForWindow:window];
       if (document && [document isDocumentEdited]) needsSaving = YES;
   }
   if (needsSaving) {
       int choice = NSRunAlertPanel(NSLocalizedString(@"Quit", @"Title of alert panel which comes up when user chooses Quit and there are unsaved documents."),
                       NSLocalizedString(@"You have unsaved documents.", @"Message in the alert panel which comes up when user chooses Quit and there are unsaved documents."),
                       NSLocalizedString(@"Review Unsaved", @"Choice (on a button) given to user which allows him/her to review all unsaved documents if he/she quits the application without saving them all first."),
                       NSLocalizedString(@"Quit Anyway", @"Choice (on a button) given to user which allows him/her to quit the application even though there are unsaved documents."),
                       NSLocalizedString(@"Cancel", @"Button choice allowing user to cancel quit"));
       if (choice == NSAlertOtherReturn)  {		/* Cancel */
           return NO;
       } else if (choice == NSAlertAlternateReturn) {	/* Quit anyway */
           return YES;
       } else {	/* Review unsaved */
           count = [windows count];
           while (count--) {
               NSWindow *window = [windows objectAtIndex:count];
               Document *document = [self documentForWindow:window];
               if (document) {
                   [window makeKeyAndOrderFront:nil];
                   if (![document canCloseDocument]) {
                       return NO;
                   }			
               }
           }
       }
   }
   return YES;
}

/* Saves all open documents... Returns NO if the user cancels out of the save.
*/
+ (BOOL)saveAllDocuments {
    NSArray *windows = [NSApp windows];
    unsigned count = [windows count];
    while (count--) {
        NSWindow *window = [windows objectAtIndex:count];
        Document *document = [self documentForWindow:window];
        if (document) {
            if ([document isDocumentEdited]) {
                if (![document saveDocument:NO]) return NO;
            }
        }
    }
    return YES;
}
 
- (NSTextView *)textView {
    return textView;
}

- (NSWindow *)window {
    return [[self textView] window];
}

+ (NSString *)cleanedUpPath:(NSString *)filename {
    NSString *resolvedSymlinks = [filename stringByResolvingSymlinksInPath];
    if ([resolvedSymlinks length] > 0) {
        NSString *standardized = [resolvedSymlinks stringByStandardizingPath];
        return [standardized length] ? standardized : resolvedSymlinks;
    }
    return filename;
}

- (void)setDocumentName:(NSString *)filename {
    [documentName autorelease];
    if (filename) {
        documentName = [[filename stringByResolvingSymlinksInPath] copyWithZone:[self zone]];
        [[self window] setTitleWithRepresentedFilename:documentName];
    } else {
        [[self window] setTitle:NSLocalizedString(@"UNTITLED", @"Name of new, untitled document")];
        documentName = nil;
    }
}

- (NSString *)documentName {
    return documentName;
}

- (void)setDocumentEdited:(BOOL)flag {
    if (flag != isDocumentEdited) {
        isDocumentEdited = flag;
        [[self window] setDocumentEdited:isDocumentEdited];
    }
}

- (BOOL)isDocumentEdited {
    return isDocumentEdited;
}

/**** User commands... ****/

- (void)printDocument:(id)sender {
    NSPrintInfo *printInfo = [[NSPrintInfo sharedPrintInfo] copy];
    [printInfo setHorizontalPagination:NSFitPagination];
    [printInfo setHorizontallyCentered:NO];
    [printInfo setVerticallyCentered:NO];
    [[NSPrintOperation printOperationWithView:[self textView] printInfo:printInfo] runOperation];
    [printInfo release];
}

- (void)revert:(id)sender {
    if (documentName) {
        NSString *fileName = [documentName lastPathComponent];
        int choice = NSRunAlertPanel(NSLocalizedString(@"Revert", @"Title of alert confirming revert"), 
				NSLocalizedString(@"Revert to saved version of %@?", @"Message confirming revert of specified document name."), 
				NSLocalizedString(@"OK", @"OK."), NSLocalizedString(@"Cancel", @"Button choice allowing user to cancel."), nil, fileName);
        if (choice == NSAlertDefaultReturn) {
            if (![self loadFromPath:documentName]) {
                (void)NSRunAlertPanel(NSLocalizedString(@"Couldn't Revert", @"Title of alert indicating file couldn't be reverted"), 
				NSLocalizedString(@"Couldn't revert to saved version of %@.", @"Message indicating file couldn't be reverted."), 
				NSLocalizedString(@"OK", @"OK."), nil, nil, documentName);
            } else {
                [self setDocumentEdited:NO];
            }
        }
    }
}

- (void)close:(id)sender {
    [[self window] close];
}

- (void)saveTo:(id)sender { /* ??? Not correct */
    [self saveAs:sender];
}

- (void)saveAs:(id)sender {
    (void)[self saveDocument:YES];
}

- (void)save:(id)sender {
    (void)[self saveDocument:NO];
}

/**** Find submenu commands ****/

- (void)orderFrontFindPanel:(id)sender {
    [[TextFinder sharedInstance] orderFrontFindPanel:sender];
}

- (void)findNext:(id)sender {
    [[TextFinder sharedInstance] findNext:sender];
}

- (void)findPrevious:(id)sender {
    [[TextFinder sharedInstance] findPrevious:sender];
}

- (void)enterSelection:(id)sender {
    NSRange range = [[self textView] selectedRange];
    if (range.length) {
        [[TextFinder sharedInstance] setFindString:[[[self textView] string] substringWithRange:range]];
    } else {
        NSBeep();
    }
}

- (void)jumpToSelection:(id)sender {
    [textView scrollRangeToVisible:[[self textView] selectedRange]];
}

/**** Document read/write routines... ****/

+ (NSArray *)fileTypes {
    return nil;
}

/* Opens a new document. Puts up an open panel.
*/
+ (NSArray *)documentsFromOpenPanel {
    NSArray *fileTypes = [self fileTypes];
    NSMutableArray *documents = [NSMutableArray array];
    NSOpenPanel *panel = [NSOpenPanel openPanel];
    [panel setAllowsMultipleSelection:YES];
    [panel setDirectory:[self openSavePanelDirectory]];
    if (fileTypes ? [panel runModalForTypes:fileTypes] : [panel runModal]) {
        NSArray *filenames = [panel filenames];
        unsigned cnt, numFiles = [filenames count];
        for (cnt = 0; cnt < numFiles; cnt++) {
	    Document *document;
            NSString *filename = [filenames objectAtIndex:cnt];
            if (!(document = [self newWithPath:filename])) {
                NSString *alternate = (cnt + 1 == numFiles) ? nil : NSLocalizedString(@"Abort", @"Button allowing user to abort opening multiple files after one couldn't be opened");
                unsigned choice = NSRunAlertPanel(NSLocalizedString(@"File system error", @"Title of alert indicating file couldn't be opened"),
                                NSLocalizedString(@"Couldn't open file %@.", @"Message indicating file couldn't be opened."),
                                NSLocalizedString(@"OK", @"OK"), alternate, nil, filename);
                if (choice == NSCancelButton) break;
            } else {
	 	[documents addObject:document];
	    }
        }
    }
    return documents;
}

/* Loads document from the specified path. Returns NO if the file could not be loaded.
*/
- (BOOL)loadFromPath:(NSString *)fileName {
    NSString *fileContents;
    if (fileContents = [[NSString alloc] initWithContentsOfFile:fileName]) {
        [[self textView] setString:fileContents];
        [fileContents release];
        return YES;
    } else {
        return NO;
    }
}

/* Saves the document. Puts up save panel if necessary or if showSavePanel is YES. Returns NO if the user cancels the save...
*/
- (BOOL)saveDocument:(BOOL)showSavePanel {
    NSString *nameForSaving = [self documentName];
        
    while (1) {
        if (!nameForSaving || showSavePanel) {
            if (![self getDocumentName:&nameForSaving oldName:nameForSaving]) return NO;	/* Cancelled */
        }
        if ([self saveToPath:nameForSaving]) {
            [self setDocumentName:nameForSaving];
            [self setDocumentEdited:NO];
	    [[self class] setLastOpenSavePanelDirectory:[nameForSaving stringByDeletingLastPathComponent]];
	    return YES;
        } else {
            NSRunAlertPanel(@"Couldn't Save",
                NSLocalizedString(@"Couldn't save document as %@.", @"Message indicating document couldn't be saved under the given name."),
                NSLocalizedString(@"OK", @"OK."), nil, nil, nameForSaving);
            nameForSaving = nil;
        }
    }
    return YES;
}

/* Puts up a save panel to get a final name from the user. If the user cancels, returns NO. If encoding is non-NULL, puts up the encoding accessory.
*/
- (BOOL)getDocumentName:(NSString **)newName oldName:(NSString *)oldName {
    NSSavePanel *panel = [NSSavePanel savePanel];
    [panel setTitle:NSLocalizedString(@"Save", @"Title of save and alert panels when saving")];
    if (oldName ? [panel runModalForDirectory:[oldName stringByDeletingLastPathComponent] file:[oldName lastPathComponent]] : [panel runModalForDirectory:[[self class] openSavePanelDirectory] file:@""]) {
        *newName = [panel filename];
        return YES;
    } else {
        return NO;
    }
}

/* Saves to specified path. Will create backups and save fileswritable if so desired... Returns NO if file cannot be saved.
*/
- (BOOL)saveToPath:(NSString *)fileName {
    BOOL success = NO;
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSDictionary *curAttributes = [fileManager fileAttributesAtPath:fileName traverseLink:YES];
    NSString *actualFileNameToSave = [fileName stringByResolvingSymlinksInPath];	/* Follow links to save */

    if (curAttributes && ![[Preferences objectForKey:DeleteBackup] boolValue]) {	/* Don't delete backup file... */
        NSString *backupFileName;
        backupFileName = [actualFileNameToSave stringByAppendingString:@"~"];
        if ([fileManager fileExistsAtPath:backupFileName]) {
            (void)[fileManager removeFileAtPath:backupFileName handler:nil];
        }
        (void)[fileManager movePath:actualFileNameToSave toPath:backupFileName handler:nil];	
    }

    success = [[[self textView] string] writeToFile:actualFileNameToSave atomically:YES];

    /* Apply the original permissions to the new file. */
    if (success && curAttributes) {
        id permissions = [curAttributes objectForKey:NSFilePosixPermissions];
        if (permissions) {
            [fileManager changeFileAttributes:[NSDictionary dictionaryWithObjectsAndKeys:permissions, NSFilePosixPermissions, nil] atPath:actualFileNameToSave];
        }
    }
    return success;
}

/**** Delegation ****/

- (BOOL)windowShouldClose:(id)sender {
    return [self canCloseDocument];
}

- (void)windowWillClose:(NSNotification *)notification {
    NSWindow *window = [self window];
    [window setDelegate:nil];
    [self release];
}

- (void)textDidChange:(NSNotification *)textObject {
    if (!isDocumentEdited) {
        [self setDocumentEdited:YES];
    }
}

/**** Misc ****/

/* Returns YES if the document can be closed. If the document is edited, gives the user a chance to save. Returns NO if the user cancels.
*/
- (BOOL)canCloseDocument {
    if (isDocumentEdited) {
        int result = NSRunAlertPanel(
                        NSLocalizedString(@"Close", @"Title of alert panel which comes when the user tries to quit or close a window containing an unsaved document."),
                        NSLocalizedString(@"Document has been edited. Save?", @"Question asked of user when he/she tries to close a window containing an unsaved document."),
                        NSLocalizedString(@"Save", @"Button choice which allows the user to save the document."),
                        NSLocalizedString(@"Don't Save", @"Button choice which allows the user to abort the save of a document which is being closed."),
                        NSLocalizedString(@"Cancel", @"Button choice allowing user to cancel."));
        if (result == NSAlertDefaultReturn) {	/* Save */
            if (![self saveDocument:NO]) return NO;
        } else if (result == NSAlertOtherReturn) {	/* Cancel */
            return NO;
        }	/* Don't save case falls through to the YES return */
    }
    return YES;
}

/* Return the document in the specified window.
*/
+ (Document *)documentForWindow:(NSWindow *)window {
    id delegate = [window delegate];
    return (delegate && [delegate isKindOfClass:[Document class]]) ? delegate : nil;
}

/* Return an existing document...
*/
+ (Document *)documentForPath:(NSString *)filename {
    NSArray *windows = [[NSApplication sharedApplication] windows];
    unsigned cnt, numWindows = [windows count];
    filename = [self cleanedUpPath:filename];	/* Clean up the incoming path */
    for (cnt = 0; cnt < numWindows; cnt++) {
        Document *document = [self documentForWindow:[windows objectAtIndex:cnt]];
        NSString *docName = [document documentName];	
        if (docName && [filename isEqual:[self cleanedUpPath:docName]]) return document;
    }
    return nil;
}

+ (unsigned)numberOfOpenDocuments {
    NSArray *windows = [[NSApplication sharedApplication] windows];
    unsigned cnt, numWindows = [windows count], numDocuments = 0;
    for (cnt = 0; cnt < numWindows; cnt++) {
        if ([self documentForWindow:[windows objectAtIndex:cnt]]) numDocuments++;
    }
    return numDocuments;
}

static NSString *lastOpenSavePanelDir = nil;

/* Sets the directory in which a save was last done...
*/
+ (void)setLastOpenSavePanelDirectory:(NSString *)dir {
    if (lastOpenSavePanelDir != dir) {
	[lastOpenSavePanelDir autorelease];
	lastOpenSavePanelDir = [dir copy];
    }
}

/* Returns the directory in which open/save panels should come up... If the OpenPanelFollowsMainWindow default is set, we have the open panel follow the main window.
*/
+ (NSString *)openSavePanelDirectory {
    if ([[NSUserDefaults standardUserDefaults] boolForKey:@"OpenPanelFollowsMainWindow"]) {
	Document *doc = [self documentForWindow:[NSApp mainWindow]];
	if (doc && [doc documentName]) {
            return [[doc documentName] stringByDeletingLastPathComponent];
	}
    } else if (lastOpenSavePanelDir) {
	return lastOpenSavePanelDir;
    }
    return NSHomeDirectory();
}


@end
