
#import <NEXTIME/NTSampleProcessor.h>
					

@interface NullDecoder: NTSampleProcessor
{
    int sWidth, sHeight;	/* source width and height */
    int dWidth, dHeight;	/* dest width and height */
    NSMutableDictionary * sampleDescription;
    NSMutableData *frameBuffer;
}

@end

