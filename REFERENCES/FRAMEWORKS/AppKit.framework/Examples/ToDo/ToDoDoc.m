/*
  You may freely copy, distribute, and reuse the code in this example.
  NeXT disclaims any warranty of any kind, expressed or implied, as to its
  fitness for any particular use.
*/

#import "ToDoDoc.h"
#import "ToDoController.h"
#import "ToDoInspector.h"
#import "ToDoItem.h"
#import "CalendarMatrix.h"
#import "SelectionNotifMatrix.h"

extern void clearButtonMatrix(id matrix);

NSString *ToDoItemChangedNotification = @"ToDoItemChangedNotification";

@implementation ToDoDoc

/******************** MATRIX MANAGEMENT (item fields and time cells) ***********/

/* display itemNames in itemMatrix and update markMatrix cells with times & state */

- (void)updateMatrix
{
    int i, cnt = [currentItems count], rows = [[itemMatrix cells] count];
    ToDoItem *thisItem;

    for (i=0; ( i<cnt || i<rows); i++) {
        NSDate *due;
        thisItem = [currentItems objectAtIndex:i];
        if ([thisItem isKindOfClass:[ToDoItem class]]) {
            if ( [thisItem secsUntilDue] )
                due = [[thisItem day] addTimeInterval:[thisItem secsUntilDue]];
            else
                due = nil;
            [[itemMatrix cellAtRow:i column:0] setStringValue:[thisItem itemName]];
            [[markMatrix cellAtRow:i column:0] setTimeDue:due];
            [[markMatrix cellAtRow:i column:0] setTriState:[thisItem itemStatus]];
        }
        else  {
            [[itemMatrix cellAtRow:i column:0] setStringValue:@""];
            [[markMatrix cellAtRow:i column:0] setTitle:@""];
            [[markMatrix cellAtRow:i column:0] setImage:nil];
        }
    }
}

- (void)selectItem:(int)item
{
    id thisItem = [currentItems objectAtIndex:item];
    [itemMatrix selectCellAtRow:item column:0];
    if (thisItem) {
        if (![thisItem isKindOfClass:[ToDoItem class]]) thisItem = nil;
        [[NSNotificationCenter defaultCenter]
postNotificationName:ToDoItemChangedNotification
              object:thisItem
            userInfo:nil];
    }
}

- (void)itemChecked:sender
{
    int row = [sender selectedRow];
    ToDoCell *cell = [sender cellAtRow:row column:0];
    if (cell && [currentItems count]) {
        id item = [currentItems objectAtIndex:row];
        if (item && [item isKindOfClass:[ToDoItem class]]) {
            [item setItemStatus:[cell triState]];
            [[sender window] setDocumentEdited:YES];
        }
    }
}


/******************* STARTUP AND SHUTDOWN ***************************/
   
- initWithFile:(NSString *)aFile
{
    NSEnumerator *dayenum;
    NSDate *itemDate;

    [super init];

    if (aFile) {
        activeDays = [NSUnarchiver unarchiveObjectWithFile:aFile];
        if (activeDays) 
            activeDays = [activeDays retain];
        else {
            NSRunAlertPanel(@"To Do", @"Couldn't unarchive file %@", nil, nil, nil, aFile);
            return nil;
        }
    } else {
        activeDays = [[NSMutableDictionary alloc] init];
        [self setCurrentItems:nil];
    }

    if (![NSBundle loadNibNamed:@"ToDoDoc.nib" owner:self] )
          return nil;

    if (aFile)
        [[itemMatrix window] setTitleWithRepresentedFilename:aFile];
    else
        [[itemMatrix window] setTitle:@"UNTITLED"];

    // traverse activeDays->items and re-set timers
    if ([self activeDays]) {
        dayenum = [[self activeDays] keyEnumerator];
        while (itemDate = [dayenum nextObject]) {
            NSEnumerator *itemenum;
            ToDoItem *anItem=nil;
            NSArray *itemArray = [[self activeDays] objectForKey:itemDate];
            itemenum = [itemArray objectEnumerator];
            while ((anItem = [itemenum nextObject]) &&
                   [anItem isKindOfClass:[ToDoItem class]] &&
                   [anItem secsUntilNotif]) {
                [self setTimerForItem:anItem];
            }
        }
    }
    [[itemMatrix window] makeKeyAndOrderFront:self];   
    return self;
}

