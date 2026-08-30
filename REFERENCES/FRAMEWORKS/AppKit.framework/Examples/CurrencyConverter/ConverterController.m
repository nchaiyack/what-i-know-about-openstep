#import "ConverterController.h"
#import "Converter.h"

@implementation ConverterController

- (void)convert:(id)sender
{
   float rate, amt, total;

    amt = [dollarField floatValue];
    rate = [rateField floatValue];
    total = [converter convertAmount:amt byRate:rate];
    [totalField setFloatValue:total];
    [rateField selectText:self];
}

- (void)awakeFromNib
{
    [rateField selectText:self];
    [[rateField window] makeKeyAndOrderFront:self];
}

@end
