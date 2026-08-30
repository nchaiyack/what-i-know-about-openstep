/*
 * NXSoundParameterTags.h
 *
 * Copyright (c) 1993, NeXT Computer, Inc.  All rights reserved. 
 */

#define NX_SoundDeviceParameterKeyBase		0
#define NX_SoundDeviceParameterValueBase	200
#define NX_SoundStreamParameterKeyBase		400
#define NX_SoundStreamParameterValueBase	600
#define NX_SoundParameterTagMax			799

typedef enum _NXSoundParameterTag {
    NX_SoundDeviceBufferSize = NX_SoundDeviceParameterKeyBase,
    NX_SoundDeviceBufferCount,
    NX_SoundDeviceDetectPeaks,
    NX_SoundDeviceRampUp,
    NX_SoundDeviceRampDown,
    NX_SoundDeviceInsertZeros,
    NX_SoundDeviceDeemphasize,
    NX_SoundDeviceMuteSpeaker,
    NX_SoundDeviceMuteHeadphone,
    NX_SoundDeviceMuteLineOut,
    NX_SoundDeviceOutputLoudness,
    NX_SoundDeviceOutputAttenuationStereo,
    NX_SoundDeviceOutputAttenuationLeft,
    NX_SoundDeviceOutputAttenuationRight,
    NX_SoundDeviceAnalogInputSource,
    NX_SoundDeviceMonitorAttenuation,
    NX_SoundDeviceInputGainStereo,
    NX_SoundDeviceInputGainLeft,
    NX_SoundDeviceInputGainRight,

    NX_SoundDeviceAnalogInputSource_Microphone
	= NX_SoundDeviceParameterValueBase,
    NX_SoundDeviceAnalogInputSource_LineIn,

    NX_SoundStreamDataEncoding = NX_SoundStreamParameterKeyBase,
    NX_SoundStreamSamplingRate,
    NX_SoundStreamChannelCount,
    NX_SoundStreamHighWaterMark,
    NX_SoundStreamLowWaterMark,
    NX_SoundStreamSource,
    NX_SoundStreamSink,
    NX_SoundStreamDetectPeaks,
    NX_SoundStreamGainStereo,
    NX_SoundStreamGainLeft,
    NX_SoundStreamGainRight,

    NX_SoundStreamDataEncoding_Linear16 = NX_SoundStreamParameterValueBase,
    NX_SoundStreamDataEncoding_Linear8,
    NX_SoundStreamDataEncoding_Mulaw8,
    NX_SoundStreamDataEncoding_Alaw8,
    NX_SoundStreamDataEncoding_AES,
    NX_SoundStreamSource_Analog,
    NX_SoundStreamSource_AES,
    NX_SoundStreamSink_Analog,
    NX_SoundStreamSink_AES
} NXSoundParameterTag;
