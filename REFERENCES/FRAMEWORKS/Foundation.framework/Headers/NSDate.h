/*	NSDate.h
	Primitives for manipulating time
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSArray, NSDictionary, NSCalendarDate, NSTimeZone, NSTimeZoneDetail;

typedef double NSTimeInterval;

#define NSTimeIntervalSince1970  978307200.0L

@interface NSDate : NSObject <NSCopying, NSCoding>

- (NSTimeInterval)timeIntervalSinceReferenceDate;

@end

@interface NSDate (NSExtendedDate)

- (NSTimeInterval)timeIntervalSinceDate:(NSDate *)anotherDate;
- (NSTimeInterval)timeIntervalSinceNow;
- (NSTimeInterval)timeIntervalSince1970;

- (id)addTimeInterval:(NSTimeInterval)seconds;

- (NSDate *)earlierDate:(NSDate *)anotherDate;
- (NSDate *)laterDate:(NSDate *)anotherDate;
- (NSComparisonResult)compare:(NSDate *)other;

- (NSString *)description;
- (BOOL)isEqualToDate:(NSDate *)otherDate;

+ (NSTimeInterval)timeIntervalSinceReferenceDate;
    
@end

@interface NSDate (NSDateCreation)

+ (id)date;
    
+ (id)dateWithTimeIntervalSinceNow:(NSTimeInterval)secs;    
+ (id)dateWithTimeIntervalSinceReferenceDate:(NSTimeInterval)secs;
+ (id)dateWithTimeIntervalSince1970:(NSTimeInterval)secs;

+ (id)distantFuture;
+ (id)distantPast;

- (id)init;
- (id)initWithTimeIntervalSinceReferenceDate:(NSTimeInterval)secsToBeAdded;
- (id)initWithTimeInterval:(NSTimeInterval)secsToBeAdded sinceDate:(NSDate *)anotherDate;
- (id)initWithTimeIntervalSinceNow:(NSTimeInterval)secsToBeAddedToNow;

@end

/*******	Conveniences to deal with Western calendar	*******/

@interface NSDate (NSCalendarDateExtras)

#if !defined(STRICT_OPENSTEP)
+ (id)dateWithString:(NSString *)aString;
#endif /* !STRICT_OPENSTEP */

- (id)initWithString:(NSString *)description;

- (NSCalendarDate *)dateWithCalendarFormat:(NSString *)format timeZone:(NSTimeZone *)aTimeZone;

- (NSString *)descriptionWithLocale:(NSDictionary *)locale;

- (NSString *)descriptionWithCalendarFormat:(NSString *)format timeZone:(NSTimeZone *)aTimeZone locale:(NSDictionary *)locale;

@end

#if !defined(STRICT_OPENSTEP)

@interface NSDate (NSNaturalLangage)

+ dateWithNaturalLanguageString:(NSString *)string;
+ dateWithNaturalLanguageString:(NSString *)string locale:(NSDictionary *)dict;

@end

#endif /* !STRICT_OPENSTEP */

@interface NSTimeZone : NSObject <NSCopying, NSCoding>

+ (void)setDefaultTimeZone:(NSTimeZone *)aTimeZone;
+ (NSTimeZoneDetail *)defaultTimeZone;

+ (NSTimeZone *)localTimeZone;

+ (NSDictionary *)abbreviationDictionary;

+ (NSArray *)timeZoneArray;

+ (NSTimeZone *)timeZoneWithName:(NSString *)aTimeZoneName;
+ (NSTimeZoneDetail *)timeZoneWithAbbreviation:(NSString *)abbreviation;
+ (NSTimeZone *)timeZoneForSecondsFromGMT:(int)seconds;

- (NSString *)timeZoneName;
- (NSArray *)timeZoneDetailArray;
- (NSTimeZoneDetail *)timeZoneDetailForDate:(NSDate *)date;

@end

@interface NSTimeZoneDetail : NSTimeZone

- (int)timeZoneSecondsFromGMT;
- (NSString *)timeZoneAbbreviation;
- (BOOL)isDaylightSavingTimeZone;

@end

@interface NSCalendarDate : NSDate {
    unsigned		refCount;
    NSTimeInterval 	_timeIntervalSinceReferenceDate;
    NSTimeZoneDetail 	*_timeZone;
    NSString 		*_formatString;
    void		*_reserved;
}

+ (id)dateWithYear:(int)year month:(unsigned)month day:(unsigned)day hour:(unsigned)hour minute:(unsigned)minute second:(unsigned)second timeZone:(NSTimeZone *)aTimeZone;

+ (id)dateWithString:(NSString *)description calendarFormat:(NSString *)format;

+ (id)dateWithString:(NSString *)description calendarFormat:(NSString *)format locale:(NSDictionary *)dict;

+ (id)calendarDate;

- (id)initWithYear:(int)year month:(unsigned)month day:(unsigned)day hour:(unsigned)hour minute:(unsigned)minute second:(unsigned)second timeZone:(NSTimeZone *)aTimeZone;
    
- (id)initWithString:(NSString *)description;
- (id)initWithString:(NSString *)description calendarFormat:(NSString *)format;

- (id)initWithString:(NSString *)description calendarFormat:(NSString *)format locale:(NSDictionary *)dict;

- (NSTimeZoneDetail *)timeZoneDetail;
- (void)setTimeZone:(NSTimeZone *)aTimeZone;

- (NSString *)calendarFormat;
- (void)setCalendarFormat:(NSString *)format;

- (int)yearOfCommonEra;
- (int)monthOfYear;
- (int)dayOfMonth;
- (int)dayOfWeek;
- (int)dayOfYear;
- (int)dayOfCommonEra;
- (int)hourOfDay;
- (int)minuteOfHour;
- (int)secondOfMinute;

- (NSCalendarDate *)dateByAddingYears:(int)year months:(int)month days:(int)day hours:(int)hour minutes:(int)minute seconds:(int)second;

- (void)years:(int *)yp months:(int *)mop days:(int *)dp hours:(int *)hp minutes:(int *)mip seconds:(int *)sp sinceDate:(NSCalendarDate *)date;

- (NSString *)description;
- (NSString *)descriptionWithLocale:(NSDictionary *)locale;
- (NSString *)descriptionWithCalendarFormat:(NSString *)format;
- (NSString *)descriptionWithCalendarFormat:(NSString *)format locale:(NSDictionary *)locale;

@end

