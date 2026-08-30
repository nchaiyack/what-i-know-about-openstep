/*	NSNumberFormatter.h
	Copyright 1996, NeXT Software, Inc.  All rights reserved.
*/

#if !defined(STRICT_OPENSTEP)

#import <Foundation/NSFormatter.h>

@class NSDecimalNumber, NSAttributedString, NSDictionary, NString;
@class NSDecimalNumberHandler;

@interface NSNumberFormatter : NSFormatter {
@private
    NSString               *_negativeFormat;
    NSString               *_positiveFormat;
    NSDictionary           *_negativeAttributes;
    NSDictionary    	   *_positiveAttributes;
    NSAttributedString     *_attributedStringForZero;
    NSAttributedString     *_attributedStringForNil;
    NSAttributedString     *_attributedStringForNotANumber; 
    NSDecimalNumber        *_minimum;
    NSDecimalNumber        *_maximum;
    NSDecimalNumberHandler *_roundingBehavior;
    NSString               *_decimalSeparator;
    NSString               *_thousandSeparator;
    void                   *_private;
    struct {
	unsigned int thousandSeparators:1;
	unsigned int localizesFormat:1;
	unsigned int allowsFloats:1;
	unsigned int RESERVED:29;
    } _flags;
    
    void *_reserved;
}

- (NSString *)negativeFormat;
- (void)setNegativeFormat:(NSString *)format;
- (NSDictionary *)textAttributesForNegativeValues;
- (void)setTextAttributesForNegativeValues:(NSDictionary *)newAttributes;

- (NSString *)positiveFormat;
- (void)setPositiveFormat:(NSString *)format;
- (NSDictionary *)textAttributesForPositiveValues;
- (void)setTextAttributesForPositiveValues:(NSDictionary *)newAttributes;

- (NSAttributedString *)attributedStringForZero;
- (void)setAttributedStringForZero:(NSAttributedString *)newAttributedString;
- (NSAttributedString *)attributedStringForNil;
- (void)setAttributedStringForNil:(NSAttributedString *)newAttributedString;
- (NSAttributedString *)attributedStringForNotANumber;
- (void)setAttributedStringForNotANumber:(NSAttributedString *)newAttributedString;

- (NSString *)format;
- (void)setFormat:(NSString *)format;

    // The formatter string can consist of one, two or three parts separated
    // by ';'. If the caller specifies three parts, the center part is used
    // to set the attributedStringForZero. The center part is always a string
    // constant. If attributedStringForZero has not been explicitly set, with
    // -setAttributedStringForZero, zeros are formatted with the positive
    // format.

- (BOOL)hasThousandSeparators;
- (void)setHasThousandSeparators:(BOOL)flag;
- (NSString *)thousandSeparator;
- (void)setThousandSeparator:(NSString *)newSeparator;

- (NSString *)decimalSeparator;
- (void)setDecimalSeparator:(NSString *)newSeparator;

- (BOOL)localizesFormat;
- (void)setLocalizesFormat:(BOOL)flag;

- (BOOL)allowsFloats;
- (void)setAllowsFloats:(BOOL)flag;

- (NSDecimalNumberHandler *)roundingBehavior;
- (void)setRoundingBehavior:(NSDecimalNumberHandler *)newRoundingBehavior;

- (NSDecimalNumber *)minimum;
- (void)setMinimum:(NSDecimalNumber *)aMinimum;
- (NSDecimalNumber *)maximum;
- (void)setMaximum:(NSDecimalNumber *)aMaximum;

@end

#endif
