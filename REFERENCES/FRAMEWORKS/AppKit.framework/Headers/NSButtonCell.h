/*
	NSButtonCell.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#import <AppKit/NSActionCell.h>

@class NSImage;
@class NSFont;
@class NSAttributedString;

typedef enum _NSButtonType {
    NSMomentaryPushButton		= 0,
    NSPushOnPushOffButton		= 1,
    NSToggleButton			= 2,
    NSSwitchButton			= 3,
    NSRadioButton			= 4,
    NSMomentaryChangeButton		= 5,
    NSOnOffButton			= 6,
    NSMomentaryLight			= 7
} NSButtonType;

typedef struct __BCFlags {
#ifdef __BIG_ENDIAN__
    unsigned int        pushIn:1;
    unsigned int        changeContents:1;
    unsigned int        changeBackground:1;
    unsigned int        changeGray:1;
    unsigned int        lightByContents:1;
    unsigned int        lightByBackground:1;
    unsigned int        lightByGray:1;
    unsigned int        hasAlpha:1;
    unsigned int        bordered:1;
    unsigned int        imageOverlaps:1;
    unsigned int        horizontal:1;
    unsigned int        bottomOrLeft:1;
    unsigned int        imageAndText:1;
    unsigned int        imageSizeDiff:1;
    unsigned int        hasKeyEquivalentInsteadOfImage:1;
    unsigned int        lastState:1;
    unsigned int        transparent:1;
    unsigned int        inset:2;
    unsigned int        doesNotDimImage:1;
    unsigned int        gradientType:3;
    unsigned int        reserved1:1;
    unsigned int        alternateMnemonicLocation:8;
#else
    unsigned int        alternateMnemonicLocation:8;
    unsigned int        reserved1:1;
    unsigned int        gradientType:3;
    unsigned int        doesNotDimImage:1;
    unsigned int        inset:2;
    unsigned int        transparent:1;
    unsigned int        lastState:1;
    unsigned int        hasKeyEquivalentInsteadOfImage:1;
    unsigned int        imageSizeDiff:1;
    unsigned int        imageAndText:1;
    unsigned int        bottomOrLeft:1;
    unsigned int        horizontal:1;
    unsigned int        imageOverlaps:1;
    unsigned int        bordered:1;
    unsigned int        hasAlpha:1;
    unsigned int        lightByGray:1;
    unsigned int        lightByBackground:1;
    unsigned int        lightByContents:1;
    unsigned int        changeGray:1;
    unsigned int        changeBackground:1;
    unsigned int        changeContents:1;
    unsigned int        pushIn:1;
#endif
} _BCFlags;


@interface NSButtonCell : NSActionCell
{
    NSString	       *_altContents;
    id			_sound;
    NSString	       *_keyEquivalent;
    unsigned int	_keyEquivalentModifierMask;
    unsigned short	_periodicDelay;
    unsigned short	_periodicInterval;
    _BCFlags            _bcFlags;
    NSImage            *_normalImage;
    id                  _alternateImageOrKeyEquivalentFont;
}


- (NSString *)title;
- (void)setTitle:(NSString *)aString;
- (NSString *)alternateTitle;
- (void)setAlternateTitle:(NSString *)aString;
#ifndef STRICT_OPENSTEP
- (id)alternateObjectValue;
- (void)setAlternateObjectValue:(id)obj;
- (BOOL)hasValidAlternateObjectValue;
#endif STRICT_OPENSTEP
- (NSImage *)alternateImage;
- (void)setAlternateImage:(NSImage *)image;
- (NSCellImagePosition)imagePosition;
- (void)setImagePosition:(NSCellImagePosition)aPosition;
- (int)highlightsBy;
- (void)setHighlightsBy:(int)aType;
- (int)showsStateBy;
- (void)setShowsStateBy:(int)aType;
- (void)setButtonType:(NSButtonType)aType;
- (BOOL)isOpaque;
- (void)setFont:(NSFont *)fontObj;
- (BOOL)isTransparent;
- (void)setTransparent:(BOOL)flag;
- (void)setPeriodicDelay:(float)delay interval:(float)interval;
- (void)getPeriodicDelay:(float *)delay interval:(float *)interval;
- (NSString *)keyEquivalent;
- (void)setKeyEquivalent:(NSString *)aKeyEquivalent;
- (unsigned int)keyEquivalentModifierMask;
- (void)setKeyEquivalentModifierMask:(unsigned int)mask;
- (NSFont *)keyEquivalentFont;
- (void)setKeyEquivalentFont:(NSFont *)fontObj;
- (void)setKeyEquivalentFont:(NSString *)fontName size:(float)fontSize;
- (void)performClick:(id)sender; // Significant NSCell override, actually clicks itself.

@end

#ifndef STRICT_OPENSTEP
@interface NSButtonCell(NSKeyboardUI)
- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand;
- (void)setAlternateTitleWithMnemonic:(NSString *)stringWithAmpersand;
- (void)setAlternateMnemonicLocation:(unsigned)location;
- (unsigned)alternateMnemonicLocation;
- (NSString *)alternateMnemonic;
@end
#endif

#ifndef STRICT_OPENSTEP

// NSGradientType :
//
// A concave gradient is darkest in the top left corner, 
// a convex gradient is darkest in the bottom right corner.
//
// Weak versus strong is how much contrast exists between
// the colors used in opposite corners
typedef enum _NSGradientType {
    NSGradientNone          = 0,
    NSGradientConcaveWeak   = 1,
    NSGradientConcaveStrong = 2,
    NSGradientConvexWeak    = 3,
    NSGradientConvexStrong  = 4
} NSGradientType;

@interface NSButtonCell(NSButtonCellExtensions)
- (NSGradientType)gradientType;
- (void)setGradientType:(NSGradientType)type;

// When disabled, the image and text of an NSButtonCell are normally dimmed with gray.
// Radio buttons and switches use (imageDimsWhenDisabled == NO) so only their text is dimmed.
- (void)setImageDimsWhenDisabled:(BOOL)flag;
- (BOOL)imageDimsWhenDisabled;
@end

@interface NSButtonCell(NSButtonCellAttributedStringMethods)
- (NSAttributedString *)attributedTitle;
- (void)setAttributedTitle:(NSAttributedString *)obj;
- (NSAttributedString *)attributedAlternateTitle;
- (void)setAttributedAlternateTitle:(NSAttributedString *)obj;
@end

#endif
