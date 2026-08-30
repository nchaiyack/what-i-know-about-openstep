/*
 *  components.h
 *
 *	Protocols for use by loadable components are specified here.
 *
 *	12 Sept 1992 mpaque Created.
 */
#import <Foundation/NSBundle.h>
#import "NTValueDictionary.h"
/*
 * Protocols available for use by all component classes, for access to
 * component resources.
 */


/*
 * Protocol to be implemented by all image decompressors
 */
@protocol NTImageDecompressor <NSObject>
- init;
- (void)dealloc;
- (BOOL)preDecompress	:(id)image;	// Really an NTSample *
- (BOOL)decompress	:(in int *)data
		size	:(inout unsigned *)size
		toImage	:(id)image;	// Really an NTSample *
@end

/*
 * Protocol to be implemented by all image compressors.  A compressor
 * is required to support decompression of it's own format.
 */
@protocol NTImageCompressor	<NTImageDecompressor>
- (unsigned)maxCompressionSize:(id)image;
- preCompress:(id)image;
- compress	:(id)image
	toBuffer:(out int *)data
	size	:(unsigned)size;

- (oneway void)setCompressionQuality:(double)q;		// Tuning parameters
- (oneway void)setCompressionRatio:(double)ratio;	// Tuning parameters
@end


/*
 * Protocol to be implemented by video source peripherals such as
 * computer controlled tape deck and laser disc components
 */
@protocol NTVideoSourcePeripheral <NSObject>
- init;
- (void)dealloc;
- (BOOL)isReady;		// Media loaded, ready to play?
- (BOOL)canSeekToFrame;		// Media dependent queries
- (BOOL)canStepByFrame;		// Media dependent
- (BOOL)canSeekToTime;		// Media dependent
- (BOOL)canShowStill;		// Media dependent
- (BOOL)canReportFrame;		// Media dependent

- (BOOL)ready;			// Load and prepare to play

- (BOOL)seekToFrame:(int)frame;	// Position media and pause/still
- (BOOL)seekToHour:(int)hour minute:(int)minute second:(int)second;

- (BOOL)play;			// Play at normal speed
- (BOOL)still;			// Enter still mode
- (BOOL)pause;			// pause performance
- (BOOL)stepForward;		// Step to next frame
- (BOOL)stepReverse;		// Step back by one frame
- (int)reportFrame;		// Return the current frame, or -1 on error

@end
