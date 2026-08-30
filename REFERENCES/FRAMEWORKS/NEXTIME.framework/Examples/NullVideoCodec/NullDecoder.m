#import <architecture/byte_order.h>
#import "NullDecoder.h"
#import <NEXTIME/NTValueDictionary.h>
#import <NEXTIME/NTDictionaryKeys.h>

#define NULLVIDEO_COMPONENT_VERSION		0
#define NULLVIDEO_COMPONENT_REVISION_LEVEL	0
#define NULLVIDEO_VENDOR			@"NeXT Computer, Inc."
#define NULLVIDEO_TEMPORAL_QUALITY		1.0
#define NULLVIDEO_SPATIAL_QUALITY		1.0
#define NULLVIDEO_HRES				72.0
#define NULLVIDEO_VRES				72.0
#define NULLVIDEO_COLORSPACE			NSDeviceRGBColorSpace

// Rowbytes are assumed to be a multiple of 8 bytes
#define AdjustedRowbytes(r)	(((r) + 7) & ~7)
#define HeightPad	4

@implementation NullDecoder

- (bycopy NSDictionary *) setConfiguration:
		(bycopy NSDictionary *) inconf
{
    NSMutableDictionary *conf, *output;
    NSDictionary *input;
    NSString * pixelEncoding;

    input = [inconf objectForKey: NTSampleInput];
    if (!input || ![inconf objectForKey: NTSampleOutput])
	return nil;

    output = [[inconf objectForKey: NTSampleOutput] mutableCopyWithZone:zone];
    conf = [inconf mutableCopyWithZone:zone];
    [conf setObject:output forKey:NTSampleOutput];
    [output release]; // retained by conf
    [conf autorelease];
    
    /* Find appropriate format.  We only support 32 bit RGBX data. */
    if ( (pixelEncoding = [output objectForKey: NTPixelEncoding]) == nil
    	|| [NTPixel_RGBX8888 isEqualToString:pixelEncoding] == NO ) {
	    [output setObject: NTPixel_RGBX8888 forKey: NTPixelEncoding];
    }
    
    /* Ensure that the scaling is appropriate */
    sWidth  = [input integerForKey:NTWidth];
    sHeight = [input integerForKey:NTHeight];
    dWidth  = [output integerForKey:NTWidth];
    dHeight = [output integerForKey:NTHeight];

    /* We don't support resizing in the decompressor */
    if (dWidth != sWidth || dHeight != sHeight) {
	[output setInteger:sWidth forKey:NTWidth];
	[output setInteger:sHeight forKey:NTHeight];
    }

    return [super setConfiguration: conf];
}

- (BOOL) finalizeConfiguration
{
    int depth, width;

    sampleDescription = [[config objectForKey: NTSampleOutput]
    				mutableCopyWithZone:[self zone]];
    [sampleDescription setInteger:NULLVIDEO_COMPONENT_VERSION forKey:NTComponentVersion];
    [sampleDescription setInteger:NULLVIDEO_COMPONENT_REVISION_LEVEL forKey:NTComponentRevisionLevel];
    [sampleDescription setObject: NULLVIDEO_VENDOR
	    forKey: NTVendor];
    [sampleDescription setDouble:NULLVIDEO_TEMPORAL_QUALITY forKey:NTTemporalQuality];
    [sampleDescription setDouble:NULLVIDEO_SPATIAL_QUALITY forKey:NTSpatialQuality];
    [sampleDescription setDouble:NULLVIDEO_HRES forKey:NTHorizontalResolution];
    [sampleDescription setDouble:NULLVIDEO_VRES forKey:NTVerticalResolution];
    depth = strlen( [sampleDescription cStringForKey:NTPixelEncoding] );
    width = [sampleDescription integerForKey:NTWidth];
    [sampleDescription setInteger:depth forKey:NTBitsPerPixel];
    [sampleDescription setInteger:AdjustedRowbytes(((width * depth) + 7) / 8) forKey:NTBytesPerRow];
    [sampleDescription setObject:NULLVIDEO_COLORSPACE forKey:NTColorSpace];
    
    return YES;
} 

- (void)dealloc
{
     if ( sampleDescription )
    	[sampleDescription release];
    if ( frameBuffer )
    	[frameBuffer release];

    [super dealloc];
}

 static void
null_decode( const unsigned int *sptr, unsigned int *dptr,
		int dWidth, int dHeight, int drb )
{
	int x, y;
	// Simple-minded pixel copier that honors rowbytes
	for (y = 0; y < dHeight; ++y)
	{
	    for (x = 0; x < dWidth; ++x)
	    {
		*dptr++ = *sptr++;
	    }
	    dptr += ((drb / sizeof *dptr) - dWidth);
	}
}

- (void)processSamplesFrom: (NTSampleBuffer *)src
	to: (NTMutableSampleBuffer *) dst
{
    const unsigned int *sptr = [src bytes];
    unsigned int *dptr = [dst mutableBytes];
    int drb = [[dst sampleDescription] integerForKey:NTBytesPerRow];

    null_decode(sptr, dptr, dWidth, dHeight, drb); 
}

- (NTMutableSampleBuffer *) outputBufferForInput: (NTSampleBuffer *) buf
{
	int rowBytes;
	int height;
	NTMutableSampleBuffer *out;
	
	height = [sampleDescription integerForKey:NTHeight];
	rowBytes = [sampleDescription integerForKey:NTBytesPerRow];
	if ( frameBuffer == nil )
	{
	    frameBuffer = [[NSMutableData allocWithZone:zone]
			    initWithLength:height * rowBytes];
	}
	out = [[NTMutableSampleBuffer allocWithZone:zone]
		    initSampleWithDataNoCopy: frameBuffer
		    dataOffset		: 0 
		    sampleSize		: height * rowBytes
		    startingTime	: [buf startingTime]
		    sampleDuration	: [buf sampleDuration]
		    sampleCount		: 1
		    sampleDescription	: sampleDescription 
		    sampleFlags		: NTSyncSample
		    trackID		: [buf trackID]
		    sequenceNumber	: [buf sequenceNumber] ];
	return [out autorelease];
}

@end
