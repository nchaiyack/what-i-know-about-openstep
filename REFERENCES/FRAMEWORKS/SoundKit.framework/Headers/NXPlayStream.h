/*
 * NXPlayStream.h
 *
 * Copyright (c) 1992, NeXT Computer, Inc.  All rights reserved. 
 */

#import "NXSoundStream.h"

@interface NXPlayStream:NXSoundStream
{
    float		_leftGain;
    float		_rightGain;
    BOOL		_isDetectingPeaks;
    unsigned int	_peakHistory;
    int			_reserved1;
}

- (id)initOnDevice:(id)anObject;
- (NXSoundDeviceError)activate;
- (void)getGainLeft:(float *)leftAmp right:(float *)rightAmp;
- (NXSoundDeviceError)setGainLeft:(float)leftAmp right:(float)rightAmp;
- (NXSoundDeviceError)getPeakLeft:(float *)leftAmp
                            right:(float *)rightAmp;

// New for 3.1.
- (NXSoundDeviceError)playBuffer:(void *)data
                            size:(unsigned int)bytes
                             tag:(int)anInt;

// Obsolete - use generic parameter api.
- (NXSoundDeviceError)playBuffer:(void *)data
                            size:(unsigned int)bytes
                             tag:(int)anInt
                    channelCount:(unsigned int)channels
                    samplingRate:(float)rate
                  bufferGainLeft:(float)leftAmp right:(float)rightAmp
                    lowWaterMark:(unsigned int)lowWater
                   highWaterMark:(unsigned int)highWater;
- (NXSoundDeviceError)playBuffer:(void *)data
                            size:(unsigned int)bytes
                             tag:(int)anInt
                    channelCount:(unsigned int)channels
                    samplingRate:(float)rate;
- (BOOL)isDetectingPeaks;
- (NXSoundDeviceError)setDetectPeaks:(BOOL)flag;
- (unsigned int)peakHistory;
- (NXSoundDeviceError)setPeakHistory:(unsigned int)bufferCount;

@end

@interface NSObject(NXPlayStreamDelegate)
- (void)soundStreamDidUnderrun:(id)sender;
@end
