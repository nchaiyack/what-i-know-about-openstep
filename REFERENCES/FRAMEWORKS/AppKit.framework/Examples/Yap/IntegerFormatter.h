#import <Foundation/NSFormatter.h>

@interface IntegerFormatter : NSFormatter {
    int _min, _max;
}
- (id)initWithMinValue:(int)min maxValue:(int)max;
- (int)minValue;
- (int)maxValue;
@end
