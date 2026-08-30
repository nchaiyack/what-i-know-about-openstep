#import <AppKit/AppKit.h>
#define diffControllerName @"DiffMergeController4.0"

//
// fileSet is a dictionary with the following keys (NSStrings):
// fileA
// fileB
// ancestor  (optional key)
// merge     (optional key)
//
// The value for each of the above keys is another dictionary which
// contains at least the key "name".  The value of "name" should be a
// full path to a file or directory.  The dictionary can contain the
// optional key "displayName" whose value is the name that FileMerge
// will use when referring to this file.
//
// When comparing directories, the dictionary may contain the key
// InitialViewParameters.  The value of this key should be another
// dictionary which may contain one or more of the following keys:
// Identical, Added/Deleted, ChangedLeft, ChangedRight, ChangedBoth.
// The value for these keys can be YES or NO (anything else is
// interpreted as NO).  A missing key defaults to YES.
//

#if 0

@protocol FileMergeRequestorProtocol
- (oneway) filesDidMerge:     (NSDictionary *) fileSet;
- (oneway) mergeDidAbort:     (NSDictionary *) fileSet;
- (oneway) diffDidSucceed:    (NSDictionary *) fileSet;
- (oneway) diffDidNotSucceed: (NSDictionary *) fileSet;
@end

#endif

@protocol FileMergeCopyProtocol

- (BOOL) copyPath: (NSString*) fromPath toPath: (NSString*) toPath;
- (BOOL) removeFileAtPath: (NSString*) path;
- (BOOL) writeData: (bycopy NSData*) data toPath: (NSString*) toPath;
- (BOOL) createDirectoryAtPath: (NSString*) directory;

@end

@protocol FileMergeRequestProtocol

- (oneway) doDiffForFileSet: (NSDictionary *) fileSet
               copyDelegate: (id<FileMergeCopyProtocol>) copier;

@end

