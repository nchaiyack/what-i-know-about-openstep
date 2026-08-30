/*
	NSFontPanel.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#import <AppKit/NSPanel.h>
#import <AppKit/NSFont.h>

@class NSMatrix;
@class NSButton;

/* Tags of views in the FontPanel */

enum {
    NSFPPreviewButton			= 131,
    NSFPRevertButton			= 130,
    NSFPSetButton			= 132,
    NSFPPreviewField			= 128,
    NSFPSizeField			= 129,
    NSFPSizeTitle			= 133,
    NSFPCurrentField			= 134
};

@interface NSFontPanel : NSPanel
{
    NSMatrix 		*_faces;
    NSMatrix 		*_families;
    id                  _preview;
    id                  _current;
    id                  _size;
    NSMatrix 		*_sizes;
    id                  _manager;
    id                  _selFont;
    struct _NSFontMetrics *_selMetrics;
    int                 _curTag;
    id                  _accessoryView;
    NSString		*_keyBuffer;
    NSButton		*_setButton;
    id                  _separator;
    id                  _sizeTitle;
    NSString		*_lastPreview;
    NSTimeInterval      _lastKeyTime;
    id		        _chooser;
    NSMutableArray      *_titles;
    id		        _previewBox;
    struct __fpFlags {
        unsigned int        multipleFont:1;
        unsigned int        dirty:1;
        unsigned int	    doingPreviewButton:1;
        unsigned int        amPreviewing:1;
        unsigned int        alwaysPreview:1;
        unsigned int        dontPreview:1;
	unsigned int	    sizeFieldChanged:1;
	unsigned int	    sizeValueCacheIsValid:1;
	unsigned int	    sizeFieldIsRelative:1;
        unsigned int        RESERVED:24;
    } _fpFlags;
    float		_cachedSizeValue;
    int _reservedFontPanel1;
    int _reservedFontPanel2;
}

+ (NSFontPanel *)sharedFontPanel;

#ifndef STRICT_OPENSTEP
+ (BOOL)sharedFontPanelExists;
#endif

- (NSView *)accessoryView;
- (void)setAccessoryView:(NSView *)aView;
- (void)orderWindow:(NSWindowOrderingMode)place relativeTo:(int)otherWin;
- (void)setPanelFont:(NSFont *)fontObj isMultiple:(BOOL)flag;
- (NSFont *)panelConvertFont:(NSFont *)fontObj;
- (BOOL)worksWhenModal;
- (BOOL)isEnabled;
- (void)setEnabled:(BOOL)flag;

@end
