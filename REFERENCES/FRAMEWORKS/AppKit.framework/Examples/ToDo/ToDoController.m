/*
  You may freely copy, distribute, and reuse the code in this example.
  NeXT disclaims any warranty of any kind, expressed or implied, as to its
  fitness for any particular use.
*/

#import "ToDoController.h"
#import "ToDoDoc.h"
#import "ToDoInspector.h"
#import "ToDoItem.h"

extern void clearButtonMatrix(id matrix);

@implementation ToDoController

/******* DOCUMENT MANAGEMENT **********************************/

/******* Target/Action ****************************************/
   
- (void)newDoc:(id)sender
{
    id currentDoc = [[ToDoDoc alloc] initWithFile:nil];
    [currentDoc activateDoc];
}

- (void)openDoc:(id)sender
{
    int result;
    NSString *selected, *startDir;
    NSArray *fileTypes = [NSArray arrayWithObject:@"td"];
    NSOpenPanel *oPanel = [NSOpenPanel openPanel];

    [oPanel setAllowsMultipleSelection:YES];
    if ([[[NSApp keyWindow] delegate] isKindOfClass:[ToDoDoc class]]) 
        startDir = [[[NSApp keyWindow] representedFilename] stringByDeletingLastPathComponent];
    else
        startDir = NSHomeDirectory();    

    result = [oPanel runModalForDirectory:startDir file:nil types:fileTypes];
    if (result == NSOKButton) {
        int i;
        id currentDoc;
        for (i=0; i<[[oPanel filenames] count]; i++) {
              selected = [[oPanel filenames] objectAtIndex:i];
              currentDoc = [[ToDoDoc alloc] initWithFile:selected];
              [currentDoc activateDoc];
              [currentDoc selectItem:0];
        }
    }
}


- (void)closeDoc:(id)sender
{
    if (inspector) [[inspector delegate] setCurrentItem:nil];
    [[NSApp mainWindow] performClose:self];
}


- (void)saveDoc:(id)sender
{
    id currentDoc = [[NSApp mainWindow] delegate];
    if (currentDoc) 
        [currentDoc saveDoc];
}

- (void)showInspector:(id)sender
{
    id currentDoc = [[NSApp mainWindow] delegate];
    if (!inspector)
        if(![NSBundle loadNibNamed:@"ToDoInspector" owner:self])
            return;
    if ([currentDoc isKindOfClass:[ToDoDoc class]])
        [currentDoc selectItem:[[currentDoc itemMatrix] selectedRow]];            
    [inspector makeKeyAndOrderFront:self];
}

- (void)showPreferences:(id)sender
{
    /* Exercise */
    
}

- (void)showInfo:(id)sender
{
    /* Exercise? */
}

- (id)inspector { return inspector; }

/******* Delegation ****************************************/

- (BOOL)applicationOpenUntitledFile:(NSApplication *)sender
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSString *docToOpen = [defaults stringForKey:@"ToDoDocumentLastSaved"];
    if (![docToOpen isEqualToString:@"UNTITLED"] &&
        [[NSFileManager defaultManager] fileExistsAtPath:docToOpen] &&
        [[docToOpen pathExtension] isEqualToString:@"td"]) {
        ToDoDoc *thisDoc = [[ToDoDoc alloc] initWithFile:docToOpen];
        [thisDoc activateDoc];
        [thisDoc selectItem:0];
        return YES;
    }
    [self newDoc:self];    
    return YES;
}

- (BOOL)applicationShouldTerminate:(id)sender
{
    NSString *repfile = nil;
    NSArray *appWindows = [NSApp windows];
    NSEnumerator *enumerator = [appWindows objectEnumerator];
    id object;

    while (object = [enumerator nextObject]) {
        int result;
        id doc;
        if ((doc = [object delegate]) &&
            [doc isKindOfClass:[ToDoDoc class]] &&
            [object isDocumentEdited] ) {
            repfile = [[NSApp keyWindow] representedFilename];
            result = NSRunAlertPanel(@"To Do", @"Save %@?", @"Save", @"Don't Save", @"Cancel", ([repfile isEqualToString:@""] ? [NSString stringWithString:@"UNTITLED"]:repfile));
            switch(result) {
              case NSAlertDefaultReturn:
                [doc saveDocItems];
                [doc saveDoc];
                break;
              case NSAlertAlternateReturn:
                [[NSApp keyWindow] close];
                break;
              case NSAlertOtherReturn:
                return NO;
            }
        }
    }
    return YES;
}

