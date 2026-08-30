/*	NSDictionary.h
	Hashed collection mapping object keys to object values
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray, NSEnumerator, NSString;

/****************	Immutable Dictionary	****************/

@interface NSDictionary : NSObject <NSCopying, NSMutableCopying, NSCoding>

- (unsigned)count;
- (NSEnumerator *)keyEnumerator;
- (id)objectForKey:(id)aKey;

@end

@interface NSDictionary (NSExtendedDictionary)

- (NSArray *)allKeys;
- (NSArray *)allKeysForObject:(id)anObject;    
- (NSArray *)allValues;
- (NSString *)description;
- (NSString *)descriptionInStringsFileFormat;
- (NSString *)descriptionWithLocale:(NSDictionary *)locale;
- (NSString *)descriptionWithLocale:(NSDictionary *)locale indent:(unsigned)level;
- (BOOL)isEqualToDictionary:(NSDictionary *)otherDictionary;
- (NSEnumerator *)objectEnumerator;
- (NSArray *)objectsForKeys:(NSArray *)keys notFoundMarker:(id)marker;
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;

#if !defined(STRICT_OPENSTEP)
- (NSArray *)keysSortedByValueUsingSelector:(SEL)comparator;
#endif /* !STRICT_OPENSTEP */

@end

@interface NSDictionary (NSDictionaryCreation)

+ (id)dictionary;
+ (id)dictionaryWithContentsOfFile:(NSString *)path;
+ (id)dictionaryWithObjects:(NSArray *)objects forKeys:(NSArray *)keys;
+ (id)dictionaryWithObjects:(id *)objects forKeys:(id *)keys count:(unsigned)count;
+ (id)dictionaryWithObjectsAndKeys:(id)firstObject, ...;
- (id)initWithContentsOfFile:(NSString *)path;
- (id)initWithObjects:(NSArray *)objects forKeys:(NSArray *)keys;
- (id)initWithObjects:(id *)objects forKeys:(id *)keys count:(unsigned)count;
- (id)initWithObjectsAndKeys:(id)firstObject, ...;
- (id)initWithDictionary:(NSDictionary *)otherDictionary;

#if !defined(STRICT_OPENSTEP)
+ (id)dictionaryWithDictionary:(NSDictionary *)dict;
+ (id)dictionaryWithObject:(id)object forKey:(id)key;
- (id)initWithDictionary:(NSDictionary *)otherDictionary copyItems:(BOOL)aBool;
#endif /* !STRICT_OPENSTEP */

@end

/****************	Mutable Dictionary	****************/

@interface NSMutableDictionary : NSDictionary

- (void)removeObjectForKey:(id)aKey;
- (void)setObject:(id)anObject forKey:(id)aKey;

@end

@interface NSMutableDictionary (NSExtendedMutableDictionary)

- (void)addEntriesFromDictionary:(NSDictionary *)otherDictionary;
- (void)removeAllObjects;
- (void)removeObjectsForKeys:(NSArray *)keyArray;
- (void)setDictionary:(NSDictionary *)otherDictionary;

@end

@interface NSMutableDictionary (NSMutableDictionaryCreation)

+ (id)dictionaryWithCapacity:(unsigned)numItems;
- (id)initWithCapacity:(unsigned)numItems;

@end

