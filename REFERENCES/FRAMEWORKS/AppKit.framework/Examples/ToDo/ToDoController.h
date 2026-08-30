#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

@interface ToDoController:NSObject
{
    id  inspector;
}

- (void)newDoc:(id)sender;
- (void)openDoc:(id)sender;
- (void)closeDoc:(id)sender;
- (void)saveDoc:(id)sender;

- (void)showInfo:(id)sender;
- (void)showInspector:(id)sender;
- (void)showPreferences:(id)sender;

- (id)inspector;

/* pasteboard copy/paste */
- (void)cutItem:sender;
- (void)copyItem:sender;
- (void)pasteItem:sender;



@end
