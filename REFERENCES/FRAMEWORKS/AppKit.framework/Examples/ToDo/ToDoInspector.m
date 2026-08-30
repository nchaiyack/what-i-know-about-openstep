/*
  You may freely copy, distribute, and reuse the code in this example.
  NeXT disclaims any warranty of any kind, expressed or implied, as to its
  fitness for any particular use.
*/

#import "ToDoInspector.h"

enum { notifTag = 0, reschedTag, notesTag };

static void clearButtonMatrix(id matrix);

@implementation ToDoInspector


- (void)awakeFromNib
{
    [inspPopUp selectItemAtIndex:0];
    [inspNotes setDelegate:self];

    /* remove inspector content views from superview, retain them, */
    /* and zap off-screen window */


    [[notifView contentView] removeFromSuperview];
    notifView = [[notifView contentView] retain];
    [[reschedView contentView] removeFromSuperview];
    reschedView = [[reschedView contentView] retain];
    [[notesView contentView] removeFromSuperview];
    notesView = [[notesView contentView] retain];
    [inspectorViews release];
    [self newInspectorView:self];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(currentItemChanged:) name:ToDoItemChangedNotification object:nil];
}

- (void)dealloc
{
    [notifView release];
    [reschedView release];
    [notesView release];
}

/* ************ INSPECTOR MANAGEMENT **************************
/* When an item is added, changed, or deleted, or when a new item is
/* selected in the document, currentItem and itemidx are updated via
/* notification.
   *********************************************************** */

/* Update the currentItem with the values on the current inspector view */
/*
   
/* update the currentItem, then switch to the chosen inspector view */

- (void)newInspectorView:(id)sender
{
    NSBox *newView=nil;
    NSView *cView = [[inspPopUp window] contentView];
    int selected = [[inspPopUp selectedItem] tag];

    switch(selected){
      case notifTag:
        newView = notifView;
        break;
      case reschedTag:
        newView = reschedView;
        break;
      case notesTag:
        newView = notesView;
        break;
    }  
    if ([[cView subviews] containsObject:newView]) return;
    [(NSBox *)dummyView setContentView:newView];
    if (newView == notifView) [inspNotifHour selectText:self];
    if (newView == notesView) [inspNotes setSelectedRange:NSMakeRange(0,0)];
    [self updateInspector:currentItem];
    [cView setNeedsDisplay:YES];
}

/* Opposite of updateItem: takes the appropriate values from the currentItem (ToDoItem) */
/* and updates the current inspector view with it */

- (void)updateInspector:(ToDoItem *)newItem
{
    int minute=0, hour=0, selected=0;
    selected = [[inspPopUp selectedItem] tag];
    [[inspPopUp window] orderFront:self];
    if (newItem && [newItem isKindOfClass:[ToDoItem class]]) {
        // add info pertinent to display from currentItem
        [inspItem setStringValue:[newItem itemName]];
        [inspDate setStringValue:[[newItem day] descriptionWithCalendarFormat:@"%a, %b %d %Y" timeZone:[NSTimeZone localTimeZone] locale:nil]];

        switch(selected) {
            case notifTag: {
                BOOL ampm;
                long notifSecs, dueSecs = [newItem secsUntilDue];
                ampm = ConvertSecondsToTime(dueSecs, &hour, &minute);
                [[inspNotifAMPM cellAtRow:0 column:0] setState:!ampm];
                [[inspNotifAMPM cellAtRow:0 column:1] setState:ampm];
                [inspNotifHour setIntValue:hour];
                [inspNotifMinute setIntValue:minute];
                notifSecs = dueSecs - [newItem secsUntilNotif];
                if (notifSecs == dueSecs) notifSecs = 0;
                clearButtonMatrix(inspNotifSwitchMatrix);
                switch(notifSecs) {
                  case 0:
                    [[inspNotifSwitchMatrix cellAtRow:0 column:0] setState:YES];
                    break;
                  case (hrInSecs/4):
                    [[inspNotifSwitchMatrix cellAtRow:1 column:0] setState:YES];
                    break;
                  case (hrInSecs):
                    [[inspNotifSwitchMatrix cellAtRow:2 column:0] setState:YES];
                    break;
                  case (dayInSecs):
                    [[inspNotifSwitchMatrix cellAtRow:3 column:0] setState:YES];
                    break;
                  default:  /* Other */
                    [[inspNotifSwitchMatrix cellAtRow:4 column:0] setState:YES];
                    [inspNotifOtherHours setIntValue:((dueSecs-notifSecs)/hrInSecs)];
                    break;
                }
                break;
            }
          case reschedTag:
            break;

          case notesTag:            
            [inspNotes setString:[newItem notes]];
            [inspNotes setSelectedRange:NSMakeRange(0,0)];
        }
    }
    else if (!newItem) { /* newItem is nil */
      /* blank out fields */
        [inspItem setStringValue:@""];
        [inspDate setStringValue:@""];
        [inspNotifHour setStringValue:@""];
        [inspNotifMinute setStringValue:@""];
        [[inspNotifAMPM cellAtRow:0 column:0] setState:YES];
        [[inspNotifAMPM cellAtRow:0 column:1] setState:NO];
        clearButtonMatrix(inspNotifSwitchMatrix);
        [[inspNotifSwitchMatrix cellAtRow:0 column:0] setState:YES];
        [inspNotifOtherHours setStringValue:@""];
        [inspNotes setString:@""];
    }
}

