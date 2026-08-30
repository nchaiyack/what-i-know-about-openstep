/* SelectionNotifMatrix.h created by tjdono on Fri 03-Nov-1995 */

#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

extern NSString *SelectionInMatrixNotification;

@interface SelectionNotifMatrix : NSMatrix
{
}

- (void)mouseDown:(NSEvent *)theEvent;

@end
