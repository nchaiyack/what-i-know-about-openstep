#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>
#import <SoundKit/SoundKit.h>

@interface Converter : NSObject
{
}

- (float)convertAmount:(float)amt byRate:(float)rate;

@end
