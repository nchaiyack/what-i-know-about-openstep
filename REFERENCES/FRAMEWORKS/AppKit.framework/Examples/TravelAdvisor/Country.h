
#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

@interface Country : NSObject <NSCoding>
{
    NSString *name;
    NSString *airports;
    NSString *airlines;
    NSString *transportation;
    NSString *hotels;
    NSString *languages;
    BOOL     englishSpoken;
    NSString *currencyName;
    float currencyRate;
    NSString *comments;
}

- (id)init;
- (void)dealloc;
- (void)encodeWithCoder:(NSCoder *)coder;
- (id)initWithCoder:(NSCoder *)coder;

/* accessor methods */
- (NSString *)name;
- (void)setName:(NSString *)str;
- (NSString *)airports;
- (void)setAirports:(NSString *)str;
- (NSString *)airlines;
- (void)setAirlines:(NSString *)str;
- (NSString *)transportation;
- (void)setTransportation:(NSString *)str;
- (NSString *)hotels;
- (void)setHotels:(NSString *)str;
- (NSString *)languages;
- (void)setLanguages:(NSString *)str;
- (BOOL)englishSpoken;
- (void)setEnglishSpoken:(BOOL)flag;
- (NSString *)currencyName;
- (void)setCurrencyName:(NSString *)str;
- (float)currencyRate;
- (void)setCurrencyRate:(float)val;
- (NSString *)comments;
- (void)setComments:(NSString *)str;

@end
