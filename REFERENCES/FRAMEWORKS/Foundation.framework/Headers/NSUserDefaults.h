/*	NSUserDefaults.h
	Storage and retrieval of user defaults
	Copyright 1994-1996, NeXT Software, Inc.  All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray, NSData, NSDictionary, NSMutableArray, NSString;

FOUNDATION_EXPORT NSString *NSGlobalDomain;
FOUNDATION_EXPORT NSString *NSArgumentDomain;
FOUNDATION_EXPORT NSString *NSRegistrationDomain;

@interface NSUserDefaults : NSObject {
    id			_dlplf;
    NSArray		*_search;
    NSDictionary	*_temp;
    NSDictionary 	*_dictRep;
    void		*_reserved;
}

+ (NSUserDefaults *)standardUserDefaults;

- (id)init;
- (id)initWithUser:(NSString *)username;

- (id)objectForKey:(NSString *)defaultName;
- (void)setObject:(id)value forKey:(NSString *)defaultName;
- (void)removeObjectForKey:(NSString *)defaultName;

- (NSString *)stringForKey:(NSString *)defaultName;
- (NSArray *)arrayForKey:(NSString *)defaultName;
- (NSDictionary *)dictionaryForKey:(NSString *)defaultName;
- (NSData *)dataForKey:(NSString *)defaultName;
- (NSArray *)stringArrayForKey:(NSString *)defaultName;
- (int)integerForKey:(NSString *)defaultName; 
- (float)floatForKey:(NSString *)defaultName; 
- (BOOL)boolForKey:(NSString *)defaultName;  

- (void)setInteger:(int)value forKey:(NSString *)defaultName;
- (void)setFloat:(float)value forKey:(NSString *)defaultName;
- (void)setBool:(BOOL)value forKey:(NSString *)defaultName;

- (NSArray *)searchList;
- (void)setSearchList:(NSArray *)array;

- (void)registerDefaults:(NSDictionary *)registrationDictionary;

- (NSDictionary *)dictionaryRepresentation;

- (NSArray *)volatileDomainNames;
- (NSDictionary *)volatileDomainForName:(NSString *)domainName;
- (void)setVolatileDomain:(NSDictionary *)domain forName:(NSString *)domainName;
- (void)removeVolatileDomainForName:(NSString *)domainName;

- (NSArray *)persistentDomainNames;
- (NSDictionary *)persistentDomainForName:(NSString *)domainName;
- (void)setPersistentDomain:(NSDictionary *)domain forName:(NSString *)domainName;
- (void)removePersistentDomainForName:(NSString *)domainName;

- (BOOL)synchronize;

@end

FOUNDATION_EXPORT NSString *NSUserDefaultsDidChangeNotification;

FOUNDATION_EXPORT NSString *NSWeekDayNameArray;
FOUNDATION_EXPORT NSString *NSShortWeekDayNameArray;
FOUNDATION_EXPORT NSString *NSMonthNameArray;
FOUNDATION_EXPORT NSString *NSShortMonthNameArray;
FOUNDATION_EXPORT NSString *NSTimeFormatString;
FOUNDATION_EXPORT NSString *NSDateFormatString;
FOUNDATION_EXPORT NSString *NSTimeDateFormatString;
FOUNDATION_EXPORT NSString *NSShortTimeDateFormatString;
FOUNDATION_EXPORT NSString *NSCurrencySymbol;
FOUNDATION_EXPORT NSString *NSDecimalSeparator;
FOUNDATION_EXPORT NSString *NSThousandsSeparator;
FOUNDATION_EXPORT NSString *NSDecimalDigits;
FOUNDATION_EXPORT NSString *NSAMPMDesignation;
FOUNDATION_EXPORT NSString *NSHourNameDesignations;
FOUNDATION_EXPORT NSString *NSYearMonthWeekDesignations;
FOUNDATION_EXPORT NSString *NSEarlierTimeDesignations;
FOUNDATION_EXPORT NSString *NSLaterTimeDesignations;
FOUNDATION_EXPORT NSString *NSThisDayDesignations;
FOUNDATION_EXPORT NSString *NSNextDayDesignations;
FOUNDATION_EXPORT NSString *NSNextNextDayDesignations;
FOUNDATION_EXPORT NSString *NSPriorDayDesignations;
FOUNDATION_EXPORT NSString *NSDateTimeOrdering;
FOUNDATION_EXPORT NSString *NSInternationalCurrencyString;

#if !defined(STRICT_OPENSTEP)

FOUNDATION_EXPORT NSString *NSShortDateFormatString;

#if !defined(STRICT_41) && !defined(STRICT_40)
FOUNDATION_EXPORT NSString *NSPositiveCurrencyFormatString;
FOUNDATION_EXPORT NSString *NSNegativeCurrencyFormatString;
#endif

#endif /* !STRICT_OPENSTEP */

