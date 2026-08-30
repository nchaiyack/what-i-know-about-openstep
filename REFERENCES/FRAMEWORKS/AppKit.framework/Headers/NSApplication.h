/*
	NSApplication.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#import <AppKit/NSResponder.h>
#import <AppKit/NSNibLoading.h>
#import <AppKit/AppKitDefines.h>

@class NSApplication;
@class NSWindow;
@class NSPasteboard;
@class NSEvent;
@class NSImage;
@class NSMenu;

/* Modes passed to NSRunLoop */
APPKIT_EXTERN NSString *NSModalPanelRunLoopMode;
APPKIT_EXTERN NSString *NSEventTrackingRunLoopMode;

/* Pre-defined return values for runModalFor: and runModalSession:. The system also reserves all values below these. */
enum {
    NSRunStoppedResponse			= (-1000),
    NSRunAbortedResponse			= (-1001),
    NSRunContinuesResponse			= (-1002)
};

#ifndef STRICT_OPENSTEP
/* used with NSRunLoop's performSelector:target:argument:order:modes: */
enum {
    NSUpdateWindowsRunLoopOrdering		= 500000
};
#endif STRICT_OPENSTEP

APPKIT_EXTERN id NSApp;

/* Information used by the system during modal sessions */
typedef struct _NSModalSession *NSModalSession;

@interface NSApplication : NSResponder
{
    NSEvent            *_currentEvent;
    NSMutableArray     *_windowList;
    id                  _keyWindow;
    id                  _mainWindow;
    id                  _delegate;
    int                *_hiddenList;
    int                 _hiddenCount;
    NSDPSContext       *_context;
    id                  _appListener;
    id			_appSpeaker;
    short               _unusedApp;
    short               _running;
    struct __appFlags {
	unsigned int        _hidden:1;
	unsigned int        _RESERVED1:1;
	unsigned int        _active:1;
	unsigned int        _hasBeenRun:1;
	unsigned int        _doingUnhide:1;
	unsigned int	    _delegateReturnsValidRequestor:1;
	unsigned int	    _deactPending:1;
	unsigned int        _invalidState:1;
	unsigned int        _invalidEvent:1;
	unsigned int        _postedWindowsNeedUpdateNote:1;
        unsigned int        _wantsToActivate:1;
        unsigned int        _doingHide:1;
	unsigned int	    _dontSendShouldTerminate:1;
        unsigned int        _skipWin32DelayedRestoreKeyWindowAfterHide:1;
	unsigned int        _reserved:18;
    }                   _appFlags;
    id                  _mainMenu;
    id                  _appIcon;
    id                  _nameTable;
    id                  _reservedApplication1;
    id                  _reservedApplication2;
}

+ (NSApplication *)sharedApplication;

- (void)setDelegate:(id)anObject;
- (id)delegate;
- (NSDPSContext *)context;
- (void)hide:(id)sender;
- (void)unhide:(id)sender;
- (void)unhideWithoutActivation;
- (NSWindow *)windowWithWindowNumber:(int)windowNum;
- (NSWindow *)mainWindow;
- (NSWindow *)keyWindow;
- (BOOL)isActive;
- (BOOL)isHidden;
- (BOOL)isRunning;
- (void)deactivate;
- (void)activateIgnoringOtherApps:(BOOL)flag;

- (void)finishLaunching;
- (void)run;
- (int)runModalForWindow:(NSWindow *)theWindow;
- (void)stop:(id)sender;
- (void)stopModal;
- (void)stopModalWithCode:(int)returnCode;
- (void)abortModal;
- (NSModalSession)beginModalSessionForWindow:(NSWindow *)theWindow;
- (int)runModalSession:(NSModalSession)session;
- (void)endModalSession:(NSModalSession)session;
- (void)terminate:(id)sender;

- (NSEvent *)nextEventMatchingMask:(unsigned int)mask untilDate:(NSDate *)expiration inMode:(NSString *)mode dequeue:(BOOL)deqFlag;
- (void)discardEventsMatchingMask:(unsigned int)mask beforeEvent:(NSEvent *)lastEvent;
- (void)postEvent:(NSEvent *)event atStart:(BOOL)flag;
- (NSEvent *)currentEvent;

- (void)sendEvent:(NSEvent *)theEvent;
- (void)preventWindowOrdering;
- (NSWindow *)makeWindowsPerform:(SEL)aSelector inOrder:(BOOL)flag;
- (NSArray *)windows;
- (void)setWindowsNeedUpdate:(BOOL)needUpdate;
- (void)updateWindows;

- (void)setMainMenu:(NSMenu *)aMenu;
- (NSMenu *)mainMenu;

- (void)setApplicationIconImage:(NSImage *)image;
- (NSImage *)applicationIconImage;

- (BOOL)sendAction:(SEL)theAction to:(id)theTarget from:(id)sender;
- (id)targetForAction:(SEL)theAction;
- (BOOL)tryToPerform:(SEL)anAction with:(id)anObject;
- (id)validRequestorForSendType:(NSString *)sendType returnType:(NSString *)returnType;

- (void)reportException:(NSException *)theException;

@end

@interface NSApplication(NSWindowsMenu)
- (void)setWindowsMenu:(NSMenu *)aMenu;
- (NSMenu *)windowsMenu;
- (void)arrangeInFront:(id)sender;
- (void)removeWindowsItem:(NSWindow *)win;
- (void)addWindowsItem:(NSWindow *)win title:(NSString *)aString filename:(BOOL)isFilename;
- (void)changeWindowsItem:(NSWindow *)win title:(NSString *)aString filename:(BOOL)isFilename;
- (void)updateWindowsItem:(NSWindow *)win;
- (void)miniaturizeAll:(id)sender;
@end


