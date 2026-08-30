/* SelectionNotifMatrix.m created by tjdono on Fri 03-Nov-1995 */

#import "SelectionNotifMatrix.h"

NSString *SelectionInMatrixNotification = @"SelectionInMatrixNotification";
   
@implementation SelectionNotifMatrix

- (void)mouseDown:(NSEvent *)theEvent
{
    int row;
    [super mouseDown:theEvent];
    
    row = [self selectedRow];
    if (row != -1) {
        [[NSNotificationCenter defaultCenter]
 postNotificationName:SelectionInMatrixNotification
               object:self
             userInfo:[NSDictionary dictionaryWithObjectsAndKeys:
                 [NSNumber numberWithInt:row], @"ItemIndex", nil]];
    }
}


@end
