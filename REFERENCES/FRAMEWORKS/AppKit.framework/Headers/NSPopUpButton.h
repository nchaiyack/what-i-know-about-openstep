/*
	NSPopUpButton.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/NSButton.h>
#import <AppKit/NSMenuItem.h>
#import <AppKit/AppKitDefines.h>

@class NSString;
@class NSFont;
@class NSMatrix;

@interface NSPopUpButton : NSButton
{
    id			_target;     
    SEL			_action;
    struct __popUpButtonFlags {
        unsigned int	pullsDown:1;
        unsigned int    usingColorizedImages:1;
	unsigned int	shouldReleasePopUpList:1;
        unsigned int	reservedPopUpButton:29;
    } _pbFlags;
}

- (id)initWithFrame:(NSRect)buttonFrame pullsDown:(BOOL)flag;

- (void)setPullsDown:(BOOL)flag;
- (BOOL)pullsDown;

- (NSArray *)itemArray;

- (int)numberOfItems;
- (void)addItemWithTitle:(NSString *)title;
- (void)addItemsWithTitles:(NSArray *)itemTitles;
- (void)insertItemWithTitle:(NSString *)title atIndex:(int)index;
- (void)removeItemWithTitle:(NSString *)title;
- (void)removeItemAtIndex:(int)index;
- (void)removeAllItems;
- (void)synchronizeTitleAndSelectedItem;
- (void)selectItemWithTitle:(NSString *)title;
- (void)selectItemAtIndex:(int)index;
- (id <NSMenuItem>)itemAtIndex:(int)index;
- (id <NSMenuItem>)itemWithTitle:(NSString *)title;
- (id <NSMenuItem>)selectedItem;
- (id <NSMenuItem>)lastItem;
- (NSString *)itemTitleAtIndex:(int)index;
- (NSString *)titleOfSelectedItem;
- (int)indexOfSelectedItem;
- (int)indexOfItemWithTitle:(NSString *)title;
- (NSArray *)itemTitles;
- (void)setFont:(NSFont *)fontObject;

	/* This is a no-op in NSControl, but it is here because we override */
	/* it to return the titleOfSelectedItem. This is useful if there is */
	/* a TextField or something that is supposed to reflect the most */
	/* recent PopUp selection. */
- (NSString *)stringValue;
	/* Adds semantic to NSButton's method that if there is no item in */
	/* popup matching title, then an item of that name is added. */
- (void)setTitle:(NSString *)aString;
- (id)target;
- (void)setTarget:(id)anObject;
- (SEL)action;
- (void)setAction:(SEL)aSelector;
- (void)setAutoenablesItems:(BOOL)flag;
- (BOOL)autoenablesItems;

@end


#ifndef STRICT_OPENSTEP

/* Notifications */
APPKIT_EXTERN NSString *NSPopUpButtonWillPopUpNotification;

#endif

