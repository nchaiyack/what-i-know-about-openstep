/*	NSFileManager.h
	File operations
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/

#if !defined(STRICT_OPENSTEP)

#import <Foundation/NSObject.h>
#import <Foundation/NSUtilities.h>

@class NSString, NSDate, NSDirectoryEnumerator, NSDictionary, NSArray, NSData;

@interface NSFileManager : NSObject

+ (NSFileManager *)defaultManager;

- (NSString *)currentDirectoryPath;
- (BOOL)changeCurrentDirectoryPath:(NSString *)path;

- (NSDictionary *)fileAttributesAtPath:(NSString *)path traverseLink:(BOOL)yorn;

- (BOOL)changeFileAttributes:(NSDictionary *)attributes atPath:(NSString *)path;

- (BOOL)fileExistsAtPath:(NSString *)path;
- (BOOL)fileExistsAtPath:(NSString *)path isDirectory:(BOOL *)isDirectory;
- (BOOL)isReadableFileAtPath:(NSString *)path;
- (BOOL)isWritableFileAtPath:(NSString *)path;
- (BOOL)isExecutableFileAtPath:(NSString *)path;
- (BOOL)isDeletableFileAtPath:(NSString *)path;

- (BOOL)contentsEqualAtPath:(NSString *)path1 andPath:(NSString *)path2;
- (BOOL)linkPath:(NSString *)src toPath:(NSString *)dest handler:handler;
- (BOOL)copyPath:(NSString *)src toPath:(NSString *)dest handler:handler;

- (BOOL)movePath:(NSString *)src toPath:(NSString *)dest handler:handler;	

- (BOOL)removeFileAtPath:(NSString *)path handler:handler;

- (NSArray *)directoryContentsAtPath:(NSString *)path;
- (NSDirectoryEnumerator *)enumeratorAtPath:(NSString *)path;
- (NSArray *)subpathsAtPath:(NSString *)path;

- (BOOL)createDirectoryAtPath:(NSString *)path attributes:(NSDictionary *)attributes;

- (NSData *)contentsAtPath:(NSString *)path;
- (BOOL)createFileAtPath:(NSString *)path contents:(NSData *)data attributes:(NSDictionary *)attr;

- (NSString *)pathContentOfSymbolicLinkAtPath:(NSString *)path;
- (BOOL)createSymbolicLinkAtPath:(NSString *)path pathContent:(NSString *)otherpath;

- (NSDictionary *)fileSystemAttributesAtPath:(NSString *)path;

- (const char *)fileSystemRepresentationWithPath:(NSString *)path;
- (NSString *)stringWithFileSystemRepresentation:(const char *)str length:(unsigned)len;

@end

@interface NSObject (NSCopyLinkMoveHandler)
- (BOOL)fileManager:(NSFileManager *)fm shouldProceedAfterError:(NSDictionary *)errorInfo;
- (void)fileManager:(NSFileManager *)fm willProcessPath:(NSString *)path;
@end

@interface NSDirectoryEnumerator : NSEnumerator
- (NSDictionary *)fileAttributes;
- (NSDictionary *)directoryAttributes;
- (void)skipDescendents;
@end

/**************** File Attributes ****************/

FOUNDATION_EXPORT NSString *NSFileType;
FOUNDATION_EXPORT NSString 	*NSFileTypeDirectory;
FOUNDATION_EXPORT NSString 	*NSFileTypeRegular;
FOUNDATION_EXPORT NSString 	*NSFileTypeSymbolicLink;
FOUNDATION_EXPORT NSString 	*NSFileTypeSocket;
FOUNDATION_EXPORT NSString 	*NSFileTypeCharacterSpecial;
FOUNDATION_EXPORT NSString 	*NSFileTypeBlockSpecial;
FOUNDATION_EXPORT NSString 	*NSFileTypeUnknown;
FOUNDATION_EXPORT NSString	*NSFileSize;
FOUNDATION_EXPORT NSString *NSFileModificationDate;
FOUNDATION_EXPORT NSString *NSFileReferenceCount;
FOUNDATION_EXPORT NSString *NSFileDeviceIdentifier;
FOUNDATION_EXPORT NSString *NSFileOwnerAccountName;
FOUNDATION_EXPORT NSString *NSFileGroupOwnerAccountName;
FOUNDATION_EXPORT NSString *NSFilePosixPermissions;
FOUNDATION_EXPORT NSString *NSFileSystemNumber;
FOUNDATION_EXPORT NSString *NSFileSystemFileNumber;

/* File System attributes */
FOUNDATION_EXPORT NSString *NSFileSystemSize;
FOUNDATION_EXPORT NSString *NSFileSystemFreeSize;
FOUNDATION_EXPORT NSString *NSFileSystemNodes;
FOUNDATION_EXPORT NSString *NSFileSystemFreeNodes;

@interface NSDictionary (NSFileAttributes)

- (unsigned long long)fileSize;
- (NSDate *)fileModificationDate;
- (NSString *)fileType;
- (unsigned long)filePosixPermissions;
- (NSString *)fileOwnerAccountName;
- (NSString *)fileGroupOwnerAccountName;
#ifndef WIN32
- (unsigned long)fileSystemNumber;
- (unsigned long)fileSystemFileNumber;
#endif

@end

#endif /* !STRICT_OPENSTEP */
