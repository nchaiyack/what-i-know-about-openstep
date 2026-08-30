/*	NSRange.h
	Range utilities
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/

#import <Foundation/NSObjCRuntime.h>

@class NSString;

typedef struct _NSRange {
    unsigned int location;
    unsigned int length;
} NSRange;

static __inline__ NSRange NSMakeRange(unsigned int loc, unsigned int len) {
    NSRange r;
    r.location = loc;
    r.length = len;
    return r;
}

static __inline__ unsigned int NSMaxRange(NSRange range) {
    return (range.location + range.length);
}

static __inline__ BOOL NSLocationInRange(unsigned int loc, NSRange range) {
    return (range.location <= loc && loc < range.location + range.length);
}

static __inline__ BOOL NSEqualRanges(NSRange range1, NSRange range2) {
    return (range1.location == range2.location && range1.length == range2.length);
}

FOUNDATION_EXPORT NSRange NSUnionRange(NSRange range1, NSRange range2);
FOUNDATION_EXPORT NSRange NSIntersectionRange(NSRange range1, NSRange range2);
FOUNDATION_EXPORT NSString *NSStringFromRange(NSRange range);
FOUNDATION_EXPORT NSRange NSRangeFromString(NSString *aString);
