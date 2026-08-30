/*
 *  NTValueDictionary.h
 * 	Copyright 1994, NeXT Computer, Inc.
 *	
 *	Extensions on NSDictionary and NSMutableDictionary to support
 *	keyed storage of values.  Since we do these operations in hundreds
 *	of places in NEXTIME, the code is implemented once, as a category
 *	on NSDictionary and NSMutableDictionary.
 *
 *	10 Jan 1994 mpaque Created.
 *	07 Oct 1994 mpaque Ported to Foundation
 */
#import <Foundation/NSDictionary.h>

@interface NSDictionary(NEXTIME_Extensions)
// Comparisons
- (BOOL)isKeyKnown:(id)key;	// Returns YES if key exists in dict.

- (BOOL)isSubset:other;
    /* Checks if other isKindOf NTValueDictionary;
    If conforming, each item in messaged dictionary is compared */

// Queries for value by key
- (const char *)cStringForKey:(id)key;
    /* Returns a C string owned by the dictionary, or NULL if the 
       key is not found or the object does not have a string representation */
       
- (NSString *)stringForKey:(id)key;
    /* Returns a NSString owned by the dictionary, or nil if the 
       key is not found or the object is not an NSString kind. */
       
- (BOOL)boolForKey:(id)key;
    /*	Returns boolean value, or NO if key is not found or object does
    	not have a boolean or numeric representation. */

- (int)integerForKey:(id)key;
    /*	Returns integer value, or 0 if key is not found or object does
    	not have a numeric representation. */
	
- (float)floatForKey:(id)key;
- (double)doubleForKey:(id)key;
    /*	Returns floating point value, or 0.0 (NaN?) if key is not
    	found or object does not have a numeric representation. */

// Variations which raise an exception if the key is not found or
// the object cannot produce the desired value type.
- (id)requiredObjectForKey:(id)key;
- (const char *)requiredCStringForKey:(id)key;       
- (NSString *)requiredStringForKey:(id)key;       
- (BOOL)requiredBoolForKey:(id)key;
- (int)requiredIntForKey:(id)key;
- (float)requiredFloatForKey:(id)key;
- (double)requiredDoubleForKey:(id)key;
@end

@interface NSMutableDictionary(NEXTIME_Extensions)
// Setting a keyed value.  The key and value are always retained or copied
// Data for old keys are dereferenced.
- (void)setCString:(const char *)value forKey:(id)key;
- (void)setString:(NSString *)value forKey:(id)key;
- (void)setBool:(BOOL)value forKey:(id)key;
- (void)setInteger:(int)value forKey:(id)key;
- (void)setFloat:(float)value forKey:(id)key;
- (void)setDouble:(double)value forKey:(id)key;
@end
