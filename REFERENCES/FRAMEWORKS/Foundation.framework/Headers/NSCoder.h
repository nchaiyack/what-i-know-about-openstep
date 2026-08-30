/*      NSCoder.h
	Abstract class for serializing arbitrary objects
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSData;

/****************** Basic functionality **********************/

@interface NSCoder : NSObject

- (void)encodeValueOfObjCType:(const char *)type at:(const void *)addr;
- (void)encodeDataObject:(NSData *)data;
- (void)decodeValueOfObjCType:(const char *)type at:(void *)data;
- (NSData *)decodeDataObject;
- (unsigned)versionForClassName:(NSString *)className;

@end

@interface NSCoder (NSExtendedCoder)
    
- (void)encodeObject:(id)object;
- (void)encodePropertyList:(id)aPropertyList;
- (void)encodeRootObject:(id)rootObject;
- (void)encodeBycopyObject:(id)anObject;

#if !defined(STRICT_OPENSTEP)

- (void)encodeByrefObject:(id)anObject;

#endif

- (void)encodeConditionalObject:(id)object;
- (void)encodeValuesOfObjCTypes:(const char *)types, ...;
- (void)encodeArrayOfObjCType:(const char *)type count:(unsigned)count at:(const void *)array;
- (void)encodeBytes:(void *)byteaddr length:(unsigned)length;

- (id)decodeObject;
- (id)decodePropertyList;
- (void)decodeValuesOfObjCTypes:(const char *)types, ...;
- (void)decodeArrayOfObjCType:(const char *)itemType count:(unsigned)count at:(void *)array;
- (void *)decodeBytesWithReturnedLength:(unsigned *)lengthp;

- (void)setObjectZone:(NSZone *)zone;
- (NSZone *)objectZone;

- (unsigned)systemVersion;

@end

