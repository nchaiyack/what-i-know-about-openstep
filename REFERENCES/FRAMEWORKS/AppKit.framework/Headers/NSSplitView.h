/*
	NSSplitView.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#import <AppKit/NSView.h>
#import <AppKit/AppKitDefines.h>

@interface NSSplitView : NSView {
    id	_delegate;
}

- (void)setDelegate:(id)anObject;
- (id)delegate;
- (void)adjustSubviews;
- (float)dividerThickness;
- (void)drawDividerInRect:(NSRect)aRect;

#if !defined(STRICT_OPENSTEP) && !defined(STRICT_40) && !defined(STRICT_41)
- (void)setVertical:(BOOL)flag;	/* Vertical splitview has a vertical split bar */ 
- (BOOL)isVertical;
#endif

@end

@interface NSObject(NSSplitViewDelegate)
- (void)splitView:(NSSplitView *)sender resizeSubviewsWithOldSize:(NSSize)oldSize;
- (void)splitView:(NSSplitView *)sender constrainMinCoordinate:(float *)min maxCoordinate:(float *)max ofSubviewAt:(int)offset;
- (void)splitViewWillResizeSubviews:(NSNotification *)notification;
- (void)splitViewDidResizeSubviews:(NSNotification *)notification;
@end

/* Notifications */
APPKIT_EXTERN NSString *NSSplitViewDidResizeSubviewsNotification;
APPKIT_EXTERN NSString *NSSplitViewWillResizeSubviewsNotification;
