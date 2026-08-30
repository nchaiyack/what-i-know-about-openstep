/*
        NSMenu.h
        Application Kit
        Copyright (c) 1995-1996, NeXT Software, Inc.
        All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/NSMenuItem.h>

@class NSEvent;

@interface NSMenu : NSObject <NSCoding> {
    @private
    unsigned char _pad[156];
}

+ (void)setMenuZone:(NSZone *)aZone;
+ (NSZone *)menuZone;


- (id)initWithTitle:(NSString *)aTitle;

- (NSString *)title;
- (void)setTitle:(NSString *)aString;

- (id <NSMenuItem>)insertItemWithTitle:(NSString *)aString action:(SEL)aSelector keyEquivalent:(NSString *)charCode atIndex:(unsigned int)index;
- (id <NSMenuItem>)addItemWithTitle:(NSString *)aString action:(SEL)aSelector keyEquivalent:(NSString *)charCode;
- (void)removeItem:(id <NSMenuItem>)item;
- (void)setSubmenu:(NSMenu *)aMenu forItem:(id <NSMenuItem>)anItem;
- (NSMenu *)supermenu;
- (NSMenu *)attachedMenu;
- (BOOL)isAttached;
- (BOOL)isTornOff;
- (void)sizeToFit;
- (void)setAutoenablesItems:(BOOL)flag;
- (BOOL)autoenablesItems;
- (id <NSMenuItem>)itemWithTag:(int)aTag;
- (id <NSMenuItem>)itemWithTitle:(NSString *)aTitle;
- (NSArray *)itemArray;
- (NSPoint)locationForSubmenu:(NSMenu *)aSubmenu;

- (BOOL)performKeyEquivalent:(NSEvent *)theEvent;
- (void)update;

#ifndef STRICT_OPENSTEP
- (void)setMenuChangedMessagesEnabled:(BOOL)flag;
- (BOOL)menuChangedMessagesEnabled;

- (void)helpRequested:(NSEvent *)eventPtr;
#endif

@end

@interface NSMenu(NSSubmenuAction)
- (void)submenuAction:(id)sender;
@end

@interface NSObject(NSMenuValidation)
- (BOOL)validateMenuItem:(id <NSMenuItem>)menuItem;
@end

