/*	NSAttributedString.h
	Combines a string with arbitrary attributes assigned to ranges of characters within the string.
	Copyright (c) 1994-1996, NeXT Software, Inc, All rights reserved.
*/

#ifndef STRICT_OPENSTEP

#import <Foundation/NSString.h>
#import <Foundation/NSDictionary.h>

/**** NSAttributedString, an abstract class ****/
   
@interface NSAttributedString : NSObject <NSCopying, NSMutableCopying, NSCoding>		/* The primitive methods */
- (NSString *)string;
- (NSDictionary *)attributesAtIndex:(unsigned)location effectiveRange:(NSRange *)range; /* Can pass NULL for range. Note that range isn't necessarily the longest range for which the attribute values are the same. */
@end

@interface NSAttributedString (NSExtendedAttributedString)
- (unsigned)length;
- (id)attribute:(NSString *)attrName atIndex:(unsigned int)location effectiveRange:(NSRange *)range; /* Can pass NULL for range. Note that range isn't necessarily the longest range for which the attribute is the same. */
- (NSAttributedString *)attributedSubstringFromRange:(NSRange)range;

/* These methods are the same as attributesAtIndex:effectiveRange: & attribute:atIndex:effectiveRange:; but they compute the longest effective range where the attributes values are the same. Use rangeLimit to limit the search area. The resulting range is clipped to this value.
*/
- (NSDictionary *)attributesAtIndex:(unsigned)location longestEffectiveRange:(NSRange *)range inRange:(NSRange)rangeLimit;
- (id)attribute:(NSString *)attrName atIndex:(unsigned int)location longestEffectiveRange:(NSRange *)range inRange:(NSRange)rangeLimit;

- (BOOL)isEqualToAttributedString:(NSAttributedString *)other;

/* There are no abstract implementations of these init methods; you may optionally implement them in your concrete subclasses. 
*/
- (id)initWithString:(NSString *)str;
- (id)initWithString:(NSString *)str attributes:(NSDictionary *)attrs;
- (id)initWithAttributedString:(NSAttributedString *)attrStr;

@end


/**** NSMutableAttributedString, an abstract class ****/

@interface NSMutableAttributedString : NSAttributedString	/* The primitive methods */
- (void)replaceCharactersInRange:(NSRange)range withString:(NSString *)str; /* The newly inserted characters have the attributes of the first replaced character; if none replaced, those of the previous character; if none, from the next character */
- (void)setAttributes:(NSDictionary *)attrs range:(NSRange)range; /* Replaces all attributes in the range */
@end


@interface NSMutableAttributedString (NSExtendedMutableAttributedString)
- (NSMutableString *)mutableString; /* Deal with the string using the mutable string protocol */

- (void)addAttribute:(NSString *)name value:(id)value range:(NSRange)range;	/* Change one attribute */
- (void)addAttributes:(NSDictionary *)attrs range:(NSRange)range; /* Change a bunch of attributes */
- (void)removeAttribute:(NSString *)name range:(NSRange)range; /* Remove one attribute */

- (void)replaceCharactersInRange:(NSRange)range withAttributedString:(NSAttributedString *)attrString;
- (void)insertAttributedString:(NSAttributedString *)attrString atIndex:(unsigned)loc;
- (void)appendAttributedString:(NSAttributedString *)attrString;
- (void)deleteCharactersInRange:(NSRange)range;
- (void)setAttributedString:(NSAttributedString *)attrString;	/* Replace the whole thing */

/* Subclasses interested in hearing about changes need to implement these methods. Default implementations of these do nothing. All methods which change the attributed string using multiple calls should call these messages to coalesce any post-editing processes.
*/
- (void)beginEditing;
- (void)endEditing;

@end

#endif
