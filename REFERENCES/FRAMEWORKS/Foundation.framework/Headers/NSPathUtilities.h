/*	NSPathUtilities.h
	NSString protocol extension to deal with Posix file names.
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/

#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>

@interface NSString (NSStringPathExtensions)

#if !defined(STRICT_OPENSTEP)

+ (NSString *)pathWithComponents:(NSArray *)components;
- (NSArray *)pathComponents;

- (BOOL)isAbsolutePath;

#endif /* !STRICT_OPENSTEP */

- (NSString *)lastPathComponent;
- (NSString *)stringByDeletingLastPathComponent;
- (NSString *)stringByAppendingPathComponent:(NSString *)str;

- (NSString *)pathExtension;
- (NSString *)stringByDeletingPathExtension;
- (NSString *)stringByAppendingPathExtension:(NSString *)str;

- (NSString *)stringByAbbreviatingWithTildeInPath;
- (NSString *)stringByExpandingTildeInPath;

- (NSString *)stringByStandardizingPath;

- (NSString *)stringByResolvingSymlinksInPath;

- (NSArray *)stringsByAppendingPaths:(NSArray *)paths;

- (unsigned)completePathIntoString:(NSString **)outputName caseSensitive:(BOOL)flag matchesIntoArray:(NSArray **)outputArray filterTypes:(NSArray *)filterTypes;

- (const char *)fileSystemRepresentation;
- (BOOL)getFileSystemRepresentation:(char *)cname maxLength:(unsigned)max;

@end

#if !defined(STRICT_OPENSTEP)
@interface NSArray (NSArrayPathExtensions)

-(NSArray *)pathsMatchingExtensions:(NSArray *)filterTypes;

@end
#endif

FOUNDATION_EXPORT NSString *NSUserName(void);
FOUNDATION_EXPORT NSString *NSHomeDirectory(void);
FOUNDATION_EXPORT NSString *NSHomeDirectoryForUser(NSString *userName);

#if !defined(STRICT_OPENSTEP)

FOUNDATION_EXPORT NSString *NSFullUserName(void);
FOUNDATION_EXPORT NSArray *NSStandardApplicationPaths(void);
FOUNDATION_EXPORT NSArray *NSStandardLibraryPaths(void);
FOUNDATION_EXPORT NSString *NSTemporaryDirectory(void);
FOUNDATION_EXPORT NSString *NSOpenStepRootDirectory(void);

#endif /* !STRICT_OPENSTEP */
