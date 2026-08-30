/*	NSPPL.h
	Persistent Property List
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/

#if !defined(STRICT_OPENSTEP)

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

@class NSData, NSDictionary, NSMutableDictionary, NSString;
@class _NSPPLCache, _NSPPLMutables, _NSPPLStore;

FOUNDATION_EXPORT NSString *NSPPLDidBecomeDirtyNotification;
FOUNDATION_EXPORT NSString *NSPPLDidSaveNotification;

@interface NSPPL : NSObject {
@private
    _NSPPLStore		*store;
    _NSPPLMutables	*mutables;
    _NSPPLCache		*cache;
    unsigned		rootHandle;
    unsigned		version;
    BOOL		readOnly;
    BOOL		isDirty;
    void		*reserved;
}

+ (id)pplWithPath:(NSString *)path create:(BOOL)create readOnly:(BOOL)readOnly;
- (id)initWithPath:(NSString *)path create:(BOOL)create readOnly:(BOOL)readOnly;

+ (id)pplWithPath:(NSString *)path fromPPLData:(NSData *)pplData readOnly:(BOOL)readOnly;
- (id)initWithPath:(NSString *)path fromPPLData:(NSData *)pplData readOnly:(BOOL)readOnly;

+ (NSDictionary *)propertyListWithPPLData:(NSData *)pplData;
- (NSData *)contentsAsData;

- (NSMutableDictionary *)rootDictionary;

- (void)detachFromFile;
- (void)flush;
- (void)pushChangesToDisk;
- (void)save;
- (void)setCacheHalfLife:(NSTimeInterval)halfLife;

@end

#endif /* !STRICT_OPENSTEP */
