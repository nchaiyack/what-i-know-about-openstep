/*
 * IOAudio.h
 *
 * Copyright (c) 1993, NeXT Computer, Inc.  All rights reserved.
 *
 */

#import <driverkit/machine/directDevice.h>
#import <mach/mach_types.h>
#import <mach/mach_interface.h>
#import <SoundKit/NXSoundParameterTags.h>

typedef void	(*IOAudioInterruptClearFunc)(void);

@interface IOAudio: IODirectDevice
{
@private
    id				_inputChannel;
    id				_outputChannel;
    id				_audioCommand;
 
    port_t			_commandPort;
    port_set_name_t		_devicePortSet;
  
    msg_header_t		*_dataPendingMessage;
    msg_timeout_t		_timeout;

    unsigned int		_sampleRate;
    unsigned int		_dataEncoding;
    unsigned int		_channelCount;
        
    unsigned int		_inputGainLeft;
    unsigned int		_inputGainRight;
    
    int				_outputAttenuationLeft;
    int				_outputAttenuationRight;

    int				_bassBoost;
    int				_trebleBoost;
    
    BOOL			_isInputActive;
    BOOL			_isOutputActive;

    BOOL			_isInputMuted;
    BOOL			_isOutputMuted;
    BOOL			_isLoudnessEnhanced;

    BOOL			_doesInsertZeros;
    BOOL			_doesDeemphasize;
    BOOL			_doesRampUp;
    BOOL			_doesRampDown;

    void			*_audioPrivate;
    
    int				_IOAudio_reserved[3];
}

- initFromDeviceDescription: description;
- (BOOL) reset;
- free;

- (unsigned int) sampleRate;

- (NXSoundParameterTag) dataEncoding;

- (unsigned int) channelCount;

- (void) interruptOccurredForInput: (BOOL *) serviceInput
                         forOutput: (BOOL *) serviceOutput;

- (void) timeoutOccurred;

- (BOOL) startDMAForChannel: (unsigned int) localChannel
                       read: (BOOL) isRead
                     buffer: (IODMABuffer) buffer
    bufferSizeForInterrupts: (unsigned int) bufferSize;

- (void) stopDMAForChannel: (unsigned int) localChannel
                      read: (BOOL) isRead;

- (void)getInputChannelBuffer: (void *)addr
                         size: (unsigned int *)byteCount;
    
- (void)getOutputChannelBuffer: (void *)addr
                          size: (unsigned int *)byteCount;

- (unsigned int) inputGainLeft;
- (unsigned int) inputGainRight;
- (int) outputAttenuationLeft;
- (int) outputAttenuationRight;

- (BOOL) isOutputMuted;

- (BOOL) isLoudnessEnhanced;

- (BOOL) isInputActive;
- (BOOL) isOutputActive;

- (BOOL) acceptsContinuousSamplingRates;

- (void) getSamplingRatesLow: (int *) lowRate
                        high: (int *) highRate;

- (void) getSamplingRates: (int *) rates
                    count: (unsigned int *) numRates;

- (void) getDataEncodings: (NXSoundParameterTag *) encodings
                    count: (unsigned int *) numEncodings;

- (unsigned int) channelCountLimit;

- (void) updateLoudnessEnhanced;
- (void) updateInputGainLeft;
- (void) updateInputGainRight;
- (void) updateOutputMute;
- (void) updateOutputAttenuationLeft;
- (void) updateOutputAttenuationRight;

- (void) setInput:(NXSoundParameterTag)ptag enable:(BOOL)enable;
- (void) setOutput:(NXSoundParameterTag)ptag enable:(BOOL)enable;

- (IOAudioInterruptClearFunc) interruptClearFunc;

@end