- (void)applicationWillResignActive:(NSNotification *)notif
{
    id doc = [[NSApp keyWindow] delegate];
    if ([doc isKindOfClass:[ToDoDoc class]]) {
        [doc saveDocItems];
    }

}

- (BOOL)application:(id)sender openFile:(NSString *)filename
{
    id currentDoc = [[ToDoDoc alloc] initWithFile:filename];
    if (currentDoc) {
        [currentDoc activateDoc];
        return YES;
    } else {
        return NO;
    }
}

/*************** STARTUP *********************************************/
+ (void)initialize
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSDictionary *regdom = [NSDictionary dictionaryWithObject:@"UNTITLED" forKey:@"ToDoDocumentLastSaved"];
    [defaults registerDefaults:regdom];
 }

- init
{
    [super init];
    [NSApp setDelegate:self];
    return self;
}

/******************************************************************************
**  PASTEBOARD COPY/PASTE
**  The following two methods enable users to cut or copy an item name in a  **
**  text field and when they paste it in another field (in the same or       **
**  other document) the associated ToDoItem is transferred as well. This     **
**  capability depends on the interaction of the pasteboard server and the   **
**  NSPasteboard class. To learn about the conceptual underpinnings of       **
**  pasteboard copy/pase, read the NSPasteboard specification.               **
**  NOTE: To enable this feature, the targets of the items on the Edit menu  **
**  (Cut, Copy, Paste) have been redirected to ToDoController and these      **
**  are the defined action methods.                                          **
******************************************************************************/

- (void)copyItem:sender
{
    BOOL result;
    int row;
    id selItem, doc = [[NSApp mainWindow] delegate];
    if ([doc isKindOfClass:[ToDoDoc class]]) {
        row = [[doc itemMatrix] selectedRow];
        selItem = [[doc currentItems] objectAtIndex:row];
        if ([selItem isKindOfClass:[ToDoItem class]]) {
            NSData *selData = [NSArchiver archivedDataWithRootObject:selItem];
            NSPasteboard *itempb = [NSPasteboard pasteboardWithName:NSGeneralPboard];
            result = [itempb declareTypes:[NSArray arrayWithObject:@"ToDoItemPBType"] owner:nil];
            [itempb setData:selData forType:@"ToDoItemPBType"];
        }
    }
}

- (void)cutItem:sender
{
    id doc = [[NSApp mainWindow] delegate];
    [self copyItem:self];
    [[doc currentItems] replaceObjectAtIndex:[[doc itemMatrix] selectedRow] withObject:@""];
    [doc updateMatrix];
}

- (void)pasteItem:sender
{
    id doc = [[NSApp mainWindow] delegate];
    if ([doc isKindOfClass:[ToDoDoc class]]) {
        int row;
        NSPasteboard *itempb;
        NSData *itemData=nil;
        ToDoItem *newItem;
        row = [[doc itemMatrix] selectedRow];
        itempb = [NSPasteboard pasteboardWithName:NSGeneralPboard];
        if ([[itempb types] containsObject:@"ToDoItemPBType"])
            itemData = [itempb dataForType:@"ToDoItemPBType"];
        newItem = [NSUnarchiver unarchiveObjectWithData:itemData];
        [newItem setDay:[[doc calendar] selectedDay]];
        if ([newItem secsUntilNotif])
            [doc setTimerForItem:newItem];
        [[doc currentItems] replaceObjectAtIndex:row withObject:newItem];
        [doc updateMatrix];
    }
}



@end