- (void)awakeFromNib
{
    int i;
    NSDate *date;
     
    // get the items for today
    date = [calendar selectedDay];
    [self setCurrentItems:[activeDays objectForKey:date]];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(selectionInMatrix:) name:@"SelectionInMatrixNotification" object:itemMatrix];

    /* set up self as delegates */
    [[itemMatrix window] setDelegate:self];
    [itemMatrix setDelegate:self];

    /* replace markMatrix with ToDoCells */
    i = [[markMatrix cells] count];
    while (i--) {
        ToDoCell *aCell = [[ToDoCell alloc] init];
        [aCell setTarget:self];
        [aCell setAction:@selector(itemChecked:)];
        [markMatrix putCell:aCell atRow:i column:0];
        [aCell release];
    }

    
 }

- (void)activateDoc
{
    if ([currentItems count]) [self updateMatrix];
    [dayLabel setStringValue:[[calendar selectedDay] descriptionWithCalendarFormat:@"To Do on %a %B %d %Y" timeZone:[NSTimeZone defaultTimeZone] locale:nil]];
}

- (void)dealloc
{
    if (activeDays) [activeDays release];
    if (currentItems) [currentItems release];
    [super dealloc];
}

/*********************** ACCESSOR METHODS **************************************/
   
- (NSMatrix *)itemMatrix {return itemMatrix;}

- (NSMatrix *)markMatrix {return markMatrix;}

- (NSMutableDictionary *)activeDays { return activeDays; }

- (CalendarMatrix *)calendar { return calendar; }

- (NSMutableArray *)currentItems { return currentItems; }

- (void)setCurrentItems:(NSMutableArray *)newItems
{
    if (currentItems) [currentItems autorelease];

    if (newItems) 
        currentItems = [newItems mutableCopy];
    else {
        int numRows, numCols;
        [itemMatrix getNumberOfRows:&numRows columns:&numCols];
        currentItems = [[NSMutableArray alloc] initWithCapacity:numRows];
        while (--numRows >= 0)
            [currentItems addObject:@""];
    }        
}


/************************ SAVING THE DOCUMENT ***********************************/
   
- (void)saveDocItems
{
    ToDoItem *anItem;
    int i, cnt = [currentItems count];
    // save day's current items (array) to document dictionary
    for (i=0; i<cnt; i++) {
        if ( (anItem = [currentItems objectAtIndex:i])  &&
             ([anItem isKindOfClass:[ToDoItem class]]) ) {
            [activeDays setObject:currentItems forKey:[anItem day]];
            break;
        }
    }
}

- (void)saveDoc
{
    NSString *fn;

    if (![[[itemMatrix window] title] hasPrefix:@"UNTITLED"]) {
        fn = [[itemMatrix window] representedFilename];
    } else {
        int result;
        NSSavePanel *sPanel = [NSSavePanel savePanel];
        [sPanel setRequiredFileType:@"td"];
        result = [sPanel runModalForDirectory:NSHomeDirectory() file:nil];
        if (result == NSOKButton) {
            fn = [sPanel filename];
            [[itemMatrix window] setTitleWithRepresentedFilename:fn];
            if (fn && ![fn isEqualToString:@""]) {
                NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
                [defaults setObject:fn forKey:@"ToDoDocumentLastSaved"];
                [defaults synchronize];
            }
        } else
            return;
    }
    if (![NSArchiver archiveRootObject:activeDays toFile:fn])
        NSRunAlertPanel(@"To Do", @"Couldn't archive file %@", nil, nil, nil, fn);
    else
        [[itemMatrix window] setDocumentEdited:NO];
}


/************************ SETTING AND RESPONDING TO TIMERS ***************************/
   
- (void)setTimerForItem:(ToDoItem *)anItem
{
    NSDate *notifDate;
    NSTimer *aTimer;
    if ([anItem secsUntilNotif]) {
        notifDate = [[anItem day] addTimeInterval:[anItem secsUntilNotif]];
        aTimer = [NSTimer scheduledTimerWithTimeInterval:[notifDate timeIntervalSinceNow]
                                         target:self
                                       selector:@selector(itemTimerFired:)
                                       userInfo:anItem
                                        repeats:NO];
        [anItem setItemTimer:aTimer];
    } else  // remove timer
        [[anItem itemTimer] invalidate];
}

- (void)itemTimerFired:(id)timer
{
    id anItem = [timer userInfo];
    ToDoInspector *inspController = [[[NSApp delegate] inspector] delegate];
    NSDate *dueDate = [[anItem day] addTimeInterval:[anItem secsUntilDue]];

    NSBeep();
    NSRunAlertPanel(@"To Do", @"%@ on %@", nil, nil, nil, [anItem itemName], [dueDate descriptionWithCalendarFormat:@"%b %d, %Y at %I:%M %p" timeZone:[NSTimeZone defaultTimeZone] locale:nil]);
    [anItem setSecsUntilNotif:0];
    [inspController resetNotifSwitch];   
}

