/*
        NSTableHeaderView.h
        Application Kit
        Copyright (c) 1995-1996, NeXT Software, Inc.
        All rights reserved.
*/

#ifndef STRICT_OPENSTEP

#import <AppKit/NSView.h>

@class NSTableView;
@class NSColor;
@class NSImage;
@class NSCursor;

@interface NSTableHeaderView : NSView
{
    NSTableView			*_tableView;
    int				_resizedColumn;
    int				_draggedColumn;
    int				_mayDragColumn;
    NSImage			*_headerDragImage;
    float			_draggedDistance;
    NSCursor			*_resizeCursor;
    BOOL			_drawingLastColumn;
    void			*_reserved;
}

- (void)setTableView:(NSTableView *)tableView;
- (NSTableView *)tableView;
- (int)draggedColumn;
- (float)draggedDistance;
- (int)resizedColumn;
- (NSRect)headerRectOfColumn:(int)column;
- (int)columnAtPoint:(NSPoint)point;

@end

#endif STRICT_OPENSTEP
