#import <Foundation/NSObject.h>
#import <Foundation/NSDictionary.h>

/* Keys in the dictionary... */   
#define DeleteBackup @"DeleteBackup"
#define ViewWidth @"ViewWidth"
#define ViewHeight @"ViewHeight"
#define ShowCache @"ShowCache"
#define ShowGridLines @"ShowGridLines"
#define ClearCache @"ClearCache"

/* Notification sent when any default changes */
#define PreferencesChangedNotification @"PreferencesChangedNotification"

@interface Preferences : NSObject {
    id dontDeleteBackupButton;
    id showCacheButton;
    id dontClearCacheButton;
    id showGridLinesButton;
    id viewWidthField;
    id viewHeightField;
    id tabWidthField;

    NSDictionary *curValues;
    NSMutableDictionary *displayedValues;
}

+ (id)objectForKey:(id)key;	/* Convenience for getting global preferences */
+ (void)saveDefaults;		/* Convenience for saving global preferences */

+ (Preferences *)sharedInstance;

- (NSDictionary *)preferences;	/* The current preferences; contains values for the documented keys */

- (void)showPanel:(id)sender;	/* Shows the panel */

- (void)updateUI;		/* Updates the displayed values in the UI */
- (void)commitDisplayedValues;	/* The displayed values are made current */
- (void)discardDisplayedValues;	/* The displayed values are replaced with current prefs and updateUI is called */

- (void)revert:(id)sender;	/* Reverts the displayed values to the current preferences */
- (void)ok:(id)sender;		/* Calls commitUI to commit the displayed values as current */
- (void)revertToDefault:(id)sender;    

- (void)miscChanged:(id)sender;		/* Action message for most of the misc items in the UI to get displayedValues */

+ (NSDictionary *)preferencesFromDefaults;
+ (void)savePreferencesToDefaults:(NSDictionary *)dict;

@end
