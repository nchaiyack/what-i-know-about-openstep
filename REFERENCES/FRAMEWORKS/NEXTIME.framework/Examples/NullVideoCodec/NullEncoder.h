
#import <NEXTIME/NTSampleProcessor.h>
					
@interface NullEncoder: NTSampleProcessor
{
    int width, height;		/* compressed width and height */
    NSMutableDictionary * sampleDescription;
}
@end