- (void)switchChecked:(id)sender
{
    long tmpSecs=0;
    int idx = 0;
    id doc = [[NSApp mainWindow] delegate];
    if (sender == inspNotifAMPM) {
        if ([inspNotifHour intValue]) {
            tmpSecs = ConvertTimeToSeconds([inspNotifHour intValue], [inspNotifMinute intValue], [[sender cellAtRow:0 column:1] state]);
            [currentItem setSecsUntilDue:tmpSecs];
            [[NSApp mainWindow] setDocumentEdited:YES];
            [doc updateMatrix];
        }
    } else if (sender == inspNotifSwitchMatrix) {
        idx = [inspNotifSwitchMatrix selectedRow];
        tmpSecs = [currentItem secsUntilDue];
        switch(idx) {
          case 0:
            [currentItem setSecsUntilNotif:0];
            break;
          case 1:
            [currentItem setSecsUntilNotif:tmpSecs-(hrInSecs/4)];
            break;
          case 2:
            [currentItem setSecsUntilNotif:tmpSecs-hrInSecs];
            break;
          case 3:
            [currentItem setSecsUntilNotif:tmpSecs-dayInSecs];
            break;
          case 4:  // Other
            [currentItem setSecsUntilNotif:([inspNotifOtherHours intValue] * hrInSecs)];
            break;
          default:
            NSLog(@"Error in selectedRow");
            break;
        }
        [[NSApp mainWindow] setDocumentEdited:YES];
        [doc setTimerForItem:currentItem];
        
    } else if (sender == inspSchedComplete) {
        [currentItem setItemStatus:complete];
        [doc updateMatrix];
        [[NSApp mainWindow] setDocumentEdited:YES];

    } else if (sender == inspSchedMatrix) {

    }
}

- (void)resetNotifSwitch
{
    clearButtonMatrix(inspNotifSwitchMatrix);
    [[inspNotifSwitchMatrix cellAtRow:0 column:0] setState:YES];
    [inspNotifSwitchMatrix display];
}

- (void)setCurrentItem:(ToDoItem *)newItem
{
    if (currentItem) [currentItem autorelease];
    if (newItem)
        currentItem = [newItem retain];
    else
        currentItem = nil;
    [self updateInspector:currentItem];
}

- (ToDoItem *)currentItem { return currentItem; }

- (void)textDidEndEditing:(NSNotification *)notif
{
    if ([notif object] == inspNotes) {
        [currentItem setNotes:[inspNotes string]];
        [[NSApp mainWindow] setDocumentEdited:YES];
    }
}

- (void)controlTextDidEndEditing:(NSNotification *)notif
{
    long tmpSecs=0;
    if ([notif object] == inspNotifHour ||
        [notif object] == inspNotifMinute) {

        tmpSecs = ConvertTimeToSeconds([inspNotifHour intValue], [inspNotifMinute intValue], [[inspNotifAMPM cellAtRow:0 column:1] state]);
        [currentItem setSecsUntilDue:tmpSecs];
        [[[NSApp mainWindow] delegate] updateMatrix];
        [[NSApp mainWindow] setDocumentEdited:YES];
    } else if ([notif object] == inspNotifOtherHours) {
        if ([inspNotifSwitchMatrix selectedRow] == 4) {
            [currentItem setSecsUntilNotif:([inspNotifOtherHours intValue] * hrInSecs)];
            [[[NSApp mainWindow] delegate] setTimerForItem:currentItem];
            [[NSApp mainWindow] setDocumentEdited:YES];
        }
    } else if ([notif object] == inspSchedDate) {

    }
}

- (void)windowDidResignMain:(NSNotification *)notif
{
    id doc = [[NSApp mainWindow] delegate];
    if ([doc isKindOfClass:[ToDoDoc class]]) {
        [[NSApp mainWindow] makeFirstResponder:[NSApp mainWindow]];
        [doc saveDocItems];
    }
}

- (BOOL)windowShouldClose:(id)sender  /* Inspector window */
{
    id doc = [[NSApp mainWindow] delegate];
    if ([doc isKindOfClass:[ToDoDoc class]]) { 
        [[NSApp mainWindow] makeFirstResponder:[NSApp mainWindow]];
        [doc saveDocItems];
    }
    return YES;
}

- (void)currentItemChanged:(NSNotification *)notif
{
    [self setCurrentItem:[notif object]];
}

/* Utility routine */
void clearButtonMatrix(id matrix)
{
    int i, rows, cols;
    [matrix getNumberOfRows:&rows columns:&cols];
    for(i=0; i<rows; i++)
        [[matrix cellAtRow:i column:0] setState:NO];
}

@end

