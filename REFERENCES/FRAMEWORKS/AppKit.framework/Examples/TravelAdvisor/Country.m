
#import "Country.h"

@implementation Country

- (id)init
{
    [super init];
    
    name=@"";
    airports=@"";
    airlines=@"";
    transportation=@"";
    hotels=@"";
    languages=@"";
    currencyName=@"";
    comments=@"";
    
    return self;
}
    
- (void)dealloc
{
    [name release];
    [airports release];
    [airlines release];
    [transportation release];
    [hotels release];
    [languages release];
    [currencyName release];
    [comments release];

    return [super dealloc];
}

- (void)encodeWithCoder:(NSCoder *)coder
{
    [coder encodeObject:name];
    [coder encodeObject:airports];
    [coder encodeObject:airlines];
    [coder encodeObject:transportation];
    [coder encodeObject:hotels];
    [coder encodeObject:languages];
    [coder encodeValueOfObjCType:"s" at:&englishSpoken];
    [coder encodeObject:currencyName];
    [coder encodeValueOfObjCType:"f" at:&currencyRate];
    [coder encodeObject:comments];
        
    return;
}

- (id)initWithCoder:(NSCoder *)coder
{
    name = [[coder decodeObject] copy];
    airports = [[coder decodeObject] copy];
    airlines = [[coder decodeObject] copy];
    transportation = [[coder decodeObject] copy];
    hotels = [[coder decodeObject] copy];
    languages = [[coder decodeObject] copy];
    [coder decodeValueOfObjCType:"s" at:&englishSpoken];
    currencyName = [[coder decodeObject] copy];
    [coder decodeValueOfObjCType:"f" at:&currencyRate];
    comments = [[coder decodeObject] copy];
    
    return self;
 }

/* accessor methods */
- (NSString *)name
{
    return name;
}

- (void)setName:(NSString *)str
{
    [name autorelease];
    name = [str copy];
}

- (NSString *)airports { return airports; }

- (void)setAirports:(NSString *)str
{
    [airports autorelease];
    airports = [str copy];
}

- (NSString *)airlines { return airlines; }

- (void)setAirlines:(NSString *)str
{
    [airlines autorelease];
    airlines = [str copy];
}

- (NSString *)transportation { return transportation; }

- (void)setTransportation:(NSString *)str
{
    [transportation autorelease];
    transportation = [str copy];
}

- (NSString *)hotels { return hotels; }

- (void)setHotels:(NSString *)str
{
    [hotels autorelease];
    hotels = [str copy];
}

- (NSString *)languages { return languages; }

- (void)setLanguages:(NSString *)str
{
    [languages autorelease];
    languages = [str copy];
}

- (BOOL)englishSpoken { return englishSpoken; }

- (void)setEnglishSpoken:(BOOL)flag
{
    englishSpoken = flag;
}

- (NSString *)currencyName { return currencyName; }

- (void)setCurrencyName:(NSString *)str
{
    [currencyName autorelease];
    currencyName = [str copy];
}

- (float)currencyRate {return currencyRate;}

- (void)setCurrencyRate:(float)val
{
    currencyRate = val;
}

- (NSString *)comments { return comments; }

- (void)setComments:(NSString *)str
{
    [comments autorelease];
    comments = [str copy];
}

@end
