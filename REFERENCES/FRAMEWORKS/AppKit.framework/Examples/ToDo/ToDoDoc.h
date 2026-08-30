#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>
#import "ToDoCell.h"
#import "CalendarMatrix.h"

extern NSString *ToDoItemChangedNotification;
@class ToDoItem;

@interface ToDoDoc:NSObject
{
    id	itemMatrix;
    id	markMatrix;
    id  calendar;
    id  dayLabel;

    NSMutableDictionary *activeDays;
    NSMutableArray *currentItems;
    BOOL itemsNeedSaving;
}

/* accessor methods */
- (NSMutableArray *)currentItems;
- (void)setCurrentItems:(NSMutableArray *)newItems;
- (NSMatrix *)itemMatrix;
- (NSMatrix *)markMatrix;
- (NSMutableDictionary *)activeDays;
- (CalendarMatrix *)calendar;

/* matrix/data management */
- (void)updateMatrix;
- (void)selectionInMatrix:(NSNotification *)notif;
- (void)itemChecked:sender;
- (void)saveDocItems;
- (void)selectItem:(int)item;

/* document management */
- (void)saveDoc;

/* item timer management */
- (void)itemTimerFired:(id)timer;
- (void)setTimerForItem:(ToDoItem *)anItem;

/* housekeeping */
- (id)initWithFile:(NSString *)aFile;
- (void)dealloc;
- (void)activateDoc;

@end
