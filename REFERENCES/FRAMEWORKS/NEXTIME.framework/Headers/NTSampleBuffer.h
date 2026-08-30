#import <Foundation/NSObject.h>
#import <Foundation/NSCoder.h>
#import <Foundation/NSData.h>
#import <Foundation/NSDictionary.h>
/*
 * A class for representing timestamped sample data internally and providing
 * transport over a DO connection.
 *
 * This provides a data encapsulation only.
 *
 */
 
typedef enum
{
	NTSyncSample = 1,
	NTEmptyEditSample = 1 << 30,
	NTEndOfSampleStream = 1 << 31
}
NTSampleFlags;

//
// NTMutableSampleBuffer should be a subclass of NTSampleBuffer, and
// a subclass of NSMutableData.  Ah, but that would be multiple inheritance,
// which we all know is a kludge.  Instead, we use protocols to whip up an
// 'inheritance' hierarchy of NTSampleBuffer API, and bind the protocols to
// our NSData and NSMutableData subclasses.  Sort of a template/mixin solution.
//
@protocol NTSampleBuffer <NSObject>
- (unsigned)sampleSize;
- (double)startingTime;
- (double)sampleDuration;
- (unsigned)sampleCount;
- (NSDictionary *)sampleDescription;
- (NTSampleFlags)sampleFlags;
- (int) trackID;
- (unsigned long) sequenceNumber;
@end

@protocol NTMutableSampleBuffer <NTSampleBuffer>
- (void)setSampleSize:(unsigned)sampleSize;
- (void)setStartingTime:(double)time;
- (void)setSampleDuration:(double)duration;
- (void)setSampleCount:(unsigned)sampleCount;
- (void)setSampleDescription:(NSDictionary *)description;
- (void)setSampleFlags:(NTSampleFlags)sampleFlags;
- (void) setSequenceNumber:(unsigned long)num;
- (void) setTrackID:(int)id;
- (void) setTimeStampFrom:(id <NTSampleBuffer>)other;
@end

@interface NTSampleBuffer: NSData <NSCopying, NSMutableCopying, NSCoding, NTSampleBuffer>
{
@private
	NSData	*		parent;
	unsigned		length;
	const void *		bytes;
	NSDictionary *		sampleDescription;
	double			startingTime;
	double			sampleDuration;
	unsigned		sampleSize;
	unsigned			sampleCount;
	NTSampleFlags		sampleFlags;
	int			trackID;
	unsigned long 		sequenceNumber;
	unsigned		refCount;
	void *			_private;
}

//
// NSData primitives we must implement
//
- (unsigned)length;
- (const void *)bytes;

// Designated initializer
- initSampleWithData		:(NSData *)data
	dataOffset		:(unsigned)offset
	sampleSize		:(unsigned)size
	startingTime		:(double)time
	sampleDuration		:(double)duration
	sampleCount		:(unsigned)count
	sampleDescription	:(NSDictionary *)description
	sampleFlags		:(NTSampleFlags)flags
	trackID			:(int)trackID
	sequenceNumber		:(unsigned long)sequenceNumber;

- (BOOL)isEqual:anObject;


@end

//
// Mutable sample buffer
// 
@interface NTMutableSampleBuffer: NSMutableData
		<NSCopying, NSMutableCopying, NSCoding, NTMutableSampleBuffer>
{
@private
	NSMutableData *		parent;
	unsigned		length;
	unsigned		capacity;
	void *			bytes;
	NSDictionary *		sampleDescription;
	double			startingTime;
	double			sampleDuration;
	int			sampleSize;
	int			sampleCount;
	NTSampleFlags		sampleFlags;
	int			trackID;
	unsigned long 		sequenceNumber;
	unsigned		refCount;
	BOOL			ownBytes;
	void *			_private;
}
- (void *)mutableBytes;
- (void)setLength:(unsigned int)length;
- (unsigned)length;
- (const void *)bytes;

// Designated initializer
- initSampleWithMemory		:(void *) memory	// May be NULL
	capacity		:(unsigned)capacity
	sampleSize		:(unsigned)size
	startingTime		:(double)time
	sampleDuration		:(double)duration
	sampleCount		:(unsigned)count
	sampleDescription	:(NSDictionary *)description
	sampleFlags		:(NTSampleFlags)flags
	trackID			:(int)_trackID
	sequenceNumber		:(unsigned long)_sequenceNumber;
	
- initSampleWithCapacity	:(unsigned)capacity
	sampleSize		:(unsigned)size
	startingTime		:(double)time
	sampleDuration		:(double)duration
	sampleCount		:(unsigned)count
	sampleDescription	:(NSDictionary *)description
	sampleFlags		:(NTSampleFlags)flags
	trackID			:(int)trackID
	sequenceNumber		:(unsigned long)sequenceNumber;

- initSampleWithData		:(NSData *)data
	dataOffset		:(unsigned)offset
	sampleSize		:(unsigned)size
	startingTime		:(double)time
	sampleDuration		:(double)duration
	sampleCount		:(unsigned)count
	sampleDescription	:(NSDictionary *)description
	sampleFlags		:(NTSampleFlags)flags
	trackID			:(int)trackID
	sequenceNumber		:(unsigned long)sequenceNumber;

- initSampleWithDataNoCopy	:(NSMutableData *)data
	dataOffset		:(unsigned)offset
	sampleSize		:(unsigned)size
	startingTime		:(double)time
	sampleDuration		:(double)duration
	sampleCount		:(unsigned)count
	sampleDescription	:(NSDictionary *)description
	sampleFlags		:(NTSampleFlags)flags
	trackID			:(int)trackID
	sequenceNumber		:(unsigned long)sequenceNumber;

@end
