
#import <architecture/byte_order.h>
#import "NullEncoder.h"
#import <NEXTIME/NTValueDictionary.h>
#import <NEXTIME/NTDictionaryKeys.h>
#import <NEXTIME/NTComponent.h>

#define NULLVIDEO_COMPONENT_VERSION		0
#define NULLVIDEO_COMPONENT_REVISION_LEVEL	0
#define NULLVIDEO_VENDOR			@"NeXT Computer, Inc."
#define NULLVIDEO_TEMPORAL_QUALITY		1.0
#define NULLVIDEO_SPATIAL_QUALITY		0.75
#define NULLVIDEO_HRES				72.0
#define NULLVIDEO_VRES				72.0
#define NULLVIDEO_BPP				32
#define NULLVIDEO_COLORSPACE			NSDeviceRGBColorSpace


@implementation NullEncoder

- (bycopy NSDictionary *) setConfiguration:
		(bycopy NSDictionary *) inconf 
{
    NSDictionary *output;
    NSMutableDictionary *input, *conf;
    NSString *pixelEncoding;

    output = [inconf objectForKey: NTSampleOutput];
    if (![inconf objectForKey: NTSampleInput] || !output)
	return nil;
    input = [[inconf objectForKey: NTSampleInput] mutableCopyWithZone:zone];
    conf = [inconf mutableCopyWithZone:zone];
    [conf setObject:input forKey:NTSampleInput];
    [input release]; // retained by conf
    [conf autorelease];
    
    /* Find appropriate format.  We only support 32 bit RGBX data. */
    if ( (pixelEncoding = [input objectForKey: NTPixelEncoding]) == nil
    	|| [NTPixel_RGBX8888 isEqualToString:pixelEncoding] == NO ) {
	    [input setObject: NTPixel_RGBX8888 forKey: NTPixelEncoding];
    }

    width = [output integerForKey:NTWidth];
    height = [output integerForKey:NTHeight];
    if (width  != [input integerForKey:NTWidth])
	[input setInteger:width forKey:NTWidth];
    if (height != [input integerForKey:NTHeight])
	[input setInteger:height forKey:NTHeight];

    return [super setConfiguration: conf];
}


- (void) setupSampleDescription
{
    NSDictionary * componentDict;

    componentDict = [[NTComponent componentForClass:[self class]] dictionary];
    sampleDescription = [[NSMutableDictionary alloc] init];

    [sampleDescription setObject: NTCompressed
	    forKey: NTFormatType];
    [sampleDescription setObject: @"NullVideo"
	    forKey: NTFormatSubtype];
    [sampleDescription setInteger:NULLVIDEO_COMPONENT_VERSION forKey:NTComponentVersion];
    [sampleDescription setInteger:NULLVIDEO_COMPONENT_REVISION_LEVEL forKey:NTComponentRevisionLevel];
    [sampleDescription setObject: NULLVIDEO_VENDOR
	    forKey: NTVendor];
    [sampleDescription setDouble:NULLVIDEO_TEMPORAL_QUALITY forKey:NTTemporalQuality];
    [sampleDescription setDouble:NULLVIDEO_SPATIAL_QUALITY forKey:NTSpatialQuality];
    [sampleDescription setInteger:width forKey:NTWidth];
    [sampleDescription setInteger:height forKey:NTHeight];
    [sampleDescription setDouble:NULLVIDEO_HRES forKey:NTHorizontalResolution];
    [sampleDescription setDouble:NULLVIDEO_VRES forKey:NTVerticalResolution];
    [sampleDescription setObject:
    			[componentDict objectForKey:NTLocalizedComponentName]
			forKey: NTCodecName];
    [sampleDescription setInteger:NULLVIDEO_BPP forKey:NTBitsPerPixel];
    [sampleDescription setObject:NULLVIDEO_COLORSPACE forKey:NTColorSpace];
}

- (BOOL) finalizeConfiguration
{
    [self setupSampleDescription];

    return YES;
} 

- (void)dealloc
{
    [sampleDescription release];
    [super dealloc];
}

 static int
null_encode( const unsigned int *sptr, unsigned int *dptr,
		int width, int height, int srb )
{
	int x, y;
	unsigned int *start = dptr;
	// Simple-minded pixel copier that honors rowbytes
	for (y = 0; y < height; ++y)
	{
	    for (x = 0; x < width; ++x)
	    {
		*dptr++ = *sptr++;
	    }
	    sptr += ((srb / sizeof *sptr) - width);
	}
	return (dptr - start) * (sizeof *dptr);
}

- (void)processSamplesFrom: (NTSampleBuffer *)src
	to: (NTMutableSampleBuffer *) dst
{
    const unsigned int *sptr = [src bytes];
    unsigned int *dptr = [dst mutableBytes];
    int size;
    int srb = [[src sampleDescription] integerForKey:NTBytesPerRow];

    size = null_encode(sptr, dptr, width, height, srb);
    [dst setSampleSize: size]; 
}

- (NTMutableSampleBuffer *) outputBufferForInput: (NTSampleBuffer *) buf
{
    return [[[NTMutableSampleBuffer allocWithZone:zone]
	     initSampleWithCapacity: (width * height + 5) * sizeof(int)
	     sampleSize		: (width * height) * sizeof(int)
	     startingTime 	: [buf startingTime]
	     sampleDuration	: [buf sampleDuration]
	     sampleCount	: 1
	     sampleDescription	: sampleDescription
	     sampleFlags	: NTSyncSample
	     trackID		: [buf trackID]
	     sequenceNumber	: [buf sequenceNumber] ] autorelease];
}

@end




