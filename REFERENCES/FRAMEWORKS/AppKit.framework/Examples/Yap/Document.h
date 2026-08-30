#import <AppKit/AppKit.h>

@interface Document : NSObject {
    NSTextView *textView;
    NSString *documentName;		/* If nil, never saved */
    BOOL isDocumentEdited;
}

/* Don't call init; call one of these methods... */
- (id)initWithPath:(NSString *)filename;	/* Should be an absolute path here; nil for untitled */
+ (Document *)newWithPath:(NSString *)filename;	/* Brings window front. Checks to see if document already open. */
+ (Document *)newUntitled;			/* Brings window front */
+ (NSArray *)documentsFromOpenPanel;		/* Puts up an open panel and returns an array of all opened documents */

/* These set/get the documentName instance var and also set the window title accordingly. "nil" is used if no title. */
- (void)setDocumentName:(NSString *)fileName;
- (NSString *)documentName;

/* These determine if document has been edited since last save */
- (void)setDocumentEdited:(BOOL)flag;
- (BOOL)isDocumentEdited;

/* Attributes */
- (NSTextView *)textView;
- (NSWindow *)window;

/* Misc methods */
+ (Document *)documentForWindow:(NSWindow *)window;
+ (Document *)documentForPath:(NSString *)filename;
+ (NSString *)cleanedUpPath:(NSString *)filename;
+ (unsigned)numberOfOpenDocuments;
+ (BOOL)closeAllDocuments;
+ (BOOL)saveAllDocuments;

/* Saving helpers. These return NO or nil if user cancels the save... */
- (BOOL)getDocumentName:(NSString **)newName oldName:(NSString *)oldName;
- (BOOL)saveDocument:(BOOL)showSavePanel;	/* Saves under documentName; if not set, tries to set it first */
- (BOOL)canCloseDocument;	/* Assures document is saved or user doesn't care about the changes; returns NO if user cancels */

/* File types to be accepted in open panel */
+ (NSArray *)fileTypes;

+ (void)setLastOpenSavePanelDirectory:(NSString *)dir;
+ (NSString *)openSavePanelDirectory;

/* Action methods */
- (void)saveAs:(id)sender;
- (void)saveTo:(id)sender;
- (void)save:(id)sender;
- (void)revert:(id)sender;
- (void)close:(id)sender;
- (void)orderFrontFindPanel:(id)sender;
- (void)findNext:(id)sender;
- (void)findPrevious:(id)sender;
- (void)enterSelection:(id)sender;
- (void)jumpToSelection:(id)sender;

/* Delegation messages */
- (void)textDidChange:(NSNotification *)textObject;
- (BOOL)windowShouldClose:(id)sender;
- (void)windowWillClose:(NSNotification *)notification;

/* File I/O. Returns NO if not successful. Doesn't set documentName. */
- (BOOL)loadFromPath:(NSString *)fileName;
- (BOOL)saveToPath:(NSString *)fileName;

@end
