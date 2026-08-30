/*	NSFormatter.h
	Copyright (c) 1995-1996, NeXT Software, Inc, All rights reserved.
*/

#ifndef STRICT_OPENSTEP

#import <Foundation/NSObject.h>

@class NSString;
@class NSAttributedString;
@class NSDictionary;

@interface NSFormatter : NSObject <NSCopying, NSCoding>

- (NSString *)stringForObjectValue:(id)obj;
    // Raises NSInvalidArgumentException

- (NSAttributedString *)attributedStringForObjectValue:(id)obj withDefaultAttributes:(NSDictionary *)attrs;
    // Returns nil, indicating that this formatter does not provide an attributed string for obj.

- (NSString *)editingStringForObjectValue:(id)obj;
    // Returns [self stringForObjectValue:obj];

- (BOOL)getObjectValue:(id *)obj forString:(NSString *)string errorDescription:(NSString **)error;
    // Raises NSInvalidArgumentException

- (BOOL)isPartialStringValid:(NSString *)partialString newEditingString:(NSString **)newString errorDescription:(NSString **)error;
    // Returns YES

@end

#endif
