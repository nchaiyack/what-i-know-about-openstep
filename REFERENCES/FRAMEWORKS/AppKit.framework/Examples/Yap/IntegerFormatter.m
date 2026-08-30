/*
 *  IntegerFormatter.m
 *  Author: Garrick Toubassi
 *  Modified: Jan 96 for Yap, Ali Ozer
 *
 *  Very simple integer formatter. Allows formatting and validating integers in a given range.
 *
 *  You may freely copy, distribute and reuse the code in this example.
 *  NeXT disclaims any warranty of any kind, expressed or implied,
 *  as to its fitness for any particular use.
 */

#import <AppKit/AppKit.h>
#import "IntegerFormatter.h"
#import <limits.h>

@implementation IntegerFormatter

- (id)init {
    return [self initWithMinValue:INT_MIN maxValue:INT_MAX];
}

- (id)initWithMinValue:(int)min maxValue:(int)max {
    if (self = [super init]) {
	_min = min;
	_max = max;
    }
    return self;
}

- (int)minValue {
    return _min;
}

- (int)maxValue {
    return _max;
}

- (NSString *)stringForObjectValue:(id)obj {
    if (![obj isKindOfClass:[NSNumber class]]) return nil;
    return [NSString localizedStringWithFormat:@"%d", [obj intValue]];
}

- (BOOL)getObjectValue:(id *)obj forString:(NSString *)string errorDescription:(NSString **)error {
    int intResult;
    NSScanner *scanner = [NSScanner localizedScannerWithString:string];
    NSString *err = nil;

    if ([scanner scanInt:&intResult]) {
        if ([scanner isAtEnd]) {
            if (intResult < _min || intResult > _max) {
                err = NSLocalizedStringFromTable(@"Value out of allowed range", @"IntegerFormatter", @"Message shown when an integer that is out of range is entered by the user.");
            } else {
                if (obj) *obj = [NSNumber numberWithInt:intResult];
            }
        } else {
            err = NSLocalizedStringFromTable(@"Junk at end", @"IntegerFormatter", @"Message shown the integer entered by the user has extra characters at the end.");
        }
    } else {
        err = NSLocalizedStringFromTable(@"Need an integer", @"IntegerFormatter", @"Message shown when the user's input is not an integer");
    }
    if (err && error) *error = err;
    return err ? NO : YES;
}

@end

