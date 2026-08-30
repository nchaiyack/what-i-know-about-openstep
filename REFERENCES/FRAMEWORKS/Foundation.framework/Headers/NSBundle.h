/*	NSBundle.h
	Dynamically loadable code with resources
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray, NSDictionary, NSString;

/* Because NSBundle caches allocated instances, subclasses should be prepared
   to receive an already initialized object back from [super initWithPath:] */
@interface NSBundle : NSObject {
@private
    struct {
	unsigned int	_externRetain : 1;
	unsigned int	_retainCount : 7;
	unsigned int	_bundleType : 3;
	unsigned int	_codeLoaded : 1;
	unsigned int	_codeAttempted : 1;
	unsigned int	_init : 1;
	unsigned int	_reserved : 18;
    }			_flags;
    id			_infoDictionary;
    void		*_classes;
    Class		_principalClass;
    void		*_tmp1;
    void		*_tmp2;
    void		*_reserved1;
    void		*_reserved;
}

+ (NSBundle *)mainBundle;
+ (NSBundle *)bundleWithPath:(NSString *)path;
- (id)initWithPath:(NSString *)path;

+ (NSBundle *)bundleForClass:(Class)aClass;

#if !defined(STRICT_OPENSTEP) && !defined(STRICT_40)
+ (NSArray *)allBundles;
+ (NSArray *)allFrameworks;
#endif

- (NSString *)bundlePath;
- (NSString *)resourcePath;

- (Class)classNamed:(NSString *)className;

- (Class)principalClass;

#if !defined(STRICT_OPENSTEP) && !defined(STRICT_40)
- (BOOL)load;
#endif

+ (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext inDirectory:(NSString *)path;
- (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext;
- (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext inDirectory:(NSString *)subpath;

- (NSArray *)pathsForResourcesOfType:(NSString *)ext inDirectory:(NSString *)subpath;

- (NSString *)localizedStringForKey:(NSString *)key value:(NSString *)value table:(NSString *)tableName;

#if !defined(STRICT_OPENSTEP)

- (NSDictionary *)infoDictionary;

#endif /* !STRICT_OPENSTEP */

@end

#define NSLocalizedString(key, comment) \
	    [[NSBundle mainBundle] localizedStringForKey:(key) value:@"" table:nil]
#define NSLocalizedStringFromTable(key, tbl, comment) \
	    [[NSBundle mainBundle] localizedStringForKey:(key) value:@"" table:(tbl)]
#define NSLocalizedStringFromTableInBundle(key, tbl, bundle, comment) \
	    [bundle localizedStringForKey:(key) value:@"" table:(tbl)]

FOUNDATION_EXPORT NSString *NSBundleDidLoadNotification;
FOUNDATION_EXPORT NSString *NSLoadedClasses;	// notification key

