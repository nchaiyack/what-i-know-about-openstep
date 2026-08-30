/*
	NSDataLinkPanel.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#ifndef STRICT_OPENSTEP

#import <AppKit/NSApplication.h>
#import <AppKit/NSPanel.h>

@class NSDataLinkManager;
@class NSDataLink;

@interface NSDataLinkPanel : NSPanel {
  /* these instance variables are NOT part of the API, are subject to change in future releases */
  @private
    id	_bannerMsg;
    id	_breakLink;
    id	_openSource;
    id	_updateDestination;
    id	_updateMode;
    id	_breakAllLinks;
    id	_showOutlines;
    id	_sourceTitle;
    id	_sourceValue;
    id	_lastUpdateTitle;
    id	_lastUpdateValue;
    id	_accessoryView;
    BOOL _needsUpdate;
    BOOL _reservedDataLinkPanel1;
    BOOL _reservedDataLinkPanel2;
    BOOL _reservedDataLinkPanel3;
    int _reservedDataLinkPanel4;
}

+ (NSDataLinkPanel *)sharedDataLinkPanel;

+ (void)setLink:(NSDataLink *)link manager:(NSDataLinkManager *)linkManager isMultiple:(BOOL)flag;
+ (void)getLink:(NSDataLink **)link manager:(NSDataLinkManager **)linkManager isMultiple:(BOOL *)flag;

- (void)setLink:(NSDataLink *)link manager:(NSDataLinkManager *)linkManager isMultiple:(BOOL)flag;
- (void)getLink:(NSDataLink **)link manager:(NSDataLinkManager **)linkManager isMultiple:(BOOL *)flag;

- (void)setAccessoryView:(NSView *)aView;
- (NSView *)accessoryView;

- (void)pickedBreakLink:(id)sender;
- (void)pickedOpenSource:(id)sender;
- (void)pickedUpdateDestination:(id)sender;
- (void)pickedUpdateMode:(id)sender;
- (void)pickedBreakAllLinks:(id)sender;

@end


@interface NSApplication(NSDataLinkPanel)
- (void)orderFrontDataLinkPanel:(id)sender;
@end

#endif STRICT_OPENSTEP
