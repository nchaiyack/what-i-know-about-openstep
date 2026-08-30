/*
 *  Preferences.m
 *  Author: Ali Ozer
 *  Created: Oct 24, 1995 for Edit
 *  Modified: Jan 96 for Yap
 *
 *  Preferences controller... Manages the display, editing, and persistence of a
 *  a set of defaults.
 *
 *  This module allows for UI where there is or there isn't an OK button. 
 *  If you wish to have an OK button, connect OK to ok:, Revert to revert:, 
 *  and don't call commitDisplayedValues from the various action messages. 
 *  The ivar displayedValues is a mirror of the UI. These are committed by
 *  copying these values to curValues.
 *
 *  You may freely copy, distribute and reuse the code in this example.
 *  NeXT disclaims any warranty of any kind, expressed or implied,
 *  as to its fitness for any particular use.
 */

#import <AppKit/AppKit.h>
#import "Preferences.h"
#import "IntegerFormatter.h"

static NSDictionary *defaultValues() {
    static NSDictionary *dict = nil;
    if (!dict) {
        dict = [[NSDictionary alloc] initWithObjectsAndKeys:
            [NSNumber numberWithBool:NO], ShowGridLines,
            [NSNumber numberWithBool:NO], ShowCache,
            [NSNumber numberWithBool:YES], ClearCache, 
            [NSNumber numberWithBool:YES], DeleteBackup, 
            [NSNumber numberWithInt:612], ViewWidth, 
            [NSNumber numberWithInt:792], ViewHeight, 
		nil];
    }
    return dict;
}

@implementation Preferences

static Preferences *sharedInstance = nil;

+ (id)objectForKey:(id)key {
    return [[[self sharedInstance] preferences] objectForKey:key];
}

+ (void)saveDefaults {
    if (sharedInstance) {
	[Preferences savePreferencesToDefaults:[sharedInstance preferences]];
    }
}

+ (Preferences *)sharedInstance {
    return sharedInstance ? sharedInstance : [[self alloc] init];
}

- (id)init {
    if (sharedInstance) {
	[self dealloc];
    } else {
        [super init];
        curValues = [[[self class] preferencesFromDefaults] copyWithZone:[self zone]];
        [self discardDisplayedValues];
        sharedInstance = self;
    }
    return sharedInstance;
}

- (void)dealloc {
}

- (NSDictionary *)preferences {
    return curValues;
}

- (void)showPanel:(id)sender {
    if (!dontDeleteBackupButton) {
 	   NSFormatter *intFormatter;
        if (![NSBundle loadNibNamed:@"Preferences" owner:self])  {
            NSLog(@"Failed to load Preferences.nib");
            NSBeep();
            return;
        }
        intFormatter = [[IntegerFormatter allocWithZone:[self zone]] initWithMinValue:1 maxValue:10000];
        [[viewWidthField cell] setFormatter:intFormatter];
        [[viewHeightField cell] setFormatter:intFormatter];
        [intFormatter release];
        [self updateUI];
        [[dontDeleteBackupButton window] center];
    }
    [[dontDeleteBackupButton window] makeKeyAndOrderFront:nil];
}

- (void)updateUI {
    [dontDeleteBackupButton setState:[[displayedValues objectForKey:DeleteBackup] boolValue] ? 0 : 1];
    [dontClearCacheButton setState:[[displayedValues objectForKey:ClearCache] boolValue] ? 0 : 1];
    [showCacheButton setState:[[displayedValues objectForKey:ShowCache] boolValue] ? 1 : 0];
    [showGridLinesButton setState:[[displayedValues objectForKey:ShowGridLines] boolValue] ? 1 : 0];
    [viewWidthField setObjectValue:[displayedValues objectForKey:ViewWidth]];
    [viewHeightField setObjectValue:[displayedValues objectForKey:ViewHeight]];
}

/* To catch changes in text fields */
- (void)controlTextDidEndEditing:(NSNotification *)notification {
    [self miscChanged:nil];
}

/* To catch all other changes */
- (void)miscChanged:(id)sender {
    static NSNumber *yes = nil;
    static NSNumber *no = nil;
    
    if (!yes) {
        yes = [[NSNumber alloc] initWithBool:YES];
        no = [[NSNumber alloc] initWithBool:NO];
    }

    [displayedValues setObject:[dontDeleteBackupButton state] ? no : yes forKey:DeleteBackup];
    [displayedValues setObject:[dontClearCacheButton state] ? no : yes forKey:ClearCache];
    [displayedValues setObject:[showCacheButton state] ? yes : no forKey:ShowCache];
    [displayedValues setObject:[showGridLinesButton state] ? yes : no forKey:ShowGridLines];
    [displayedValues setObject:[viewWidthField objectValue] forKey:ViewWidth];
    [displayedValues setObject:[viewHeightField objectValue] forKey:ViewHeight];

    [self commitDisplayedValues];
    [[NSNotificationCenter defaultCenter] postNotificationName:PreferencesChangedNotification object:self];
}

/**** Commit/revert etc ****/

- (void)commitDisplayedValues {
    if (curValues != displayedValues) {
        [curValues release];
        curValues = [displayedValues copyWithZone:[self zone]];
    }
}

- (void)discardDisplayedValues {
    if (curValues != displayedValues) {
        [displayedValues release];
        displayedValues = [curValues mutableCopyWithZone:[self zone]];
        [self updateUI];
    }
}

- (void)ok:(id)sender {
    [self commitDisplayedValues];
}

- (void)revertToDefault:(id)sender {
    curValues = [defaultValues() copyWithZone:[self zone]];
    [self discardDisplayedValues];
}

- (void)revert:(id)sender {
    [self discardDisplayedValues];
}

/**** Code to deal with defaults ****/
   
#define getBoolDefault(name) \
  {NSString *str = [defaults stringForKey:name]; \
      [dict setObject:str ? [NSNumber numberWithBool:[str hasPrefix:@"Y"]] : [defaultValues() objectForKey:name] forKey:name];}

#define getIntDefault(name) \
  {int val = [defaults integerForKey:name]; \
      [dict setObject:val ? [NSNumber numberWithInt:val] : [defaultValues() objectForKey:name] forKey:name];}

+ (NSDictionary *)preferencesFromDefaults {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSMutableDictionary *dict = [NSMutableDictionary dictionaryWithCapacity:10];

    getBoolDefault(DeleteBackup);
    getBoolDefault(ClearCache);
    getBoolDefault(ShowCache);
    getBoolDefault(ShowGridLines);
    getIntDefault(ViewWidth);
    getIntDefault(ViewHeight);

    return dict;
}

#define setBoolDefault(name) \
  {if ([[defaultValues() objectForKey:name] isEqual:[dict objectForKey:name]]) [defaults removeObjectForKey:name]; else [defaults setBool:[[dict objectForKey:name] boolValue] forKey:name];}

#define setIntDefault(name) \
  {if ([[defaultValues() objectForKey:name] isEqual:[dict objectForKey:name]]) [defaults removeObjectForKey:name]; else [defaults setInteger:[[dict objectForKey:name] intValue] forKey:name];}

+ (void)savePreferencesToDefaults:(NSDictionary *)dict {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    setBoolDefault(ClearCache);
    setBoolDefault(ShowCache);
    setBoolDefault(ShowGridLines);
    setBoolDefault(DeleteBackup);
    setIntDefault(ViewWidth);
    setIntDefault(ViewHeight);
}

@end
