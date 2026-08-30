/*
	NSSelection.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#ifndef STRICT_OPENSTEP

#import <Foundation/NSObject.h>
#import <Foundation/Foundation.h>
#import <AppKit/NSPasteboard.h>
#import <AppKit/AppKitDefines.h>

APPKIT_EXTERN NSString *NSSelectionPboardType;

@interface NSSelection : NSObject <NSCopying, NSCoding>
{
  @private
    NSData *data;
    struct _selFlags {
	unsigned int reserved:1;
	unsigned int isMagic:1;
	unsigned int _reserved:30;
    } selFlags;
    unsigned int _reservedSel1;
}

/* these methods return special objects that indicate special selections */
+ (NSSelection *)emptySelection;		/* nothing selected */
+ (NSSelection *)allSelection;			/* the result of a select all */
+ (NSSelection *)currentSelection;		/* whatever is currently selected */

/* data should be architecture independant and include a version stamp */
- (id)initWithDescriptionData:(NSData *)newData;
- (id)initWithPasteboard:(NSPasteboard *)pasteboard;
+ (NSSelection *)selectionWithDescriptionData:(NSData *)newData;

- (NSData *)descriptionData;

- (void)writeToPasteboard:(NSPasteboard *)pasteboard;

- (BOOL)isWellKnownSelection;

@end

#endif STRICT_OPENSTEP
