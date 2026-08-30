#import <AppKit/AppKit.h>

@interface ConverterController : NSObject
{
    id converter;
    id dollarField;
    id rateField;
    id totalField;
}
- (void)convert:(id)sender;
@end