/*************************** DOCUMENT MANAGEMENT--DELEGATION *****************/

- (void)controlTextDidChange:(NSNotification *)notif
{
    [[itemMatrix window] setDocumentEdited:YES];
}


- (void)controlTextDidEndEditing:(NSNotification *)notif
{
    id curItem, newItem;
    int row = [itemMatrix selectedRow];
    NSString *selName = [[itemMatrix selectedCell] stringValue];

    // here save the item just modified, if any
    // Note: matrix of fields and array of items should mirror each other

    if (![[itemMatrix window] isDocumentEdited] ||
        (row >= [currentItems count])) return;
    if (![self currentItems])
        [self setCurrentItems:nil];
        
    // Empty entry means delete corresponding item
    if ([selName isEqualToString:@""] && 
        ([[currentItems objectAtIndex:row] isKindOfClass:[ToDoItem class]]) &&
        (![[[currentItems objectAtIndex:row] itemName] isEqualToString:@""])) 
        [currentItems replaceObjectAtIndex:row withObject:@""];
    
    // change name if matching currentItem has name
    else if ([[currentItems objectAtIndex:row] isKindOfClass:[ToDoItem class]] &&
             ([[[currentItems objectAtIndex:row] itemName] isEqualToString:selName]) )
        [[currentItems objectAtIndex:row] setItemName:selName];
    
    // item is new, add to currentItems
    else if (![selName isEqualToString:@""]) {
        newItem = [[ToDoItem alloc] initWithName:selName andDate:[calendar selectedDay]];
        [currentItems replaceObjectAtIndex:row withObject:newItem];
        [newItem release];
    }    
    // update the matrix
    [self updateMatrix];

    // post notification to update inspector
    if (curItem = [currentItems objectAtIndex:row]) {
        if (![curItem isKindOfClass:[ToDoItem class]]) curItem = nil;
        [[NSNotificationCenter defaultCenter] postNotificationName:ToDoItemChangedNotification object:curItem userInfo:nil];
    }
   
}

- (void)selectionInMatrix:(NSNotification *)notif
{
    id curItem;
    int row = [itemMatrix selectedRow];

    if (!currentItems || (![[itemMatrix window] isKeyWindow])) return;
    if ( !(row < [currentItems count]) ) return;

    if (curItem = [currentItems objectAtIndex:row]) {
        if (![curItem isKindOfClass:[ToDoItem class]]) curItem = nil;
        [[NSNotificationCenter defaultCenter] postNotificationName:ToDoItemChangedNotification object:curItem userInfo:nil];
    }
}

- (BOOL)windowShouldClose:(id)sender
{
    int result;
    if (![[itemMatrix window] isDocumentEdited]) {
        [[NSNotificationCenter defaultCenter] postNotificationName:ToDoItemChangedNotification object:nil userInfo:nil];
        return YES;
    }
    [[itemMatrix window] makeFirstResponder:[itemMatrix window]];

    result = NSRunAlertPanel(@"Close", @"Document has been edited. Save changes before closing?", @"Save", @"Don't Save", @"Cancel");

    switch(result) {
      case NSAlertDefaultReturn: {
          [self saveDocItems]; 
          [self saveDoc];
          [[NSNotificationCenter defaultCenter] postNotificationName:ToDoItemChangedNotification object:nil userInfo:nil];  
          return YES;
      }
        case NSAlertAlternateReturn: {
            [[NSNotificationCenter defaultCenter] postNotificationName:ToDoItemChangedNotification object:nil userInfo:nil];
          return YES;
        }
        case NSAlertOtherReturn: {
          return NO;
        }
    }
    return NO;
}

- (void)calendarMatrix:(CalendarMatrix *)matrix didChangeToDate:(NSDate *)date
{
    [self saveDocItems]; 

    // use date as key to get currentItems array
    [self setCurrentItems:[activeDays objectForKey:date]];
    [dayLabel setStringValue:[date descriptionWithCalendarFormat:@"To Do on %a %B %d %Y" timeZone:[NSTimeZone defaultTimeZone] locale:nil]];
    [self updateMatrix];
    [self selectItem:0];
}

- (void)calendarMatrix:(CalendarMatrix *)matrix didChangeToMonth:(int)mo year:(int)yr
{
    [self saveDocItems];
    [self setCurrentItems:nil];
    [self updateMatrix];
}



@end

