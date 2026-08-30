/*
	NSDataLink.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#ifndef STRICT_OPENSTEP

#import <Foundation/NSObject.h>
#import <AppKit/AppKitDefines.h>

@class NSDataLinkManager;
@class NSPasteboard;
@class NSSelection;
@class NSArray;
@class NSDate;

typedef enum _NSDataLinkUpdateMode {
	NSUpdateContinuously = 1,
	NSUpdateWhenSourceSaved = 2,
	NSUpdateManually = 3,
	NSUpdateNever = 4
} NSDataLinkUpdateMode;

typedef enum _NSDataLinkDisposition {
	NSLinkInDestination = 1,
	NSLinkInSource = 2,
	NSLinkBroken = 3
} NSDataLinkDisposition;

APPKIT_EXTERN NSString *NSDataLinkPboardType;

/* A persistent identifier of links on the destination side. Never 0. */
typedef int NSDataLinkNumber;

/* filename suffix used for saved links */
APPKIT_EXTERN NSString *NSDataLinkFilenameExtension;

@interface NSDataLink : NSObject <NSCopying, NSCoding>
{
  @private
    NSSelection *srcSelection;
    id srcFile;
    NSString *srcAppName;
    id srcMgr;
    NSSelection *destSelection;
    NSString *destFileName;
    NSString *destAppName;
    id destMgr;
    long lastUpdateTime;
    NSDataLinkNumber linkNum;
    struct _dlFlags {
	unsigned int dirty:1;
	unsigned int memorable:1;
	unsigned int mode:2;
	unsigned int canUpdateContinuously:1;
	unsigned int updateMode:4;
	unsigned int appVerifiesLinks:1;
	unsigned int willOpenSource:1;
	unsigned int willUpdate:1;
	unsigned int dead:1;
	unsigned int cyclical:1;
	unsigned int reserved:18;
    } dlFlags;
    NSArray *types;
    unsigned int _reservedDataLink1;
}

- (id)initLinkedToSourceSelection:(NSSelection *)selection managedBy:(NSDataLinkManager *)linkManager supportingTypes:(NSArray *)newTypes;
- (id)initLinkedToFile:(NSString *)filename;
- (id)initWithPasteboard:(NSPasteboard *)pasteboard;
- (id)initWithContentsOfFile:(NSString *)filename;

- (void)writeToPasteboard:(NSPasteboard *)pasteboard;
- (BOOL)writeToFile:(NSString *)filename;

- (BOOL)saveLinkIn:(NSString *)directoryName;

- (NSArray *)types;
- (NSSelection *)sourceSelection;
- (NSSelection *)destinationSelection;
- (NSString *)sourceFilename;
- (NSString *)currentSourceFilename;
- (NSString *)destinationFilename;
- (NSString *)sourceApplicationName;
- (NSString *)destinationApplicationName;
- (NSDataLinkManager *)manager;
- (NSDate *)lastUpdateTime;
- (NSDataLinkNumber)linkNumber;
- (NSDataLinkDisposition)disposition;

- (BOOL)updateDestination;
- (BOOL)openSource;
- (BOOL)break;
- (void)setUpdateMode:(NSDataLinkUpdateMode)mode;
- (NSDataLinkUpdateMode)updateMode;
- (void)noteSourceEdited;

@end

#endif STRICT_OPENSTEP
