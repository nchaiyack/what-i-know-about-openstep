#import <Foundation/Foundation.h>

@class YapOutput;
@class NSApplication;

@interface Controller : NSObject {
    id infoPanel;
    id outputView;
}

/* NSApplication delegate methods */
- (BOOL)application:(NSApplication *)app openFile:(NSString *)filename;
- (BOOL)application:(NSApplication *)app openTempFile:(NSString *)filename;
- (BOOL)applicationOpenUntitledFile:(NSApplication *)app;
- (BOOL)applicationShouldTerminate:(NSApplication *)app;

/* Action methods */
- (void)createNew:(id)sender;
- (void)open:(id)sender;
- (void)saveAll:(id)sender;
- (void)showInfoPanel:(id)sender;

/* Outlet methods */
- (void)setVersionField:(id)anObject;	/* Fake; there's no outlet */

/* Output view... */
- (YapOutput *)outputView;

@end