@interface NSObject(NSApplicationNotifications)
- (void)applicationWillFinishLaunching:(NSNotification *)notification;
- (void)applicationDidFinishLaunching:(NSNotification *)notification;
- (void)applicationWillHide:(NSNotification *)notification;
- (void)applicationDidHide:(NSNotification *)notification;
- (void)applicationWillUnhide:(NSNotification *)notification;
- (void)applicationDidUnhide:(NSNotification *)notification;
- (void)applicationWillBecomeActive:(NSNotification *)notification;
- (void)applicationDidBecomeActive:(NSNotification *)notification;
- (void)applicationWillResignActive:(NSNotification *)notification;
- (void)applicationDidResignActive:(NSNotification *)notification;
- (void)applicationWillUpdate:(NSNotification *)notification;
- (void)applicationDidUpdate:(NSNotification *)notification;
- (void)applicationWillTerminate:(NSNotification *)notification;
@end

@interface NSObject(NSApplicationDelegate)
- (BOOL)applicationShouldTerminate:(NSApplication *)sender;
- (BOOL)application:(NSApplication *)sender openFile:(NSString *)filename;
- (BOOL)application:(NSApplication *)sender openTempFile:(NSString *)filename;
- (BOOL)applicationOpenUntitledFile:(NSApplication *)sender;
- (BOOL)application:(id)sender openFileWithoutUI:(NSString *)filename;

#ifndef STRICT_OPENSTEP
- (BOOL)application:(NSApplication *)sender printFile:(NSString *)filename;
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender;
#endif
@end

@interface NSApplication(NSServicesMenu)
- (void)setServicesMenu:(NSMenu *)aMenu;
- (NSMenu *)servicesMenu;
- (void)registerServicesMenuSendTypes:(NSArray *)sendTypes returnTypes:(NSArray *)returnTypes;
@end

@interface NSObject(NSServicesRequests)
- (BOOL)writeSelectionToPasteboard:(NSPasteboard *)pboard types:(NSArray *)types;
- (BOOL)readSelectionFromPasteboard:(NSPasteboard *)pboard;
@end

@interface NSApplication(NSServicesHandling)
- (void)setServicesProvider:(id)provider;
- (id)servicesProvider;
@end

#ifndef STRICT_OPENSTEP
#ifdef WIN32
@interface NSApplication (NSWindowsExtensions)
+ (void)setApplicationHandle:(void * /*HINSTANCE*/)hInstance previousHandle:(void * /*HINSTANCE*/)PrevInstance commandLine:(NSString *)cmdLine show:(int)cmdShow;
+ (void)useRunningCopyOfApplication;
- (void * /*HINSTANCE*/)applicationHandle;
- (NSWindow *)windowWithWindowHandle:(void * /*HWND*/)hWnd; // does not create a new NSWindow
@end
#endif

#endif

/* An Application's startup function */

APPKIT_EXTERN int NSApplicationMain(int argc, const char *argv[]);

/*
 * Functions to enable/disable Services Menu items.  These should usually
 * only be called by service PROVIDERS (since they are the only ones who
 * know the name of the services, requestors don't).  The itemName in the
 * two functions below is the language-independent "Menu Item:" entry in
 * the __services section (which all provided services must have).  The
 * set function returns whether it was successful.
 * NSUpdateDynamicServices() causes the services information for the
 * system to be updated.  This will only be necessary if your program
 * adds dynamic services to the system (i.e. services not found in macho
 * segments of executables).
 */

APPKIT_EXTERN BOOL NSShowsServicesMenuItem(NSString * itemName);
APPKIT_EXTERN int NSSetShowsServicesMenuItem(NSString * itemName, BOOL enabled);
APPKIT_EXTERN void NSUpdateDynamicServices(void);
APPKIT_EXTERN BOOL NSPerformService(NSString *itemName, NSPasteboard *pboard);

APPKIT_EXTERN void NSRegisterServicesProvider(id provider, NSString *name); // apps should use -setServicesProvider
APPKIT_EXTERN void NSUnregisterServicesProvider(NSString *name);

/* Notifications */
APPKIT_EXTERN NSString *NSApplicationDidBecomeActiveNotification;
APPKIT_EXTERN NSString *NSApplicationDidHideNotification;
APPKIT_EXTERN NSString *NSApplicationDidFinishLaunchingNotification;
APPKIT_EXTERN NSString *NSApplicationDidResignActiveNotification;
APPKIT_EXTERN NSString *NSApplicationDidUnhideNotification;
APPKIT_EXTERN NSString *NSApplicationDidUpdateNotification;
APPKIT_EXTERN NSString *NSApplicationWillBecomeActiveNotification;
APPKIT_EXTERN NSString *NSApplicationWillHideNotification;
APPKIT_EXTERN NSString *NSApplicationWillFinishLaunchingNotification;
APPKIT_EXTERN NSString *NSApplicationWillResignActiveNotification;
APPKIT_EXTERN NSString *NSApplicationWillUnhideNotification;
APPKIT_EXTERN NSString *NSApplicationWillUpdateNotification;
APPKIT_EXTERN NSString *NSApplicationWillTerminateNotification;

