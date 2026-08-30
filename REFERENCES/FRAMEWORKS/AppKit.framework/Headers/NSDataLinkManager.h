/*
	NSDataLinkManager.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#ifndef STRICT_OPENSTEP

#import <Foundation/NSObject.h>
#import <AppKit/NSGraphics.h>
#import <AppKit/AppKitDefines.h>

@class List;
@class NSPasteboard;
@class NSDataLink;
@class NSSelection;
@class NSWindow;

@interface NSDataLinkManager : NSObject <NSCoding> {
  @private
    id delegate;
    id ref;
    List *srcLinks;
    List *destLinks;
    struct _lmFlags {
	unsigned int isEdited:1;
	unsigned int doUI:1;
	unsigned int showOutlines:1;
	unsigned int registered:1;
	unsigned int linksDirty:1;
	unsigned int delegateVerifiesLinks:1;
	unsigned int reserved:26;
    } lmFlags;
    int destLinksCounter;
    long lastEditTime;
    List *linkInfo;
    NSPasteboard *linkInfoPboard;
    int linkInfoChangeCount;
    unsigned int _reservedDataLinkManager1;
}

- (id)initWithDelegate:(id)obj;
- (id)initWithDelegate:(id)obj fromFile:(NSString *)path;

- (id)delegate;
- (NSString *)filename;
- (BOOL)isEdited;
- (void)setInteractsWithUser:(BOOL)flag;
- (BOOL)interactsWithUser;
- (void)setDelegateVerifiesLinks:(BOOL)flag;
- (BOOL)delegateVerifiesLinks;

/* used to notify DataLinkManager whats happening with the doc */
- (void)noteDocumentSaved;
- (void)noteDocumentReverted;
- (void)noteDocumentSavedAs:(NSString *)path;
- (void)noteDocumentSavedTo:(NSString *)path;
- (void)noteDocumentClosed;
- (void)noteDocumentEdited;

/* adds a link to a document */
- (BOOL)addLink:(NSDataLink *)link at:(NSSelection *)selection;
- (BOOL)addLinkAsMarker:(NSDataLink *)link at:(NSSelection *)selection;

/* copies info about all existing links into a pasteboard */
- (void)writeLinksToPasteboard:(NSPasteboard *)pasteboard;

/* adds a data link to a document using info from writeLinksToPasteboard: */
- (NSDataLink *)addLinkPreviouslyAt:(NSSelection *)oldSelection fromPasteboard:(NSPasteboard *)pasteboard at:(NSSelection *)selection;

/* sets whether to show outlines around linked data */
- (void)setLinkOutlinesVisible:(BOOL)flag;
- (BOOL)areLinkOutlinesVisible;

/* breaks all links in a document */
- (void)breakAllLinks;

- (NSDataLink *)destinationLinkWithSelection:(NSSelection *)destSel;

- (NSEnumerator *)sourceLinkEnumerator;
- (NSEnumerator *)destinationLinkEnumerator;

@end


/* generic selection messages, sent to the LinkManager's delegate.  Return NO if the selecion arg can not be resolved. */
@interface NSObject(NSSelectionHandling)

- (BOOL)showSelection:(NSSelection *)selection;
- (BOOL)copyToPasteboard:(NSPasteboard *)pasteboard at:(NSSelection *)selection cheapCopyAllowed:(BOOL)flag;
- (BOOL)pasteFromPasteboard:(NSPasteboard *)pasteboard at:(NSSelection *)selection;
- (BOOL)importFile:(NSString *)filename at:(NSSelection *)selection;
- (NSWindow *)windowForSelection:(NSSelection *)selection;

@end


/* delegate methods specific to links */
@interface NSObject(NSDataLinkManagerDelegate)

/* used to close documents opened without UI */
- (void)dataLinkManagerCloseDocument:(NSDataLinkManager *)sender;

- (void)dataLinkManager:(NSDataLinkManager *)sender didBreakLink:(NSDataLink *)link;
- (void)dataLinkManagerRedrawLinkOutlines:(NSDataLinkManager *)sender;
- (void)dataLinkManagerDidEditLinks:(NSDataLinkManager *)sender;

/* if not implemented, doc assumes that whenever the app saves all linking clients need to be updated */
- (BOOL)dataLinkManagerTracksLinksIndividually:(NSDataLinkManager *)sender;

- (void)dataLinkManager:(NSDataLinkManager *)sender startTrackingLink:(NSDataLink *)link;
- (void)dataLinkManager:(NSDataLinkManager *)sender stopTrackingLink:(NSDataLink *)link;

/* only needed if you do setLinksVerifiedByDelegate:Yes */
- (BOOL)dataLinkManager:(NSDataLinkManager *)sender isUpdateNeededForLink:(NSDataLink *)link;

@end

APPKIT_EXTERN void NSFrameLinkRect(NSRect aRect, BOOL isDestination);
APPKIT_EXTERN float NSLinkFrameThickness(void);

#endif STRICT_OPENSTEP
