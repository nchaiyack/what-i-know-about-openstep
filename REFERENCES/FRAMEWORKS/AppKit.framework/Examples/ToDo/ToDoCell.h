/* A three-state button */

#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

typedef enum _ToDoButtonState {
    notDone=0,
    done, 
    deferred} ToDoButtonState;

@interface ToDoCell : NSButtonCell
{
    ToDoButtonState triState;
    NSImage *doneImage, *deferredImage;
    NSDate *timeDue;
}
- (void)setTriState:(ToDoButtonState)newState;
- (ToDoButtonState)triState;
- (void)setTimeDue:(NSDate *)newTime;
- (NSDate *)timeDue;
@end
