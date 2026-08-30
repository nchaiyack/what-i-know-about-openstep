/*	NSDateFormatter.h
	Copyright (c) 1995-1996, NeXT Software, Inc, All rights reserved.
*/

#ifndef STRICT_OPENSTEP

#import <Foundation/NSFormatter.h>

@class NSString;

@interface NSDateFormatter : NSFormatter {
@private
    NSString *_format;
    BOOL _naturalLanguage;
    int _reserved;
}

- (id)initWithDateFormat:(NSString *)format allowNaturalLanguage:(BOOL)flag;
- (NSString *)dateFormat;
- (BOOL)allowsNaturalLanguage;

@end

#endif
