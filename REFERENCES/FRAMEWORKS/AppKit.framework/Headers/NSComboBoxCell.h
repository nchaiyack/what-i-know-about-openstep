/*
	NSComboBoxCell.h
	Application Kit
	Copyright (c) 1996, NeXT Software, Inc.
	All rights reserved.
*/

#if !defined(STRICT_OPENSTEP) && !defined(STRICT_40) && !defined(STRICT_41)

#import <AppKit/NSTextFieldCell.h>
#import <AppKit/NSTableView.h>

@interface NSComboBoxCell : NSTextFieldCell   {
    id _delegate;
    id _dataSource;
    struct __cbcFlags {
	unsigned int usesDataSource:1;
	unsigned int reserved:15;
	unsigned int visibleItems:16;
    } _cbcFlags;
    NSButtonCell *_buttonCell;
    NSTableView *_tableView;
    NSScrollView *_scrollView;
    NSWindow *_popUp;
    NSMutableArray *_popUpList;
    NSRect *_cellFrame;
    void *_reserved;
 }

- (BOOL)hasVerticalScroller;
- (void)setHasVerticalScroller:(BOOL)flag;
- (NSSize)intercellSpacing; 
- (void)setIntercellSpacing:(NSSize)aSize; 
- (float)itemHeight;
- (void)setItemHeight:(float)itemHeight; 
- (int)numberOfVisibleItems;
- (void)setNumberOfVisibleItems:(int)visibleItems;

- (void)reloadData;
- (void)noteNumberOfItemsChanged;

- (void)setUsesDataSource:(BOOL)flag;
- (BOOL)usesDataSource;

- (void)scrollItemAtIndexToTop:(int)index;
- (void)scrollItemAtIndexToVisible:(int)index;

- (void)selectItemAtIndex:(int)index;
- (void)deselectItemAtIndex:(int)index;
- (int)indexOfSelectedItem;
- (int)numberOfItems;

- (void)encodeWithCoder:(NSCoder *)coder;
- (id)initWithCoder:(NSCoder *)coder;

/* These two methods can only be used when usesDataSource is YES */
- (id)dataSource;
- (void)setDataSource:(id)aSource; 

/* These methods can only be used when usesDataSource is NO */
- (void)addItemWithObjectValue:(id)object;
- (void)addItemsWithObjectValues:(NSArray *)objects;
- (void)insertItemWithObjectValue:(id)object atIndex:(int)index;
- (void)removeItemWithObjectValue:(id)object;
- (void)removeItemAtIndex:(int)index;
- (void)removeAllItems;
- (void)selectItemWithObjectValue:(id)object;
- (id)itemObjectValueAtIndex:(int)index;
- (id)objectValueOfSelectedItem;
- (int)indexOfItemWithObjectValue:(id)object;
- (NSArray *)objectValues;

@end

@interface NSObject (NSComboBoxCellDataSource)
- (int)numberOfItemsInComboBoxCell:(NSComboBoxCell *)comboBoxCell;
- (id)comboBoxCell:(NSComboBoxCell *)aComboBoxCell objectValueForItemAtIndex:(int)index;
- (unsigned int)comboBoxCell:(NSComboBoxCell *)aComboBoxCell indexOfItemWithStringValue:(NSString *)string;
@end

#endif
