/*
 * NXRecordStream.h
 *
 * Copyright (c) 1992, NeXT Computer, Inc.  All rights reserved. 
 */

#import "NXSoundStream.h"

@interface NXRecordStream:NXSoundStream
{
    int _reserved1;
}

- (NXSoundDeviceError)recordSize:(unsigned int)bytes tag:(int)anInt;
- (NXSoundDeviceError)sendRecordedDataToDelegate;

// Obsolete - use generic parameter api.
- (NXSoundDeviceError)recordSize:(unsigned int)bytes tag:(int)anInt
                    lowWaterMark:(unsigned int)lowWater
                   highWaterMark:(unsigned int)highWater;

@end

@interface NSObject(NXRecordStreamDelegate)
- (void)soundStreamDidOverrun:(id)sender;
- (void)soundStream:sender didRecordData:(void *)data size:(unsigned int)bytes forBuffer:(int)tag;
@end
