/*
 * NXSoundOut.h
 *
 * Copyright (c) 1992, NeXT Computer, Inc.  All rights reserved. 
 */

#import "NXSoundDevice.h"

@interface NXSoundOut:NXSoundDevice
{
    unsigned int	_options;
    int			_reserved1;
}

// Obsolete - use generic parameter api.
+ (port_t)lookUpDevicePortOnHost:(NSString *)hostName;
- (BOOL)doesInsertZeros;
- (NXSoundDeviceError)setInsertsZeros:(BOOL)flag;
- (BOOL)doesRampUp;
- (NXSoundDeviceError)setRampsUp:(BOOL)flag;
- (BOOL)doesRampDown;
- (NXSoundDeviceError)setRampsDown:(BOOL)flag;
- (BOOL)doesDeemphasize;
- (NXSoundDeviceError)setDeemphasis:(BOOL)flag;
- (BOOL)isSpeakerMute;
- (NXSoundDeviceError)setSpeakerMute:(BOOL)flag;
- (unsigned int)clipCount;
- (NXSoundDeviceError)getAttenuationLeft:(float *)leftDB
                                   right:(float *)rightDB;
- (NXSoundDeviceError)setAttenuationLeft:(float)leftDB
                                   right:(float)rightDB;

@end
