/* ColorRect.m
 *
 * by Nik Gervae, Technical Publications, NeXT Software Inc.
 *
 * You may freely copy, distribute, and reuse the code in this example.
 * NeXT disclaims any warranty of any kind, expressed or  implied, as to
 * its fitness for any particular use.
 */


#import "ColorRect.h"

@implementation ColorRect

- (id)initWithFrame:(NSRect)aRect color:(NSColor *)aColor
{
    self = [super init];
    if (!self) return nil;
    frame = aRect;
    color = [aColor copyWithZone:[self zone]];
    return self;
}

- (void)setFrame:(NSRect)aRect
{
    frame = aRect;
    return;
}

- (NSRect)frame
{
    return frame;
}

- (NSColor *)color
{
    return color;
}

- (void)setLocked:(BOOL)flag
{
    locked = flag;
    return;
}


- (BOOL)isLocked
{
    return locked;
}


- (void)drawRect:(NSRect)aRect selected:(BOOL)flag
{
    NSRect dRect;

    PSgsave();
    NSRectClip(aRect);

    dRect = NSIntersectionRect(aRect, frame);
    [color set];
    NSRectFill(dRect);

    if (flag) {
        [[NSColor blackColor] set];
        PSsetlinewidth(4.0);
        NSFrameRect(frame);
    }

    if (locked) {
        float xSize;

        [[NSColor blackColor] set];
        PSsetlinewidth(3.0);

        if (NSWidth(frame) > 10.0) xSize = 5.0;
        else xSize = 2.0;

        PSmoveto(NSMidX(frame) - xSize, NSMidY(frame) - xSize);
        PSlineto(NSMidX(frame) + xSize, NSMidY(frame) + xSize);
        PSmoveto(NSMidX(frame) - xSize, NSMidY(frame) + xSize);
        PSlineto(NSMidX(frame) + xSize, NSMidY(frame) - xSize);
        PSstroke();
    }

    PSgrestore();

    return;
}


@end
