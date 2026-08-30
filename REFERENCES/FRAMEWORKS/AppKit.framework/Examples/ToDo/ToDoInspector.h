#import <AppKit/AppKit.h>
#import "ToDoItem.h"
#import "ToDoDoc.h"

@interface ToDoInspector : NSObject
{
    ToDoItem *currentItem;
 
    id dummyView;
    id inspDate;
    id inspectorViews;
    id inspItem;
    id inspNotes;
    id inspNotifAMPM;
    id inspNotifHour;
    id inspNotifMinute;
    id inspNotifOtherHours;
    id inspNotifSwitchMatrix;
    id inspPopUp;
    id inspSchedComplete;
    id inspSchedDate;
    id inspSchedMatrix;
    id notesView;
    id notifView;
    id reschedView;
}
- (void)newInspectorView:(id)sender;
- (void)switchChecked:(id)sender;
- (void)resetNotifSwitch;
- (void)setCurrentItem:(ToDoItem *)newItem;
- (ToDoItem *)currentItem;
- (void)updateInspector:(ToDoItem *)item;
- (void)currentItemChanged:(NSNotification *)notif;
@end
