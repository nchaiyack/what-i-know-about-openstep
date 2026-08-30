/*
 *  NTSampleProcessor.h
 * 	Copyright 1994, NeXT Computer, Inc.
 *	
 *	This is a server only abstract superclass to aid component writers.
 *
 *	27 Apr 1994 pgraff Created.
 */

#import "NTSampleProcessorProtocol.h"
#import "NTSampleBuffer.h"
#import <Foundation/NSObject.h>
#import <Foundation/NSDictionary.h>

@interface NTSampleProcessor: NSObject <NTSampleProcessor>
{
    NSZone *zone;
    NSDictionary *env;
    NSDictionary *config;
    id <NTMutableSampleBuffer> inputBuffer;
    id nextObject;
    BOOL samplesEnqueued;
    BOOL stopped;
}

// The following is the implementation of writeSample in this superclass.
// If it meets your needs, override either of the two below methods to taste.
// Otherwise override writeSample.
//
// - (void)writeSample: (NTSampleBuffer *) sample; 
// {
//     NTSampleBuffer *dst;
//
//     if ((dst = [nextObject inputBuffer]) == nil &&
//         (dst = [self outputBufferForInput: sample]) == nil) {
// 	   [sample free];
// 	   return;
//     }
//
//     [self processSamplesFrom: sample to: dst];
//     if (sample != inputBuffer) 
// 	   [sample free];
//     [nextObject writeSample: dst];
// }

- (NTMutableSampleBuffer *) outputBufferForInput: (NTSampleBuffer *) buf;
- (void) processSamplesFrom: (NTSampleBuffer *)src to: (NTMutableSampleBuffer *) dst;

@end







