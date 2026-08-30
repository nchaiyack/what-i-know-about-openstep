/*
	NSScrollView.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#import <AppKit/NSView.h>

@class NSScroller;
@class NSClipView;
@class NSColor;
@class NSRulerView;

typedef struct __SFlags {
#ifdef __BIG_ENDIAN__
    unsigned int        vScrollerRequired:1;
    unsigned int        hScrollerRequired:1;
    unsigned int        vScrollerStatus:1;
    unsigned int        hScrollerStatus:1;
    unsigned int        noDynamicScrolling:1;
    NSBorderType        borderType:2;
    unsigned int        oldRulerInstalled:1;
    unsigned int        showRulers:1;
    unsigned int        hasHorizontalRuler:1;
    unsigned int        hasVerticalRuler:1;
    unsigned int        needsTile:1;
    unsigned int        RESERVED:20;
#else
    unsigned int        RESERVED:20;
    unsigned int        needsTile:1;
    unsigned int        hasVerticalRuler:1;
    unsigned int        hasHorizontalRuler:1;
    unsigned int        showRulers:1;
    unsigned int        oldRulerInstalled:1;
    NSBorderType        borderType:2;
    unsigned int        noDynamicScrolling:1;
    unsigned int        hScrollerStatus:1;
    unsigned int        vScrollerStatus:1;
    unsigned int        hScrollerRequired:1;
    unsigned int        vScrollerRequired:1;
#endif
} _SFlags;

@interface NSScrollView : NSView
{
    NSScroller	*_vScroller;
    NSScroller	*_hScroller;
    NSClipView	*_contentView;
    float	_pageContext;
    float	_lineAmount;
    id		_ruler;
    _SFlags     _sFlags;
    void       *_reserved1;
    
    // new rulers
    NSRulerView *_horizontalRuler;
    NSRulerView *_verticalRuler;
}

+ (NSSize)frameSizeForContentSize:(NSSize)cSize hasHorizontalScroller:(BOOL)hFlag hasVerticalScroller:(BOOL)vFlag borderType:(NSBorderType)aType;
+ (NSSize)contentSizeForFrameSize:(NSSize)fSize hasHorizontalScroller:(BOOL)hFlag hasVerticalScroller:(BOOL)vFlag borderType:(NSBorderType)aType;

- (NSRect)documentVisibleRect;
- (NSSize)contentSize;

- (void)setDocumentView:(NSView *)aView;
- (id)documentView;
- (void)setContentView:(NSClipView *)contentView;
- (NSClipView *)contentView;
- (void)setDocumentCursor:(NSCursor *)anObj;
- (NSCursor *)documentCursor;
- (void)setBorderType:(NSBorderType)aType;
- (NSBorderType)borderType;
- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;
- (void)setHasVerticalScroller:(BOOL)flag;
- (BOOL)hasVerticalScroller;
- (void)setHasHorizontalScroller:(BOOL)flag;
- (BOOL)hasHorizontalScroller;
- (void)setVerticalScroller:(NSScroller *)anObject;
- (NSScroller *)verticalScroller;
- (void)setHorizontalScroller:(NSScroller *)anObject;
- (NSScroller *)horizontalScroller;
- (void)setLineScroll:(float)value;
- (float)lineScroll;
- (void)setPageScroll:(float)value;
- (float)pageScroll;
- (void)setScrollsDynamically:(BOOL)flag;
- (BOOL)scrollsDynamically;
- (void)tile;
- (void)reflectScrolledClipView:(NSClipView *)cView;

@end

#ifndef STRICT_OPENSTEP

@interface NSScrollView(NSRulerSupport)

+ (void)setRulerViewClass:(Class)rulerViewClass;
+ (Class)rulerViewClass;

- (void)setRulersVisible:(BOOL)flag;
- (BOOL)rulersVisible;

- (void)setHasHorizontalRuler:(BOOL)flag;
- (BOOL)hasHorizontalRuler;
- (void)setHasVerticalRuler:(BOOL)flag;
- (BOOL)hasVerticalRuler;

- (void)setHorizontalRulerView:(NSRulerView *)ruler;
- (NSRulerView *)horizontalRulerView;
- (void)setVerticalRulerView:(NSRulerView *)ruler;
- (NSRulerView *)verticalRulerView;

@end

#endif

@interface NSScrollView(NSOldRuler)
- (void)toggleRuler:(id)sender;
- (BOOL)isRulerVisible;
@end

