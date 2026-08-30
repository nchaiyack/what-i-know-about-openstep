/*
	obsoleteGraphics.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
	
	This file declares API that is now obsolete.
*/

#import <Foundation/Foundation.h> 
#import <AppKit/NSGraphics.h>
#import <AppKit/NSColor.h>
#import <AppKit/AppKitDefines.h>

#import <AppKit/dpsfriends.h>
#import <AppKit/event.h>

#import <objc/objc.h>
#import <objc/typedstream.h>

typedef float NXCoord;
typedef NSRect NXRect;
typedef NSSize NXSize;
typedef NSPoint NXPoint;

#define	NX_X(aRect)	((aRect)->origin.x)
#define	NX_Y(aRect)	((aRect)->origin.y)
#define	NX_WIDTH(aRect)	((aRect)->size.width)
#define	NX_HEIGHT(aRect)	((aRect)->size.height)
#define	NX_MAXX(aRect)	((aRect)->origin.x + (aRect)->size.width)
#define	NX_MAXY(aRect)	((aRect)->origin.y + (aRect)->size.height)
#define	NX_MIDX(aRect)	(NX_X(aRect)+NX_WIDTH(aRect)/2.0)
#define	NX_MIDY(aRect)	(NX_Y(aRect)+NX_HEIGHT(aRect)/2.0)

/* The sides of a rectangle */
#define NX_XMIN	0
#define NX_YMIN	1
#define NX_XMAX	2
#define NX_YMAX	3

APPKIT_EXTERN NSColor *NXReadPixel(const NXPoint *p);
APPKIT_EXTERN void NXCopyBits(int sgnum, const NXRect *sRect, const NXPoint *dPoint);
APPKIT_EXTERN void NXDrawButton(const NXRect *aRect, const NXRect *clipRect);
APPKIT_EXTERN void NXDrawGrayBezel(const NXRect *aRect, const NXRect *clipRect);
APPKIT_EXTERN void NXDrawGroove(const NXRect *aRect, const NXRect *clipRect);
APPKIT_EXTERN NXRect *NXDrawTiledRects(NXRect *boundsRect, const NXRect *clipRect,
		const int *sides, const float *grays, int count);
APPKIT_EXTERN void NXDrawWhiteBezel(const NXRect *aRect, const NXRect *clipRect);
APPKIT_EXTERN void NXEraseRect(const NXRect *aRect);
APPKIT_EXTERN void NXFrameRect(const NXRect *aRect);
APPKIT_EXTERN void NXFrameRectWithWidth(const NXRect *aRect, float frameWidth);
APPKIT_EXTERN void NXRectClip(const NXRect *aRect);
APPKIT_EXTERN void NXRectClipList(const NXRect *rects, int count);
APPKIT_EXTERN void NXRectFill(const NXRect *aRect);
APPKIT_EXTERN void NXRectFillList(const NXRect *rects, int count);
APPKIT_EXTERN void NXHighlightRect(const NXRect *aRect);
APPKIT_EXTERN void NXRectFillListWithGrays(const NXRect *rects, const float *grays, int count);

APPKIT_EXTERN BOOL NXContainsRect(const NXRect *a, const NXRect *b);
APPKIT_EXTERN NXRect *NXDivideRect(NXRect *aRect, NXRect *bRect, float slice, int edge);
APPKIT_EXTERN BOOL NXEmptyRect(const NXRect *aRect);
APPKIT_EXTERN BOOL NXEqualRect(const NXRect *aRect, const NXRect *bRect);
APPKIT_EXTERN void NXInsetRect(NXRect *aRect, float dX, float dY);
APPKIT_EXTERN void NXIntegralRect(NXRect *aRect);
APPKIT_EXTERN NXRect *NXIntersectionRect(const NXRect *aRect, NXRect *bRect);
APPKIT_EXTERN BOOL NXIntersectsRect(const NXRect *aRect, const NXRect *bRect);
APPKIT_EXTERN void NXOffsetRect(NXRect *aRect, float dX, float dY);
APPKIT_EXTERN BOOL NXPointInRect(const NXPoint *aPoint, const NXRect *aRect);
APPKIT_EXTERN BOOL NXMouseInRect(const NXPoint *aPoint, const NXRect *aRect, BOOL flipped);
APPKIT_EXTERN void NXSetRect(NXRect *aRect, float x, float y, float w, float h);
APPKIT_EXTERN NXRect *NXUnionRect(const NXRect *aRect, NXRect *bRect);

APPKIT_EXTERN void NXDrawBitmap(const NXRect *rect, int width, int height,
			int bps, int spp, int bpp, int bpr, 
			BOOL isPlanar, BOOL hasAlpha, int colorSpace,
			const unsigned char *const data[5]);


/* photoInterp values */
#define NX_MONOTONICMASK	1
#define NX_COLORMASK		2
#define NX_ALPHAMASK		4
#define NX_PALETTEMASK		8

/* isPlanar values */
#define NX_MESHED		1
#define NX_PLANAR		2	

APPKIT_EXTERN void NXReadBitmap(const NXRect *rect, int w, int h, int bps, int spp, 
				int planarConfig, int photoInt,
				void *data1, void *data2, void *data3,
				void *data4, void *data5 );

APPKIT_EXTERN void NXSizeBitmap(const NXRect *rect, int *size, int *width, 
    int *height, int *bps, int *spp, int *planarConfig, int *photoInt );

APPKIT_EXTERN void NXCopyBitmapFromGState (int srcGState,
					const NXRect *srcRect,
					const NXRect *destRect);


/*
 * NXContainRect() is obsolete and used in the 1.0 API.
 */
APPKIT_EXTERN int NSContainRect(NXRect *aRect, const NXRect *bRect);
