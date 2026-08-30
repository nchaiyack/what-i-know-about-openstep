/*	NXBundle.h
	Copyright 1990, 1991, 1996, NeXT Software Inc.
	Utilities for dynamic loading and internationalization.
	IPC, November 1990
*/

#ifndef _OBJC_NXBUNDLE_H_
#define _OBJC_NXBUNDLE_H_

#import <objc/Object.h>

@interface NXBundle: Object {
@private
    char	*_directory;
    Class	_principalClass;
    BOOL	_codeLoaded;
    BOOL	_reserved1, _reserved2, _reserved3;
    int		_bundleVersion;
}

- initForDirectory:(const char *)path;
+ mainBundle;
+ bundleForClass:theClass;
- (const char *)directory;
- classNamed:(const char *)className;
- principalClass;
- setVersion:(int)version;
- (int)version;
- free;
+ (BOOL)getPath:(char *)path forResource:(const char *)name
         ofType:(const char *)ext inDirectory: (const char *)bundlePath
    withVersion: (int)version;
- (BOOL)getPath:(char *)path forResource:(const char *)name ofType:(const char *)ext;
+ setSystemLanguages:(const char * const *)languages;
@end

#define NXLocalString(key, value, comment) \
    NXLoadLocalStringFromTableInBundle(NULL, nil, key, value)
#define NXLocalStringFromTable(table, key, value, comment) \
    NXLoadLocalStringFromTableInBundle(table, nil, key, value)
#define NXLocalStringFromTableInBundle(table, bundle, key, value, comment) \
    NXLoadLocalStringFromTableInBundle(table, bundle, key, value)

#define NXLocalizedString(key, value, comment) \
    NXLoadLocalizedStringFromTableInBundle(NULL, nil, key, value)
#define NXLocalizedStringFromTable(table, key, value, comment) \
    NXLoadLocalizedStringFromTableInBundle(table, nil, key, value)
#define NXLocalizedStringFromTableInBundle(table, bundle, key, value, comment) \
    NXLoadLocalizedStringFromTableInBundle(table, bundle, key, value)

extern const char *NXLoadLocalStringFromTableInBundle(const char *table, NXBundle *bundle, const char *key, const char *value);
extern const char *NXLoadLocalizedStringFromTableInBundle(const char *table, NXBundle *bundle, const char *key, const char *value);

#endif /* _OBJC_NXBUNDLE_H_ */
