/*
	SoundMeter.h
	Sound Kit, Release 2.0
	Copyright (c) 1988, 1989, 1990, NeXT, Inc.  All rights reserved. 
*/

#import <AppKit/NSView.h>

@class Sound;

@interface SoundMeter:NSView
{
    id sound;
    int currentSample;
    float currentValue;
    float currentPeak;
    float minValue;
    float maxValue;
    float holdTime;
    NSColor *backgroundColor;
    NSColor *foregroundColor;
    NSColor *peakColor;
    struct {
	unsigned int running:1;
	unsigned int bezeled:1;
	unsigned int shouldStop:1;
	unsigned int _reservedFlags:13;
    } smFlags;
    void *_timedEntry;
    int _valTime;
    int _peakTime;
    float _valOneAgo;
    float _valTwoAgo;
}

- (id)initWithFrame:(NSRect)frameRect;

- (id)initWithCoder:(NSCoder *)aStream;
- (void)encodeWithCoder:(NSCoder *)aStream;
- (float)holdTime;
- (void)setHoldTime:(float)seconds;
- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;
- (void)setForegroundColor:(NSColor *)color;
- (NSColor *)foregroundColor;
- (void)setPeakColor:(NSColor *)color;
- (NSColor *)peakColor;
- (Sound *)sound;
- (void)setSound:(Sound *)aSound;
- (void)run:(id)sender;
- (void)stop:(id)sender;
- (BOOL)isRunning;
- (BOOL)isBezeled;
- (void)setBezeled:(BOOL)aFlag;
- (void)setFloatValue:(float)aValue;
- (float)floatValue;
- (float)peakValue;
- (float)minValue;
- (float)maxValue;
- (void)drawRect:(NSRect)rects;
- (void)drawCurrentValue;
@end
